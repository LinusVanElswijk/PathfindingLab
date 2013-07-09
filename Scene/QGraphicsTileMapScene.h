#ifndef QGRAPHICSTILEMAPSCENE_H
#define QGRAPHICSTILEMAPSCENE_H

#include <QGraphicsScene>
#include <QGraphicsTileItem.h>
#include <QGraphicsNodeItem.h>
#include <QGraphicsEdgeItem.h>
#include <TileMap.h>
#include <Task.h>

#include <AbstractGraph.h>

#include <map>
#include <list>
#include <utility>

#include "Edge.hpp"
#include "position.h"
#include "InteractionHandler.h"

class QGraphicsTileMapScene : public QGraphicsScene
{
    Q_OBJECT
    public:
        typedef TileMap::uint uint;

        explicit QGraphicsTileMapScene(const TileMap& tileMap, InteractionHandler&  handler, QObject *parent = 0)
        :QGraphicsScene(parent),
         tileMap(tileMap),
         tiles(),
         nodes(),
         abstractNodes(),
         edges(),
         pathEdges(),
         checkedTiles(),
         handler(handler)
        { }

    signals:

    public slots:

    public:
        void rebuild();
        void setScale(const qreal& scale);

        const TileMap& tileMap;

        void setVisited(unsigned int x, unsigned int y, graphs::Real evaluation) {
            QPoint point(x,y);
            QGraphicsNodeItem* node = nodes.at(point);

            node->setVisited(true);
            node->setEvaluation(evaluation);
            node->update();

            visitedNodes.push_back(node);
        }

        void setExpanded(unsigned int x, unsigned int y) {
            QPoint point(x,y);
            QGraphicsNodeItem* node = nodes.at(point);

            node->setExpanded(true);
            node->update();

            expandedNodes.push_back(node);
        }

        void clearVisited() {
            for(auto node: visitedNodes) {
                node->setVisited(false);
                node->update();
            }
            visitedNodes.clear();

            for(auto node: expandedNodes) {
                node->setExpanded(false);
                node->update();
            }
            expandedNodes.clear();

            for(auto node: pathNodes) {
                node->setPath(false);
                node->update();
            }
            pathNodes.clear();
        }

        void setPath(unsigned int x, unsigned int y) {
            QPoint point(x,y);
            QGraphicsNodeItem* node = nodes.at(point);

            node->setPath(true);
            node->update();

            pathNodes.push_back(node);
        }

        void addPathEdge(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
            QPoint point1(x1,y1),
                   point2(x2,y2);

            QGraphicsEdgeItem* edge = new QGraphicsEdgeItem(nodes.at(point1), nodes.at(point2));
            this->addItem(edge);
            edge->setPath(true);

            pathEdges.push_back(edge);
        }

        void clearPathEdges() {
            for(auto edge: pathEdges) {
                this->removeItem(edge);
            }

            this->update();
            pathEdges.clear();
        }

        void addLineOfSightTile(unsigned int x, unsigned int y) {
            QPoint point(x,y);

            QGraphicsTileItem* tile = this->tiles.at(point);
            tile->setLineOfSightCheck(true);
            tile->update();

            checkedTiles.push_back(tile);

            this->update();
        }

        void clearLineOfSightChecks() {
            for(auto tile: checkedTiles) {
                tile->setLineOfSightCheck(false);
            }

            checkedTiles.clear();
        }

    private:
        void build();

        void buildTiles();
        void buildNodes();
        void buildEdges(const graphs::GridGraph* const graph);

        void buildClusterGrid(const AbstractGraph* const graph) {
            for(unsigned int x = 1; x < graph->getAbstractWidth(); x++) {
                auto gridLine = new QGraphicsLineItem(x * 100 - 5, 0, x * 100 - 5, tileMap.getHeight() * 10);
                gridLine->setPen(QPen(Qt::yellow));
                gridLine->setZValue(2);
                this->clusterGridLines.push_back(gridLine);
                this->addItem(gridLine);

            }

            for(unsigned int y = 1; y < graph->getAbstractHeight(); y++) {
                auto gridLine = new QGraphicsLineItem(0,y * 100 - 5, tileMap.getWidth() * 10, y * 100 - 5);
                gridLine->setPen(QPen(Qt::yellow));
                gridLine->setZValue(2);
                this->clusterGridLines.push_back(gridLine);
                this->addItem(gridLine);
            }
        }
        /*
        void clearClusterGrid() {
            for(auto gridLine: clusterGridLines) {
                this->removeItem(gridLine);
                delete gridLine;
                gridLine = nullptr;
            }

            clusterGridLines.clear();
        }*/

        void buildAbstractMap(const AbstractGraph* const graph) {
            for(unsigned int i = 0; i < graph->getNrOfVertices(); i++) {
                auto &abstractVertex = graph->getVertex(i);
                auto &baseVertex = graph->toBase(abstractVertex);

                auto node = new QGraphicsNodeItem(baseVertex, this->handler);
                node->setAbstract(true);
                abstractNodes.insert(std::make_pair(i, node));
                this->addItem(node);
            }

            buildAbstractEdges(graph);
        }


        void buildAbstractEdges(const AbstractGraph* const graph) {
            for(uint i = 0; i < graph->getNrOfVertices(); i++){
                auto &vertex = graph->getVertex(i);
                auto &gridVertex = graph->toBase(vertex);
                QGraphicsNodeItem* node = nodes.at(QPoint(gridVertex.getX(),gridVertex.getY()));

                const std::list<graphs::ConstEdgePtr>&& edges = vertex.getOutgoingEdges();

                for(auto edge: edges) {
                    auto &otherVertex = graph->toBase(graph->getVertex(edge->toIndex));
                    QPoint otherNode = QPoint(otherVertex.getX(), otherVertex.getY());

                    //if(otherNode.first <= x && otherNode.second <= y) {
                    QGraphicsEdgeItem* edgeItem = new QGraphicsEdgeItem(node, nodes.find(otherNode)->second);

                    edgeItem->setAbstract(true);
                    edgeItem->setZValue(1.25);
                    this->addItem(edgeItem);
                }
            }
        }

        class QPointComparator {
            public:
                bool operator() (const QPoint& leftHandSide, const QPoint& rightHandSide) const
                {
                    if(leftHandSide.x() != rightHandSide.x())
                        return leftHandSide.x() < rightHandSide.x();
                    else
                        return leftHandSide.y() < rightHandSide.y();
                }
        };

        class QPointPairComparator {
            private:
                QPointComparator pointComp;

            public:

                bool operator() (const std::pair<QPoint, QPoint>& leftHandSide, const std::pair<QPoint, QPoint>& rightHandSide) const
                {
                    if(leftHandSide.first != rightHandSide.first)
                        return pointComp(leftHandSide.first, rightHandSide.first);
                    else
                        return pointComp(leftHandSide.second, rightHandSide.second);
                }
        };

        std::map<QPoint, QGraphicsTileItem*, QPointComparator> tiles;
        std::map<QPoint, QGraphicsNodeItem*, QPointComparator> nodes;
        std::map<unsigned int, QGraphicsNodeItem*> abstractNodes;
        std::map<std::pair<QPoint, QPoint>, QGraphicsEdgeItem*> edges;


        std::list<QGraphicsNodeItem*> visitedNodes;
        std::list<QGraphicsNodeItem*> expandedNodes;
        std::list<QGraphicsNodeItem*> pathNodes;
        std::list<QGraphicsEdgeItem*> pathEdges;
        std::list<QGraphicsTileItem*> checkedTiles;

        std::list<QGraphicsLineItem*> clusterGridLines;

        InteractionHandler& handler;
};

#endif // QGRAPHICSTILEMAPSCENE_H
