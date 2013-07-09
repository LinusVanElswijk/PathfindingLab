#include "SearchManager.h"

SearchManager::SearchManager(QObject *parent) :
    QObject(parent)
{
}

void SearchManager::startSearchWorker()
{
   QThread* thread = new QThread;
   SearchWorker* worker = new SearchWorker(this);
   worker->moveToThread(thread);

   connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
   connect(thread, SIGNAL(started()), worker, SLOT(process()));
   connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
   connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
   connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

   thread->start();
}


void SearchManager::solveProblem(Problem &problem, const SearchAlgorithmType &searchAlgorithm) {
    switch(searchAlgorithm) {
        case SearchAlgorithmType::aStar:
            std::cout << "Solving with A*" << std::endl;
            break;
        case SearchAlgorithmType::thetaStar:
            std::cout << "Solving with Theta*" << std::endl;
            break;
        case SearchAlgorithmType::hpaStar:
            std::cout << "Solving with HPA*" << std::endl;
            break;
        case SearchAlgorithmType::hptStar:
            std::cout << "Solving with HPT*" << std::endl;
            break;
    }
}
