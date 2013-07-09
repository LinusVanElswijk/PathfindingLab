#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <cmath>
#include <vector>
#include <GridGraph.hpp>
#include <AbstractGraph.h>

/**
 * Class that represents a map
 */
class TileMap
{
    public:
    typedef typename std::vector<bool>::size_type uint;
    typedef typename std::vector<bool>::reference reference;
    typedef typename std::vector<bool>::const_reference constReference;

    // Constructors & assignment


        /**
         * Default constructor for a map
         */
        TileMap()
        :width(0),
         height(0),
         tile(0),
         gridGraph(nullptr),
         abstractGraph(nullptr)
        { }

        TileMap( const uint& x, const uint& y
               )
        :width(x),
         height(y),
         tile(x * y),
         gridGraph(nullptr),
         abstractGraph(nullptr)
        { }

        /**
         * Copy-constructor for a map
         * @param[in] The map to copy
         */
        TileMap( const TileMap& sourceMap
               )
        :width(sourceMap.width),
         height(sourceMap.height),
         tile(sourceMap.tile),
         gridGraph(nullptr),
         abstractGraph(nullptr)
        { }

        TileMap& operator= (const TileMap& otherMap);

   // Data access

        reference operator() (const uint& x, const uint& y)
        {
            return tile.at(coordinatesToIndex(x,y));
        }

        constReference operator() (const uint& x, const uint& y) const
        {
            return tile.at(coordinatesToIndex(x,y));
        }

        reference operator() (const uint& index)
        {
            return tile.at(index);
        }

        constReference operator() (const uint& index) const
        {
            return tile.at(index);
        }

        /**
         * Gives the width of the map
         * @return the map width
         */
        uint getWidth() const
        {
            return width;
        }

        /**
         * Gives the height of the map
         * @return the map height
         */
        uint getHeight() const
        {
            return height;
        }

        /**
         * Gives the number of tiles on the map
         * @return the number of tiles on the map
         */
        uint getSize() const
        {
            return width * height;
        }

   // Index & coordinate conversions

        uint indexToXCoordinate(const uint& index) const
        {
            return index % width;
        }

        uint indexToYCoordinate(const uint& index) const
        {
            return index / width;
        }

        uint coordinatesToIndex(const uint& x, const uint& y) const
        {
            return y * width + x;
        }

        const graphs::GridGraph* getGraph() const {
            return gridGraph;
        }

        AbstractGraph* getAbstractGraph() {
            return abstractGraph;
        }

        const AbstractGraph* getAbstractGraph() const {
            return abstractGraph;
        }

    public:

        void rebuildGridGraph() {
            if(gridGraph != NULL) {
                delete gridGraph;
            }

            gridGraph = new graphs::GridGraph(width+1, height+1, graphs::GridGraph::UNCONNECTED);

            buildEdges();

            rebuildAbstractMap();
        }

    private:

        void buildEdges() {
            for(unsigned int x = 0; x < gridGraph->getWidth(); x++){
                for(unsigned int y = 0; y < gridGraph->getHeight(); y++) {
                    if( horizontalEdgeAllowed(x,y) ) {
                        gridGraph->addBidirectionalEdge(gridGraph->getVertex(x,y), gridGraph->getVertex(x-1,y), STRAIGHT_COST);
                    }

                    if( verticalEdgeAllowed(x,y) ) {
                        gridGraph->addBidirectionalEdge(gridGraph->getVertex(x,y), gridGraph->getVertex(x,y-1), STRAIGHT_COST);
                    }

                    if( diagonalsAllowed(x,y)) {
                        gridGraph->addBidirectionalEdge(gridGraph->getVertex(x,y), gridGraph->getVertex(x-1, y-1), DIAGONAL_COST);
                        gridGraph->addBidirectionalEdge(gridGraph->getVertex(x-1,y), gridGraph->getVertex(x, y-1), DIAGONAL_COST);
                    }
                }
            }
        }

        bool horizontalEdgeAllowed(unsigned int x, unsigned int y) {
            return(!(blocked(x-1,y) && blocked(x-1,y-1)));
        }

        bool verticalEdgeAllowed(unsigned int x, unsigned int y) {
            return(!(blocked(x,y-1) & blocked(x-1,y-1)));
        }

        bool diagonalsAllowed(unsigned int x, unsigned int y) {
            return(!blocked(x-1,y-1));
        }

        bool blocked(int x, int y) {
            if(x < 0 || y < 0 || (long)x >= (long)width || (long)y >= (long)height)
                return true;
            else
                return ((*this)(x,y));
        }

        void rebuildAbstractMap() {
            if(abstractGraph) {
                delete abstractGraph;
            }

            abstractGraph = new AbstractGraph(*gridGraph);
        }

    private:
        /**
         * The width/height of the map
         */
        uint width, height;

        /**
         * The tile data of the maps where the data for
         * tile (x, y) is stored on position y * width + x;
         */
        std::vector<bool> tile;

        /**
         * The gridGraph corresponding to the tilemap.
         */
        graphs::GridGraph *gridGraph;
        AbstractGraph *abstractGraph;

        static const double STRAIGHT_COST, DIAGONAL_COST;
};

#endif //TILE_MAP_H
