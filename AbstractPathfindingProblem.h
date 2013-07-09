#ifndef ABSTRACTPATHFINDINGPROBLEM_H
#define ABSTRACTPATHFINDINGPROBLEM_H

#include <Problem.hpp>
#include <AbstractGraph.h>

class AbstractPathfindingProblem: public searchAlgorithms::Problem<graphs::Vertex, graphs::Edge, graphs::Real>
{
public:
    AbstractPathfindingProblem(const graphs::Vertex& initialState, const graphs::Vertex& goalState, AbstractGraph* graph)
    :Problem(initialState, goalState),
     graph(graph)
    {

    }

    virtual ~AbstractPathfindingProblem() {

    }

    virtual std::list<ActionAndResult> getSuccessors(const graphs::Vertex& vertex) const
    {
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
    virtual graphs::Real actionCost(const graphs::Vertex& state, const graphs::Edge& action) const {
        return action.cost;
    }
    #pragma GCC diagnostic pop

protected:
    AbstractGraph* const graph;
};

#endif // ABSTRACTPATHFINDINGPROBLEM_H
