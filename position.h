#ifndef POSITION_H
#define POSITION_H

#include <cmath>
#include <boost/unordered_map.hpp>

class Position
{
    public:
        Position()
        :x(0),y(0)
        {}

        Position(const double& x, const double& y)
        :x(x),y(y)
        { }

        double x, y;

        bool operator== (const Position& otherPosition) const
        {
            return this->x == otherPosition.x && this->y == otherPosition.y;
        }

        bool operator!=  (const Position& otherPosition) const
        {
            return !(*this == otherPosition);
        }
};

double squareDistance(const Position& positionA, const Position& positionB);

double distance(const Position& positionA, const Position& positionB);

/*
    template<typename precision>
    class PositionHash: public std::unary_function< Position<precision>, std::size_t>
    {
        public:
            std::size_t operator () (const Position<precision>& position) const;
    };
*/

/*
    template<typename precision>
    Position<precision>::Position()
    :x((precision)0),
     y((precision)0)
    { }

    template<typename precision>
    Position<precision>::Position(const precision& x, const precision& y)
    :x(x),
     y(y)
    { }

    template<typename precision>
    std::size_t PositionHash<precision>::operator()(const Position<precision>& position) const
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, position.x);
        boost::hash_combine(seed, position.y);
        return seed;
     }

}
}
*/
#endif
