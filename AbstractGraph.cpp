#include "AbstractGraph.h"

AbstractGraph::AbstractGraph(const graphs::GridGraph& graph, const unsigned int& clusterSize)
:Graph(0),
 baseGraph(graph),
 abstractWidth(divRoundUp(graph.getWidth(), clusterSize)),
 abstractHeight(divRoundUp(graph.getHeight(), clusterSize)),
 clusterSize(clusterSize),
 clusters(),
 baseToAbstract(),
 abstractToBase(),
 abstractToCluster(),
 start(nullptr),
 goal(nullptr),
 newStart(false),
 newGoal(false)
{
    addClusters();
    std::cout << "Clusters = " << this->getNumberOfClusters() << std::endl;
    buildEntrances();
    std::cout << "Entrance Nodes = " << this->getNrOfVertices() << std::endl;

    buildIntraEdges();
}


unsigned int AbstractGraph::divRoundUp(const unsigned int& dividend, const unsigned int& divisor) {
    return (dividend + (divisor - 1)) / divisor;
}

void AbstractGraph::addClusters() {
    clusters.reserve(abstractWidth * abstractHeight);

    for(unsigned int x = 0; x < abstractWidth; x++) {
        for(unsigned int y = 0; y < abstractHeight; y++) {
            clusters.emplace_back(x,y, this);
        }
    }
}

void AbstractGraph::buildEntrances() {
    buildLeftEntrances();
    buildTopEntrances();
}

void AbstractGraph::buildLeftEntrances() {
   for(unsigned int y = 0; y < abstractHeight; y++) {
       for(unsigned int x = 0; x < abstractWidth - 1; x++) {
           unsigned int clusterIndex = clusterPositionToIndex(x, y);
           buildLeftEntrances(clusters.at(clusterIndex));
       }
   }
}

void AbstractGraph::buildTopEntrances()  {
   for(unsigned int y = 0; y < abstractHeight - 1; y++) {
       for(unsigned int x = 0; x < abstractWidth; x++) {
           unsigned int clusterIndex = clusterPositionToIndex(x, y);
           buildTopEntrances(clusters.at(clusterIndex));
       }
   }
}

void AbstractGraph::buildLeftEntrances(Cluster& left) {
    const unsigned int X_LEFT   = left.right(),
                       X_RIGHT  = X_LEFT+1,
                       Y_BOTTOM = left.bottom();

    unsigned int width = baseGraph.getWidth(),
                 height = baseGraph.getHeight(),
                 right = baseGraph.getRight(),
                 bottom = baseGraph.getBottom();

    unsigned int y = left.top();

    while(y <= Y_BOTTOM) {
        std::pair<unsigned int, unsigned int>* yPos = maximalVerticalEntrancePositions(X_LEFT, X_RIGHT, y, Y_BOTTOM);
        createVerticalEntrance(X_LEFT, X_RIGHT, yPos);
    }
}

void AbstractGraph::buildTopEntrances(Cluster& top) {
    const unsigned int Y_TOP    = top.bottom(),
                       Y_BOTTOM = Y_TOP+1,
                       X_RIGHT  = top.right();

    unsigned int width = baseGraph.getWidth(),
                 height = baseGraph.getHeight(),
                 right = baseGraph.getRight(),
                 bottom = baseGraph.getBottom();

    unsigned int x = top.left();

    while(x <= X_RIGHT) {
        std::pair<unsigned int, unsigned int>* xPos = maximalHorizontalEntrancePositions(x, X_RIGHT, Y_TOP, Y_BOTTOM);
        createHorizontalEntrance(xPos, Y_TOP, Y_BOTTOM);
    }
}

std::pair<unsigned int, unsigned int>* AbstractGraph::maximalVerticalEntrancePositions(const unsigned int& x1, const unsigned int& x2, unsigned int& y, const unsigned int& maxY) {
    if(!graphs::Vertex::mutuallyConnected(baseGraph.getVertex(x1,y), baseGraph.getVertex(x2,y))) {
        y++;
        return nullptr;
    }

    auto beginAndEnd = new std::pair<unsigned int, unsigned int>(y,y);

    do {
        beginAndEnd->second = y;
        y++;
    }
    while(y <= maxY &&
          graphs::Vertex::mutuallyConnected(baseGraph.getVertex(x1,y), baseGraph.getVertex(x2,y)) &&
          graphs::Vertex::mutuallyConnected(baseGraph.getVertex(x1,y), baseGraph.getVertex(x1,y-1)) &&
          graphs::Vertex::mutuallyConnected(baseGraph.getVertex(x2,y), baseGraph.getVertex(x2,y-1)) &&
          graphs::Vertex::mutuallyConnected(baseGraph.getVertex(x2,y), baseGraph.getVertex(x1,y-1)) &&
          graphs::Vertex::mutuallyConnected(baseGraph.getVertex(x1,y), baseGraph.getVertex(x2,y-1))
          );

    return beginAndEnd;
}

std::pair<unsigned int, unsigned int>* AbstractGraph::maximalHorizontalEntrancePositions(unsigned int& x, const unsigned int& maxX, const unsigned int& y1, const unsigned int& y2) {
    auto graphWidth  = baseGraph.getWidth(),
         graphHeight = baseGraph.getHeight();

    if(!graphs::Vertex::mutuallyConnected(baseGraph.getVertex(x,y1), baseGraph.getVertex(x,y2))) {
        x++;
        return nullptr;
    }

    auto beginAndEnd = new std::pair<unsigned int, unsigned int>(x,x);

    do {
        beginAndEnd->second = x;
        x++;
    }
    while(x <= maxX &&
          graphs::Vertex::mutuallyConnected(baseGraph.getVertex(x,y1), baseGraph.getVertex(x,y2)) &&
          graphs::Vertex::mutuallyConnected(baseGraph.getVertex(x,y1), baseGraph.getVertex(x-1,y1)) &&
          graphs::Vertex::mutuallyConnected(baseGraph.getVertex(x,y2), baseGraph.getVertex(x-1,y2)) &&
          graphs::Vertex::mutuallyConnected(baseGraph.getVertex(x,y2), baseGraph.getVertex(x-1,y1)) &&
          graphs::Vertex::mutuallyConnected(baseGraph.getVertex(x,y1), baseGraph.getVertex(x-1,y2))
         );

    return beginAndEnd;
}

void AbstractGraph::createVerticalEntrance(unsigned int x1, unsigned int x2, std::pair<unsigned int, unsigned int>*& minAndMaxY) {
    if(minAndMaxY) {
        auto &vertex1 = addVertex(x1, minAndMaxY->first),
             &vertex2 = addVertex(x2, minAndMaxY->first);

        buildEdge(vertex1, vertex2, true);

        if(minAndMaxY->second != minAndMaxY->first) {
            auto &vertex3 = addVertex(x1, minAndMaxY->second),
                 &vertex4 = addVertex(x2, minAndMaxY->second);

            buildEdge(vertex1, vertex3, true);
            buildEdge(vertex1, vertex4, true);
            buildEdge(vertex2, vertex3, true);
            buildEdge(vertex2, vertex4, true);
            buildEdge(vertex3, vertex4, true);
        }

        delete minAndMaxY;
        minAndMaxY = nullptr;
    }
}

void AbstractGraph::createHorizontalEntrance(std::pair<unsigned int, unsigned int>*& minAndMaxX, unsigned int y1, unsigned int y2) {
    if(minAndMaxX) {
        auto &vertex1 = fetchOrAddVertex(minAndMaxX->first, y1),
             &vertex2 = fetchOrAddVertex(minAndMaxX->first, y2);

        buildEdge(vertex1, vertex2, true);

        if(minAndMaxX->second != minAndMaxX->first) {
            auto &vertex3 = fetchOrAddVertex(minAndMaxX->second, y1),
                 &vertex4 = fetchOrAddVertex(minAndMaxX->second, y2);

            buildEdge(vertex1, vertex3, true);
            buildEdge(vertex1, vertex4, true);
            buildEdge(vertex2, vertex3, true);
            buildEdge(vertex2, vertex4, true);
            buildEdge(vertex3, vertex4, true);
        }

        delete minAndMaxX;
        minAndMaxX = nullptr;
    }
}

graphs::Vertex& AbstractGraph::fetchOrAddVertex(const unsigned int& baseX, const unsigned int& baseY) {
    auto it = this->baseToAbstract.find(&baseGraph.getVertex(baseX,baseY));
    if(it != baseToAbstract.end())
        return *(it->second);
    else
        return addVertex(baseX,baseY);
}

std::pair<unsigned int, unsigned int> AbstractGraph::nodePositionToClusterPosition(const unsigned int& x, const unsigned int& y) const {
    return std::pair<unsigned int, unsigned int>(x / clusterSize, y / clusterSize);
}

graphs::Vertex& AbstractGraph::addVertex(const unsigned int& baseX, const unsigned int& baseY){
    graphs::Vertex& abstract = Graph::addVertex();
    const graphs::GridVertex& base = baseGraph.getVertex(baseX, baseY);

    baseToAbstract.insert(std::pair<const graphs::GridVertex*, graphs::Vertex*>(&base, &abstract));
    abstractToBase.insert(std::pair<graphs::Vertex*, const graphs::GridVertex*>(&abstract, &base));

    std::pair<unsigned int, unsigned int>&& clusterXY = nodePositionToClusterPosition(baseX, baseY);
    Cluster& cluster = this->clusters.at(clusterPositionToIndex(clusterXY.first, clusterXY.second));
    cluster.nodes.push_back(&abstract);
    abstractToCluster.insert(std::pair<graphs::Vertex*, Cluster*>(&abstract, &cluster));

    return abstract;
}

void AbstractGraph::buildEdge(graphs::Vertex &start, graphs::Vertex &goal, const bool& interEdge) {
    const graphs::GridVertex &baseStart = *abstractToBase.at(&start),
                             &baseGoal = *abstractToBase.at(&goal);

    PathfindingProblem *problem;

    if(interEdge) {
        problem = new PathfindingProblem(baseStart, baseGoal, &baseGraph);
    }
    else {
        problem = new ClusterBoundPathfindingProblem(baseStart, baseGoal, &baseGraph, this);
    }
    TileDistanceFunction distance(baseStart);

    searchAlgorithms::AStar<PathfindingProblem, VertexHash> aStar(distance);
    //searchAlgorithms::ThetaStar<PathfindingProblem, VertexHash> aStar(distance, los);

    std::shared_ptr<searchAlgorithms::Solution<PathfindingProblem>> solution = aStar(*problem);
    if(solution) {
        this->addBidirectionalEdge(start, goal, solution->getCost());
    }

    this->updateNodesAndMem(aStar.getNrOfVisits(), aStar.getMaxNodesInMemory());

    delete problem;
}

void AbstractGraph::buildIntraEdges() {
    for(Cluster& cluster: clusters) {
        for(unsigned int start = 0; start < cluster.nodes.size(); start++) {
            for(unsigned int goal = start + 1; goal < cluster.nodes.size(); goal++ ) {
                buildEdge(*cluster.nodes.at(start), *cluster.nodes.at(goal), false);
            }
        }
    }
}

void AbstractGraph::connect(graphs::Vertex* vertex, Cluster& cluster) {
    for(auto goal: cluster.nodes) {
        if(vertex->getIndex() != goal->getIndex())
            buildEdge(*vertex, *goal, false);
    }
}

void AbstractGraph::insertStartAndGoal(const graphs::GridVertex& start, const graphs::GridVertex& goal) {
    removeStartAndGoal();

    unsigned int verts = this->getNrOfVertices();
    this->start = &this->fetchOrAddVertex(start.getX(), start.getY());
    newStart = this->getNrOfVertices() > verts;

    verts = this->getNrOfVertices();
    this->goal = &this->fetchOrAddVertex(goal.getX(), goal.getY());
    newGoal = this->getNrOfVertices() > verts;

    auto clusterPos = this->nodePositionToClusterPosition(start.getX(), start.getY());

    Cluster& startCluster = clusters.at(this->clusterPositionToIndex(clusterPos.first, clusterPos.second));
    std::cout << this->start->getIndex() << std::endl;
    if(newStart)
        connect(this->start, startCluster);

    clusterPos = this->nodePositionToClusterPosition(goal.getX(), goal.getY());

    Cluster& goalCluster = clusters.at(this->clusterPositionToIndex(clusterPos.first, clusterPos.second));
    if(newGoal)
        connect(this->goal, goalCluster);
}

void AbstractGraph::removeStartAndGoal() {
    if(start && newStart) {
        std::cout << "removing start" << std::endl;
        removeVertex(*start);
    }
    if(goal && newGoal) {
        std::cout << "removing goal" << std::endl;
        removeVertex(*goal);
    }

    start = goal = nullptr;
    newStart = newGoal = false;
}

void AbstractGraph::removeVertex(graphs::Vertex& vertex) {
    const graphs::GridVertex *baseVertex = this->abstractToBase.at(&vertex);

    std::cout << "removing (" << baseVertex->getX() << ", " << baseVertex->getY() << ")";

    auto clusterPos = nodePositionToClusterPosition(baseVertex->getX(), baseVertex->getY());
    std::cout << " from cluster " << clusterPositionToIndex(clusterPos.first, clusterPos.second) << std::endl;
    Cluster& cluster = clusters.at(clusterPositionToIndex(clusterPos.first, clusterPos.second));
    cluster.removeNode(vertex);

    Graph::removeVertex(vertex);
}
