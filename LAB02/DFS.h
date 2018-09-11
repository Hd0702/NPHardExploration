//
// Created by Hayden Donofrio on 9/10/18.
//

#ifndef LAB02_DFS_H
#define LAB02_DFS_H
#include <vector>
#include <list>
#include "search.h"

class DFS: public search {
public:
    DFS(std::vector<std::list<int> > &, int **);
    void execute(std::vector<std::list<int> >&, int**);
};


#endif //LAB02_DFS_H
