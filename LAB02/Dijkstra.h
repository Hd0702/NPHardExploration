//
// Created by Hayden Donofrio on 9/10/18.
//

#ifndef LAB02_DIJKSTRA_H
#define LAB02_DIJKSTRA_H
#include <vector>
#include <list>
#include "search.h"

class Dijkstra: public search {
    Dijkstra(std::vector<std::list<int> > &, int **);
    void execute(std::vector<std::list<int> >&, int**);
};


#endif //LAB02_DIJKSTRA_H
