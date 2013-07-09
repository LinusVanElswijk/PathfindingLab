#include "ScenarioFile.h"

void ScenarioFile::load(const std::string &filePath) {
    using std::ifstream;
    using std::string;

    std::cout << "loading " << filePath << std::endl;

    ifstream inputStream(filePath.c_str(), ifstream::in);
    /*
    if( inputStream.fail() )
    {
        throw exceptions::FileAccessException(fileName);
    }
    */
    if(scenario) {
        delete scenario;
    }

    scenario = new Scenario();

    readFromStream(inputStream);

    this->filePath = filePath;
}

void ScenarioFile::readFromStream(std::ifstream &inputStream) {
    using std::string;

    string dump;
    getline(inputStream, dump);

    std::cout << dump << std::endl;

    while(inputStream.good()) // To get you all the lines.
    {
        string a,b,c,d;

        unsigned int startX, startY, endX, endY;
        float best;

        if(inputStream >> a >> b >> c >> d >> startX >> startY >> endX >> endY >> best)
        {
            char endLine;
            inputStream.get(endLine);
            /*
            std::cout << a      << ' '
                      << b      << ' '
                      << c      << ' '
                      << d      << ' '
                      << startX << ' '
                      << startY << ' '
                      << endX   << ' '
                      << endY   << ' '
                      << best   << std::endl;
            */
            scenario->push_back( std::pair<Position, Position>(Position(startX, startY), Position(endX, endY)) );
        }
    }

    std::cout << "nr of tasks: " << scenario->size() << std::endl;
}
