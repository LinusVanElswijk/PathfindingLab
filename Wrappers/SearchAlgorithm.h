#ifndef SEARCHALGORITHM_H
#define SEARCHALGORITHM_H

#include "Problem.h"

class SearchAlgorithm
{
public:
    explicit SearchAlgorithm();

    void operator ()(Problem& problem);
};

#endif // SEARCHALGORITHM_H
