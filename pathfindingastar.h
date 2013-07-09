#ifndef PATHFINDINGASTAR_H
#define PATHFINDINGASTAR_H

#include <AStar.hpp>

class PathFindingAStar : public searchAlgorithm::AStar<Position, Position, double>
{
    public:
        PathFindingAStar();
};

#endif // PATHFINDINGASTAR_H
