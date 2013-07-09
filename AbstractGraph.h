#ifndef ABSTRACT_GRAPH_H
#define ABSTRACT_GRAPH_H

#include "GridGraph.hpp"
#include <utility>
#include <map>
#include <vector>

#include <SearchAlgorithm.hpp>
#include <ClusterBoundPathfindingProblem.h>
#include <VertexHash.h>
#include <DistanceFunctions.h>
#include <AStar.hpp>
#include <Solution.hpp>
//#include <DDALineOfSight.hpp>

class AbstractGraph: public graphs::Graph
{

public:
    AbstractGraph(const graphs::GridGraph& graph, const unsigned int& clusterSize = 10);

    unsigned int getNumberOfClusters() const {
        return clusters.size();
    }

    unsigned int getAbstractWidth() const {
        return abstractWidth;
    }

    unsigned int getAbstractHeight() const {
        return abstractHeight;
    }

    unsigned int getClusterSize() const {
        return clusterSize;
    }

    unsigned int getNumberOfVisits() const {
        return visits;
    }

    unsigned int getMaxNodesInMemory() const {
        return maxNodesInMemory;
    }

    void clearNodesAndMem() {
        visits = maxNodesInMemory = 0;
    }

    void updateNodesAndMem(const unsigned int& visits, const unsigned int& mem) {
        this->visits += visits;
        if(mem > maxNodesInMemory) {
            maxNodesInMemory = mem;
        }
    }

    const graphs::GridVertex& toBase(const graphs::Vertex& vertex) const {
        return *abstractToBase.at(&vertex);
    }

    const graphs::Vertex& toAbstract(const graphs::GridVertex& gridVertex) const {
        return *baseToAbstract.at(&gridVertex);
    }

    std::pair<unsigned int, unsigned int> nodePositionToClusterPosition(const unsigned int& x, const unsigned int& y) const;

    void insertStartAndGoal(const graphs::GridVertex& start, const graphs::GridVertex& goal);

    void removeStartAndGoal();

private:
    struct Cluster {
    public:
        Cluster(const unsigned int& x, const unsigned int& y, AbstractGraph* graph)
        :x(x),y(y),
         graph(graph),
         nodes()
        {

        }

        bool isNeighbor(const Cluster& other) const {
            unsigned int xDiff = abs(x - other.x),
                         yDiff = abs(y - other.y);

            return (xDiff == 1 || yDiff == 1) && (xDiff != yDiff);
        }

        unsigned int left() const {
            return x * graph->clusterSize;
        }

        unsigned int right() const {
            return std::min(graph->baseGraph.getRight(), (x + 1) * graph->clusterSize - 1);
        }

        unsigned int top() const {
            return y * graph->clusterSize;
        }

        unsigned int bottom() const {
            return std::min(graph->baseGraph.getBottom(), (y + 1) * graph->clusterSize - 1);
        }

        void removeNode(const graphs::Vertex &vertex) {
            for(auto iterator = nodes.begin(); iterator != nodes.end(); iterator++) {
                if(&vertex == *iterator) {
                    nodes.erase(iterator);
                    break;
                }
            }
        }

        std::vector<graphs::Vertex*> nodes;

        unsigned int x, y;
        AbstractGraph* graph;
    };

    typedef std::pair<graphs::Vertex*, graphs::Vertex*> Entrance;
    typedef std::pair<Entrance, Entrance> EntrancePair;

    friend class Cluster;

    void addClusters();


    void buildEntrances();

    void buildLeftEntrances();
    void buildLeftEntrances(Cluster& left);
    std::pair<unsigned int, unsigned int>* maximalVerticalEntrancePositions(const unsigned int& x1, const unsigned int& x2, unsigned int& y, const unsigned int& maxY);
    void createVerticalEntrance(unsigned int x1, unsigned int x2, std::pair<unsigned int, unsigned int>*& minAndMaxY);

    void buildTopEntrances();
    void buildTopEntrances(Cluster& top);
    std::pair<unsigned int, unsigned int>* maximalHorizontalEntrancePositions(unsigned int& x, const unsigned int& maxX, const unsigned int& y1, const unsigned int& y2);
    void createHorizontalEntrance(std::pair<unsigned int, unsigned int>*& minAndMaxX, unsigned int y1, unsigned int y2);

    graphs::Vertex& addVertex(const unsigned int& baseX, const unsigned int& baseY);
    graphs::Vertex& fetchOrAddVertex(const unsigned int& baseX, const unsigned int& baseY);

    void buildEdge(graphs::Vertex &start, graphs::Vertex &goal, const bool& interEdge);

    void buildIntraEdges();

    unsigned int clusterIndexToX(const unsigned int& index) {
        return index / abstractHeight;
    }

    unsigned int clusterIndexToY(const unsigned int& index) {
        return index % abstractHeight;
    }

    unsigned int clusterPositionToIndex(const unsigned int& x, const unsigned int& y) {
        return x * abstractHeight + y;
    }

    void removeVertex(graphs::Vertex& vertex);

    void connect(graphs::Vertex* vertex, Cluster& cluster);

    static unsigned int divRoundUp(const unsigned int& dividend, const unsigned int& divisor);

    const graphs::GridGraph& baseGraph;

    const unsigned int abstractWidth, abstractHeight;
    const unsigned int clusterSize;

    std::vector<Cluster> clusters;
    std::map<const graphs::GridVertex*, graphs::Vertex*> baseToAbstract;
    std::map<const graphs::Vertex*, const graphs::GridVertex*> abstractToBase;
    std::map<const graphs::Vertex*, Cluster*> abstractToCluster;

    graphs::Vertex *start, *goal;
    bool newStart, newGoal;

    unsigned int visits, maxNodesInMemory;
};

#endif // ABSTRACT_GRAPH_H
