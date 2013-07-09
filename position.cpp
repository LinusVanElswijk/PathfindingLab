#include "position.h"

double squareDistance(const Position& positionA, const Position& positionB)
{
    const double DELTA_X = positionA.x - positionB.x,
                 DELTA_Y = positionA.y - positionB.y;

    return (DELTA_X * DELTA_X) + (DELTA_Y * DELTA_Y);
}

double distance(const Position& positionA, const Position& positionB)
{
    return std::sqrt(squareDistance(positionA, positionB));
}
