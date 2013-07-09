#include "DistanceFunctions.h"


AbstractTileDistanceFunction::AbstractTileDistanceFunction(const graphs::Vertex& goalState, const AbstractGraph &graph)
:tileDistanceFunction(graph.toBase(goalState)),
 goalState(goalState),
 graph(graph)
{   }

AbstractTileDistanceFunction::~AbstractTileDistanceFunction()
{   }

AbstractTileDistanceFunction* AbstractTileDistanceFunction::clone() const {
    return new AbstractTileDistanceFunction(goalState, graph);
}


double AbstractTileDistanceFunction::operator() (const graphs::Vertex& state) const {
    auto &baseState     = graph.toBase(state),
         &baseGoalState = graph.toBase(goalState);

    long dx = std::abs(long(baseGoalState.getX()) - long(baseState.getX())),
         dy = std::abs(long(baseGoalState.getY()) - long(baseState.getY()));

    return std::min(dx, dy) * sqrt(2.0) + (std::max(dx, dy) - std::min(dx,dy));
}
