#ifndef ASTAR_H
#define ASTAR_H

#include "SearchAlgorithm.h"
#include "AStar.hpp"

class AStar : public SearchAlgorithm
{
public:
    AStar();

    operator ()(Problem& problem);

private:
    TileDistanceFunction heuristic;
};

#endif // ASTAR_H
