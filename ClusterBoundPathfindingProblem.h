#ifndef CLUSTERBOUNDPATHFINDINGPROBLEM_H
#define CLUSTERBOUNDPATHFINDINGPROBLEM_H

#include <pathfindingproblem.h>
#include <AbstractGraph.h>

class AbstractGraph;

class ClusterBoundPathfindingProblem : public PathfindingProblem
{
public:
    ClusterBoundPathfindingProblem( const graphs::GridVertex& initialState, const graphs::GridVertex& goalState,
                                    const graphs::GridGraph* baseGraph, const AbstractGraph* abstractGraph
                                  )
    :PathfindingProblem(initialState, goalState, baseGraph),
     abstractGraph(abstractGraph)
    {

    }

    virtual std::list<ActionAndResult> getSuccessors(const graphs::GridVertex& state) const;

protected:
    const AbstractGraph* abstractGraph;
};

#endif // CLUSTERBOUNDPATHFINDINGPROBLEM_H
