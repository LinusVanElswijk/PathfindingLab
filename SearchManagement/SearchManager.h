#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H

#include <iostream>
#include <QObject>
#include <QThread>

#include "Wrappers/SearchAlgorithm.h"
#include "Wrappers/Problem.h"

#include "SearchAlgorithmTypes.hpp"
#include "SearchWorker.h"
#include "DDALineOfSight.hpp"

class SearchManager : public QObject
{
    Q_OBJECT

public:

    explicit SearchManager(QObject *parent = 0);

    void solveProblem(Problem& problem, const SearchAlgorithmType& searchAlgorithm);

signals:
    
public slots:

private:
    void startSearchWorker(Problem& problem, const SearchAlgorithmType& searchAlgorithm);
};

#endif // SEARCHMANAGER_H
