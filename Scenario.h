#ifndef SCENARIO_H
#define SCENARIO_H

#include <vector>
#include <utility>

#include "pathfindingproblem.h"
#include "position.h"

class Scenario: public std::vector< std::pair<Position, Position> >
{
    public:
        Scenario();

};

#endif // SCENARIO_H
