#include "TaskRunner.h"

void TaskRunner::run(const SearchTask& task,  TileMap& tileMap) {
    tileMap.getAbstractGraph()->clearNodesAndMem();
    auto problem = toProblem(task, tileMap);


    visits = tileMap.getAbstractGraph()->getNumberOfVisits();
    unsigned int maxMemoryNodes = tileMap.getAbstractGraph()->getMaxNodesInMemory();

    //visits = 0;
    //unsigned int maxMemoryNodes = 0;

    std::cout << "In inserting goal and start: visits=" << visits << " mem=" << maxMemoryNodes << std::endl;

    scene.clearPathEdges();

    //TileDistanceFunction heuristicFunction(problem->goalState());
    //EuclideanDistanceFunction heuristicFunction(problem->goalState());
    AbstractTileDistanceFunction heuristicFunction(problem->goalState(), *tileMap.getAbstractGraph());

    lineOfSight = new DDALineOfSight(tileMap);
    //lineOfSight = new HPADDALineOfSight(tileMap);

    HPADDALineOfSight hpaLineOfSight(tileMap);
    //distanceFunction = &heuristicFunction;
    maxEval = 0.0;



    //searchAlgorithms::AStar<PathfindingProblem, VertexHash> aStar(heuristicFunction);
    //searchAlgorithms::ThetaStar<PathfindingProblem, VertexHash> aStar(heuristicFunction, *lineOfSight);

    searchAlgorithms::AStar<AbstractPathfindingProblem, VertexHash> aStar(heuristicFunction);
    //searchAlgorithms::ThetaStar<AbstractPathfindingProblem, VertexHash> aStar(heuristicFunction, hpaLineOfSight);

    //aStar.addNodeVisitListener(*this);
    //aStar.addNodePushListener(*this);
    clock_t begin = clock();
    std::shared_ptr<searchAlgorithms::Solution<AbstractPathfindingProblem>> sol = aStar(*problem);
    //std::shared_ptr<searchAlgorithms::Solution<PathfindingProblem>> sol = aStar(*problem);
    clock_t end = clock();

    std::cout << "actual run visits " << aStar.getNrOfVisits() << " nodes " << aStar.getMaxNodesInMemory() << std::endl;

    visits += aStar.getNrOfVisits();

    if(aStar.getMaxNodesInMemory() > maxMemoryNodes)
    maxMemoryNodes = aStar.getMaxNodesInMemory();

    std::cout << "Full run: visits=" << visits << " mem=" << maxMemoryNodes << std::endl;

    double timeSpend = (double)(end - begin) / CLOCKS_PER_SEC;

    /*
    if(sol != nullptr) {
        std::cout << "Solution : " << sol->getNumberOfActions() << " steps, with cost " << sol->getCost() << "." << std::endl;

        for(int i = 0; i < sol->getNumberOfStates(); i++) {
            const graphs::GridVertex& vert = sol->getState(i);
            scene.setPath(vert.getX(),vert.getY());
        }

        for(int i = 0; i < sol->getNumberOfActions(); i++) {
            const graphs::GridVertex& from = sol->getState(i);
            const graphs::GridVertex& to = sol->getState(i+1);

            scene.addPathEdge(from.getX(), from.getY(), to.getX(), to.getY());
        }
    }*/
    if(sol != nullptr) {
        std::cout << "Solution : " << sol->getNumberOfActions() << " steps, with cost " << sol->getCost() << "." << std::endl;

        for(int i = 0; i < sol->getNumberOfStates(); i++) {
            const graphs::GridVertex& vert = tileMap.getAbstractGraph()->toBase(sol->getState(i));
            scene.setPath(vert.getX(),vert.getY());
        }

        for(int i = 0; i < sol->getNumberOfActions(); i++) {
            const graphs::GridVertex& from = tileMap.getAbstractGraph()->toBase(sol->getState(i));
            const graphs::GridVertex& to = tileMap.getAbstractGraph()->toBase(sol->getState(i+1));

            scene.addPathEdge(from.getX(), from.getY(), to.getX(), to.getY());
        }
    }
    else
        std::cout << "No Solution" << std::endl;

    std::cout << "nodes/second = " << visits / timeSpend << std::endl;

    delete lineOfSight;
    lineOfSight = nullptr;
    distanceFunction = nullptr;
}

std::shared_ptr<AbstractPathfindingProblem> TaskRunner::toProblem(const SearchTask& task, TileMap& tileMap) {
    const QPoint *startPoint = task.getStart(),
                 *goalPoint  = task.getGoal();

    scene.clearVisited();

    auto &startVertex = tileMap.getGraph()->getVertex(startPoint->x(), startPoint->y()),
         &goalVertex  = tileMap.getGraph()->getVertex(goalPoint->x(), goalPoint->y());

    tileMap.getAbstractGraph()->insertStartAndGoal(startVertex, goalVertex);
    auto &abstractStart = tileMap.getAbstractGraph()->toAbstract(startVertex),
            &abstractGoal = tileMap.getAbstractGraph()->toAbstract(goalVertex);


    //return std::shared_ptr<PathfindingProblem>(new PathfindingProblem(startVertex, goalVertex, tileMap.getGraph()));
    return std::shared_ptr<AbstractPathfindingProblem>(new AbstractPathfindingProblem(abstractStart, abstractGoal, tileMap.getAbstractGraph()));
}

void TaskRunner::onNodeVisited(const typename Node::ConstPtr& node) {
    /*unsigned int x = node->getState().getX(),
                 y = node->getState().getY();

    scene.setVisited(x,y, getRelativeEvaluation(node, *distanceFunction) );
    scene.update();*/

    visits++;
}

void TaskRunner::onNodePushed(const typename Node::ConstPtr& node) {
    unsigned int x = node->getState().getX(),
                 y = node->getState().getY();

    scene.setExpanded(x,y);
    scene.update();
}


graphs::Real TaskRunner::getRelativeEvaluation(const typename Node::ConstPtr& node, const searchAlgorithms::HeuristicFunction<graphs::GridVertex, graphs::Real> &heuristic){
    if(maxEval == 0.0) {
        maxEval = evaluation(node, heuristic) * 1.25;
    }

    return evaluation(node, heuristic) / maxEval;
}

graphs::Real TaskRunner::evaluation(const typename Node::ConstPtr& node, const searchAlgorithms::HeuristicFunction<graphs::GridVertex, graphs::Real> &heuristic){
    return heuristic(node->getState());
}
