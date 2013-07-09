#ifndef TASKRUNNER_H
#define TASKRUNNER_H

#include <Solution.hpp>
#include <AStar.hpp>
#include <ThetaStar.hpp>
#include <BreadthFirstSearch.h>

#include "DistanceFunctions.h"
#include "VertexHash.h"

#include "QGraphicsTileMapScene.h"
#include "pathfindingproblem.h"
#include "Task.h"
#include "DDALineOfSight.hpp"

#include "AbstractPathfindingProblem.h"

#include <time.h>

#include "NodeListeners.hpp"

class TaskRunner: public searchAlgorithms::NodeVisitListener<PathfindingProblem>,
                         searchAlgorithms::NodeExpansionListener<PathfindingProblem>,
                         searchAlgorithms::NodeClosureListener<PathfindingProblem>,
                         searchAlgorithms::NodePushListener<PathfindingProblem>,
                         searchAlgorithms::NodePopListener<PathfindingProblem>,
                         searchAlgorithms::NodeUpdateListener<PathfindingProblem>
{
    public:
        typedef typename searchAlgorithms::NodeVisitListener<PathfindingProblem>::NodeType Node;

        TaskRunner(QGraphicsTileMapScene& scene)
        :scene(scene),
         maxEval(),
         distanceFunction(nullptr),
         lineOfSight(nullptr),
         visits()
        {

        }

        virtual void onNodeVisited(const typename Node::ConstPtr& node);

        virtual void onNodeExpanded(const typename Node::ConstPtr& node)
        { }

        virtual void onNodeClosed(const typename Node::ConstPtr& node)
        { }

        virtual void onNodePushed(const typename Node::ConstPtr& node);

        virtual void onNodePopped(const typename Node::ConstPtr& node)
        { }

        virtual void onNodeUpdated(const typename Node::ConstPtr& oldNodeValue, const typename Node::ConstPtr& newNodeValue)
        { }

        virtual void run(const SearchTask& task,  TileMap &tileMap);


    private:
        std::shared_ptr<AbstractPathfindingProblem> toProblem(const SearchTask& task, TileMap& tileMap);

        QGraphicsTileMapScene& scene;

        graphs::Real evaluation(const typename Node::ConstPtr& node, const searchAlgorithms::HeuristicFunction<graphs::GridVertex, graphs::Real> &heuristic);

        graphs::Real getRelativeEvaluation(const typename Node::ConstPtr& node, const searchAlgorithms::HeuristicFunction<graphs::GridVertex, graphs::Real> &heuristic);

        graphs::Real maxEval;

        searchAlgorithms::HeuristicFunction<graphs::GridVertex, graphs::Real>* distanceFunction;
        searchAlgorithms::LineOfSightFunction<PathfindingProblem>* lineOfSight;

        unsigned int visits;
};

#endif // TASKRUNNER_H
