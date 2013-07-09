#ifndef PATHFINDINGPROBLEM_H
#define PATHFINDINGPROBLEM_H

#include <Problem.hpp>

#include <GridGraph.hpp>
#include <QPoint>

class PathfindingProblem: public searchAlgorithms::Problem<graphs::GridVertex, graphs::Edge, graphs::Real>
{   
    public:
        PathfindingProblem(const graphs::GridVertex& initialState, const graphs::GridVertex& goalState, const graphs::GridGraph* graph)
        :Problem(initialState, goalState),
         graph(graph)
        {

        }

        virtual ~PathfindingProblem() {

        }

        virtual std::list<ActionAndResult> getSuccessors(const graphs::GridVertex& state) const
        {
            const graphs::GridVertex& vertex = graph->getVertex(state.getX(), state.getY());

            const std::list<graphs::ConstEdgePtr>&& edges = vertex.getOutgoingEdges();
            std::list<ActionAndResult> successors;

            for(auto edge : edges)
            {
                auto& vertex = graph->getVertex(edge->toIndex);

                successors.emplace_back(*edge,vertex);
            }

            return successors;
        }

        #pragma GCC diagnostic ignored "-Wunused-parameter"
        virtual graphs::Real actionCost(const graphs::GridVertex& state, const graphs::Edge& action) const {
            return action.cost;
        }
        #pragma GCC diagnostic pop

    protected:
        const graphs::GridGraph* const graph;

};
/*
class QPointHasher
: std::unary_function<const QPoint*, std::size_t>
{
    public:
        std::size_t operator() (const QPoint* const& point) const
        {
            return point->x() ^ point->y();
        }
};
*/
#endif // PATHFINDINGPROBLEM_H
