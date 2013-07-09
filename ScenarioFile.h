#ifndef SCENARIOFILE_H
#define SCENARIOFILE_H

#include <string>
#include <fstream>
#include <iostream>

#include "Scenario.h"

class ScenarioFile
{
public:
    ScenarioFile()
    :filePath(""),
     scenario(NULL)
    {

    }

    ScenarioFile(std::string &filePath)
    :filePath(""),
     scenario(NULL)
    {
        load(filePath);
    }

    ~ScenarioFile()
    {
        if(scenario)
            delete scenario;
    }

    void load(const std::string &filePath);
    //void save();
    //void saveAs(const std::string &filePath);

    bool isLoaded() const
    {
        return false;
    }

    Scenario* getScenario() {
        return scenario;
    }

private:
    std::string filePath;
    Scenario* scenario;


    void readFromStream(std::ifstream &inputStream);

    void unload() const
    {
    }

};

#endif // SCENARIOFILE_H
