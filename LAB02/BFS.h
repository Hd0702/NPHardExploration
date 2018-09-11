//
// Created by Hayden Donofrio on 9/10/18.
//

#ifndef LAB02_BFS_H
#define LAB02_BFS_H
#include <vector>
#include <list>
#include "search.h"

class BFS: public search {
    BFS(std::vector<std::list<int> > &, int **);
    void execute(std::vector<std::list<int> >&, int**);
};


#endif //LAB02_BFS_H
