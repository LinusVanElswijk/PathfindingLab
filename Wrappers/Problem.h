#ifndef PROBLEM_H
#define PROBLEM_H

#include <QPoint>
#include "TileMap.h"

class Problem
{
    public:
        explicit Problem(const QPoint& from, const QPoint& to, TileMap& tileMap);

        QPoint initialState() const;

        QPoint goalState() const;

        TileMap& map();

    private:
        QPoint fromState,toState;
        TileMap& tileMap;
};

#endif // PROBLEM_H
