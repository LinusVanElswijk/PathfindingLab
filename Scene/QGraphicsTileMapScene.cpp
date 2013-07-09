#include "QGraphicsTileMapScene.h"

void QGraphicsTileMapScene::rebuild() {
    clear();

    tiles.clear();
    nodes.clear();
    edges.clear();

    clusterGridLines.clear();
    abstractNodes.clear();

    build();
}

void QGraphicsTileMapScene::build() {
    //QPixmap *pixMap = new QPixmap(tileMap.getWidth(), tileMap.getHeight());
    //QPainter painter(pixMap);

    buildTiles();

    buildNodes();

    if(tileMap.getAbstractGraph()) {
        buildClusterGrid(tileMap.getAbstractGraph());
        buildAbstractMap(tileMap.getAbstractGraph());
    }
}


void QGraphicsTileMapScene::buildTiles() {
    for(uint y = 0; y < tileMap.getHeight(); y++){
        for(uint x = 0; x < tileMap.getWidth(); x++){
            QGraphicsTileItem* item = new QGraphicsTileItem(x, y, tileMap, handler);
            this->addItem(item);

            auto entry = std::pair<QPoint, QGraphicsTileItem*>(QPoint(x,y), item);
            tiles.insert(entry);
        }
    }
}

void QGraphicsTileMapScene::buildNodes() {
    std::cout << tileMap.getGraph() << std::endl;
    if(tileMap.getGraph() != NULL) {
        const graphs::GridGraph* const graph = tileMap.getGraph();

        for(uint y = 0; y < graph->getHeight(); y++){
            for(uint x = 0; x < graph->getWidth(); x++){
                QGraphicsNodeItem* node = new QGraphicsNodeItem(graph->getVertex(x,y), handler);
                this->addItem(node);

                auto entry = std::pair<QPoint, QGraphicsNodeItem*>(QPoint(x,y), node);
                nodes.insert(entry);
            }
        }

        buildEdges(graph);
    }
}

void QGraphicsTileMapScene::buildEdges(const graphs::GridGraph* const graph) {
    for(uint y = 0; y < graph->getHeight(); y++){
        for(uint x = 0; x < graph->getWidth(); x++){
            QGraphicsNodeItem* node = nodes.at(QPoint(x,y));
            const graphs::GridVertex& vertex = node->getVertex();
            const std::list<graphs::ConstEdgePtr>&& edges = vertex.getOutgoingEdges();

            for(auto edge: edges) {
                QPoint otherNode = QPoint(graph->indexToX(edge->toIndex), graph->indexToY(edge->toIndex));

                //if(otherNode.first <= x && otherNode.second <= y) {
                QGraphicsEdgeItem* edgeItem = new QGraphicsEdgeItem(node, nodes.find(otherNode)->second);
                this->addItem(edgeItem);
                //}
            }
        }
    }
}
