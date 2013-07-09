#include "Problem.h"

Problem::Problem(const QPoint& from, const QPoint& to, TileMap& tileMap)
:fromState(from),
 toState(to),
 tileMap(tileMap)
{
}

QPoint Problem::initialState() const {
    return fromState;
}

QPoint Problem::goalState() const {
    return toState;
}

TileMap& Problem::map() {
    return tileMap;
}
