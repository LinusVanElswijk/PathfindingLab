#ifndef ASTARWORKER_H
#define ASTARWORKER_H

#include "SearchWorker.h"
#include "AStar.hpp"

class AStarWorker : public SearchWorker
{
    public:
        explicit AStarWorker(QObject* parent);

    public slots:
        void process();

    signals:
        void finished();
        void error(QString err);

    private:

        // add your variables here

};

#endif // ASTARWORKER_H
