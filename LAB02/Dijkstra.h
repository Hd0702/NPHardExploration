//
// Created by Hayden Donofrio on 9/10/18.
//

#ifndef LAB02_DIJKSTRA_H
#define LAB02_DIJKSTRA_H
#include <vector>
#include "search.h"

class Dijkstra: public search {
public:
    Dijkstra(std::vector<std::vector<Node> > adjList, Node **matrix, int start, int end, int size);

    void executeList(std::vector<std::vector<Node> > adjList, int start, int end);

    void executeMatrix(Node **matrix, int start, int end);

private:
    int matrixSize;
};


#endif //LAB02_DIJKSTRA_H
