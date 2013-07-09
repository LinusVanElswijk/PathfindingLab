#ifndef EUCLIDEANDISTANCEFUNCTION_H
#define EUCLIDEANDISTANCEFUNCTION_H

#include "HeuristicFunction.hpp"
#include <GridGraph.hpp>
#include <math.h>
#include <AbstractGraph.h>

class AbstractGraph;

class EuclideanDistanceFunction: public searchAlgorithms::HeuristicFunction<graphs::GridVertex, graphs::Real>
{
public:

    EuclideanDistanceFunction(const graphs::GridVertex& goalState)
    :goalState(goalState)
    {   }

    virtual ~EuclideanDistanceFunction()
    {
    }

    virtual EuclideanDistanceFunction* clone() const {
        return new EuclideanDistanceFunction(goalState);
    }

    virtual double operator() (const graphs::GridVertex& state) const {
        long dx = goalState.getX() - state.getX(),
             dy = goalState.getY() - state.getY();

        return sqrt(dx * dx + dy * dy);
    }

private:
    const graphs::GridVertex& goalState;
};

class TileDistanceFunction: public searchAlgorithms::HeuristicFunction<graphs::GridVertex, graphs::Real>
{
public:

    TileDistanceFunction(const graphs::GridVertex& goalState)
    :goalState(goalState)
    {   }

    virtual ~TileDistanceFunction()
    {
    }

    virtual TileDistanceFunction* clone() const {
        return new TileDistanceFunction(goalState);
    }

    virtual double operator() (const graphs::GridVertex& state) const {
        long dx = std::abs(long(goalState.getX()) - long(state.getX())),
             dy = std::abs(long(goalState.getY()) - long(state.getY()));

        return std::min(dx, dy) * sqrt(2.0) + (std::max(dx, dy) - std::min(dx,dy));
    }

private:
    const graphs::GridVertex& goalState;
};

class AbstractTileDistanceFunction: public searchAlgorithms::HeuristicFunction<graphs::Vertex, graphs::Real>
{
public:

    AbstractTileDistanceFunction(const graphs::Vertex& goalState, const AbstractGraph &graph);

    virtual ~AbstractTileDistanceFunction();

    virtual AbstractTileDistanceFunction* clone() const;

    virtual double operator() (const graphs::Vertex& state) const;

private:
    TileDistanceFunction tileDistanceFunction;
    const graphs::Vertex& goalState;
    const AbstractGraph &graph;
};


#endif // EUCLIDEANDISTANCEFUNCTION_H
