#ifndef TILE_MAP_FILE_H
#define TILE_MAP_FILE_H

#include <string>
#include <fstream>

#include "TileMap.h"

class TileMapFile
{
    public:
        TileMapFile()
        :filePath(""),
         type(""),
         tileMap(NULL)
        {

        }

        TileMapFile(std::string &filePath)
        :filePath(""),
         type(""),
         tileMap(NULL)
        {
            load(filePath);
            tileMap->rebuildGridGraph();
        }

        ~TileMapFile()
        {
            if(tileMap)
                delete tileMap;
        }

        void load(const std::string &filePath);
        //void save();
        //void saveAs(const std::string &filePath);

        bool isLoaded() const
        {
            return tileMap != NULL;
        }

        TileMap* getTileMap() {
            return tileMap;
        }

    private:
        std::string filePath;
        std::string type;

        TileMap* tileMap;

        void readFromStream(std::ifstream &inputStream);
        void readType(std::ifstream &inputStream);
        unsigned int readWidth(std::ifstream &inputStream);
        unsigned int readHeight(std::ifstream &inputStream);
        void readMap(std::ifstream &inputStream);
        void readTiles(std::ifstream &inputStream);
        void readTileRow(const unsigned int& row, std::ifstream &inputStream);

        void unload() const
        {
            if(tileMap != NULL)
            {
                delete tileMap;
            }
        }

};

#endif // TILE_MAP_FILE_H
