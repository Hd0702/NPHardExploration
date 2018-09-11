//
// Created by Hayden Donofrio on 9/10/18.
//

#ifndef LAB02_A_H
#define LAB02_A_H
#include <vector>
#include <list>
#include "search.h"

class A: public search {
    A(std::vector<std::list<int> > &, int **);
    void execute(std::vector<std::list<int> >&, int**);
};


#endif //LAB02_A_H
