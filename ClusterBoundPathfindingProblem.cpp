#include "ClusterBoundPathfindingProblem.h"

std::list<ClusterBoundPathfindingProblem::ActionAndResult> ClusterBoundPathfindingProblem::getSuccessors(const graphs::GridVertex& state) const
{
    const graphs::GridVertex& vertex = graph->getVertex(state.getX(), state.getY());

    const std::list<graphs::ConstEdgePtr>&& edges = vertex.getOutgoingEdges();
    std::list<ActionAndResult> successors;

    auto cluster = abstractGraph->nodePositionToClusterPosition(state.getX(), state.getY());

    for(auto edge : edges)
    {
        auto& vertex = graph->getVertex(edge->toIndex);

        if(abstractGraph->nodePositionToClusterPosition(vertex.getX(), vertex.getY()) == cluster) {
            successors.emplace_back(*edge,vertex);
        }
    }

    return successors;
}
