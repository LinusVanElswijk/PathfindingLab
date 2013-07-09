#include "TileMap.h"

TileMap& TileMap::operator= (const TileMap& otherMap)
{
    if(&otherMap==this)
    {
        return *this;
    }

    this->width  = otherMap.width;
    this->height = otherMap.height;
    this->tile = otherMap.tile;

    return* this;
}

const double TileMap::STRAIGHT_COST = 1.0;
const double TileMap::DIAGONAL_COST = sqrt(2.0);
