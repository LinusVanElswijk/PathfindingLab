#include "TileMapFile.h"

void TileMapFile::load(const std::string &filePath)
{
	using std::ifstream;
	using std::string;
		
    ifstream inputStream(filePath.c_str(), ifstream::in);
    /*
	if( inputStream.fail() )
	{
		throw exceptions::FileAccessException(fileName);
	}
    */
    readFromStream(inputStream);
	
	this->filePath = filePath;
}

void TileMapFile::readFromStream(std::ifstream &inputStream)
{
	readType(inputStream);
	unsigned int height = readHeight(inputStream);
	unsigned int width  = readWidth(inputStream);
	
	if(tileMap != NULL)
		delete tileMap;	
	tileMap = new TileMap(width, height);
	
    readMap(inputStream);
}

void TileMapFile::readType(std::ifstream &inputStream)
{
    using namespace std;

    string input;
    inputStream >> input;
    /*
    if( input.compare("type") != 0 )
    {
        throw MapLoadingException( this->fileName, exceptions::FileLoadingException::unexpectedStringMessage("type", input) );
    }
    */
    inputStream >> this->type;
}
	
unsigned int TileMapFile::readWidth(std::ifstream &inputStream)
{
    using namespace std;

    string input;
    inputStream >> input;
    /*
    if( input.compare("width") != 0 )
    {
        throw MapLoadingException( this->fileName, exceptions::FileLoadingException::unexpectedStringMessage("width", input) );
    }
    */
    unsigned int width;
    inputStream >> width;
    return width;
}

unsigned int TileMapFile::readHeight(std::ifstream &inputStream)
{
    using namespace std;

    string input;
    inputStream >> input;
    /*
    if( input.compare("height") != 0 )
    {
        throw MapLoadingException( this->fileName, exceptions::FileLoadingException::unexpectedStringMessage("height", input) );
    }
    */
    unsigned int height;
    inputStream >> height;
    return height;
}
	
void TileMapFile::readMap(std::ifstream &inputStream)
{
    using namespace std;

    string input;
    inputStream >> input;
    /*
    if( input.compare("map") != 0 )
    {
        throw MapLoadingException( this->fileName, exceptions::FileLoadingException::unexpectedStringMessage("map", input) );
    }
    */
    readTiles(inputStream);
}
	
void TileMapFile::readTiles(std::ifstream &inputStream)
{
    for(unsigned int row = 0; row < tileMap->getHeight(); row++)
    {
        char c;
        inputStream.get(c);
        /*
        if(c != '\n')
        {
            throw MapLoadingException( this->fileName, exceptions::FileLoadingException::unexpectedCharMessage('\n', c) );
        }
        */
        readTileRow(row, inputStream);
    }
}
	
void TileMapFile::readTileRow(const unsigned int& row, std::ifstream &inputStream)
{
    for(unsigned int column = 0; column < tileMap->getWidth(); column++)
    {
        char c;
        inputStream.get(c);

        switch(c)
        {
            case '.': case 'G': case 'S':
                (*tileMap)(column, row) = false;
                break;

            case '@': case 'O': case 'T': case 'W':
                (*tileMap)(column, row) = true;
                break;

            //default:
            //	throw MapLoadingException( this->fileName, exceptions::FileLoadingException::unexpectedCharMessage(".GS@OTW", c).c_str() );
        }
    }
}
