#ifndef DDALINEOFSIGHT_HPP
#define DDALINEOFSIGHT_HPP

#include <AbstractPathfindingProblem.h>
#include <QGraphicsTileMapScene.h>
#include <LineOfSightFunction.hpp>
#include <GridVertex.hpp>
#include <TileMap.h>
#include <pathfindingproblem.h>


class DDALineOfSight: public searchAlgorithms::LineOfSightFunction<PathfindingProblem>
{
public:
    DDALineOfSight(const TileMap& map)
    :map(map)
    {   }

    virtual LineOfSightFunction* clone() const {
        return new DDALineOfSight(map);
    }

    virtual std::pair<std::shared_ptr<graphs::Edge>, graphs::Real> operator() (const graphs::GridVertex& stateA, const graphs::GridVertex& stateB) const {


        if(hasLineOfSight(stateA, stateB)) {
            int dx = stateA.getX() - stateB.getX(),
                dy = stateB.getY() - stateB.getY();

            graphs::Real distance = sqrt(dx * dx + dy * dy);

            std::shared_ptr<graphs::Edge> edge(new graphs::Edge(stateA.getIndex(), stateB.getIndex(), distance));
            return std::pair<std::shared_ptr<graphs::Edge>, graphs::Real>(edge, edge->cost);

            std::cout << "called" << std::endl;
        }

        return std::pair<std::shared_ptr<graphs::Edge>, graphs::Real>(nullptr, 0);
    }

    virtual bool hasLineOfSight(const graphs::GridVertex& stateA, const graphs::GridVertex& stateB) const {
        RunData data(stateA, stateB);

        if(data.xDir == 0 && data.yDir == 0) return true;

        bool lineOfSight;

        do {
            lineOfSight = free(data);
        }
        while(next(data) && lineOfSight);

        return lineOfSight;
    }

private:
    struct RunData {
        RunData(const graphs::GridVertex& stateA, const graphs::GridVertex& stateB)
        :x(stateA.getX()),
         y(stateA.getY()),
         xEnd(stateB.getX()),
         yEnd(stateB.getY()),
         xDir(DDALineOfSight::sign(xEnd - x)),
         yDir(DDALineOfSight::sign(yEnd - y)),
         slope(double(yEnd - y)/double(xEnd - x)),
         climb(0.0),
         primary(slope <= 1 ? x : y),
         secondary(slope <= 1 ? y : x),
         primaryDir(slope <= 1 ? xDir : yDir),
         secondaryDir(slope <= 1 ? yDir : xDir)
        {
            if(slope > 1)
                slope = 1 / slope;
        }

        int x,
            y;

        const int xEnd,
                  yEnd,
                  xDir,
                  yDir;

        double slope;
        double climb;

        int &primary, &secondary;
        const int &primaryDir, &secondaryDir;
    };

    bool next(RunData& data) const {
        if( data.climb + fabs(data.slope) > 1.0 ) {
            data.secondary += data.secondaryDir;
            data.climb -= 1.0;
        }
        else if(data.climb + fabs(data.slope) == 1.0) {
            data.climb -= 1.0;
            data.primary += data.primaryDir;
            data.secondary += data.secondaryDir;
            data.climb += fabs(data.slope);
        }
        else {
            data.primary += data.primaryDir;
            data.climb += fabs(data.slope);
        }

        return !reachedEnd(data);
    }

    bool reachedEnd(const RunData& data) const {
        if(data.xDir != 0 && data.yDir != 0)
            return (reachedY(data) || reachedX(data));
        else if(data.xDir == 0)
            return reachedY(data);
        else
            return reachedX(data);
    }

    bool reachedX(const RunData& data) const {
        return reached(data.x, data.xEnd, data.xDir);
    }

    bool reachedY(const RunData& data) const {
        return reached(data.y, data.yEnd, data.yDir);
    }

    bool reached(const int& start, const int& end, const int& dir) const {
        return (dir >= 0 ? start >= end : start <= end);
    }

    bool free(const RunData& data) const {
        int x = data.x,
            y = data.y;

        if(data.yDir < 0)
            y--;
        if(data.xDir < 0)
            x--;

        if(data.xDir == 0) {
            return !(mapCheck(x,y) && mapCheck(x-1,y));
        }
        if(data.yDir == 0) {
            return !(mapCheck(x,y) && mapCheck(x, y-1));
        }

        return !mapCheck(x,y);
    }

    bool mapCheck(const int& x, const int& y) const {
        if(x < 0 || y < 0 || x >= (long)map.getWidth() || y >= (long)map.getHeight())
            return false;

       return map(x,y);
    }

    static int sign(const int& value) {
        return (value > 0) - (value < 0);
    }

protected:
    const TileMap& map;
};

class HPADDALineOfSight: public searchAlgorithms::LineOfSightFunction<AbstractPathfindingProblem>, private DDALineOfSight {

public:
    HPADDALineOfSight(const TileMap& map)
    :DDALineOfSight(map)
    {   }

    virtual HPADDALineOfSight* clone() const {
        return new HPADDALineOfSight(this->map);
    }

    virtual std::pair<std::shared_ptr<graphs::Edge>, graphs::Real> operator() (const graphs::Vertex& stateA, const graphs::Vertex& stateB) const {

        auto &baseA = map.getAbstractGraph()->toBase(stateA),
             &baseB = map.getAbstractGraph()->toBase(stateB);

        return DDALineOfSight::operator ()(baseA,baseB);
    }
};

#endif // DDALINEOFSIGHT_HPP
