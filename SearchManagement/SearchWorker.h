#ifndef SEARCH_WORKER_H
#define SEARCH_WORKER_H

#include <QObject>
#include "Wrappers/Problem.h"
#include "SearchAlgorithmTypes.hpp"

class SearchWorker : public QObject
{
    Q_OBJECT

public:
    explicit SearchWorker(Problem& problem, const SearchAlgorithmType& searchAlgorithm, QObject* parent);

public slots:
    virtual void process();

signals:
    virtual void finished();
    virtual void error(QString err);

private:
    // add your variables here
    
};

#endif // SEARCH_WORKER_H
