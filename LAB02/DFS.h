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
    DFS(std::vector<std::vector<Node> >& , Node **, int, int, int);
    void executeIterativeList(std::vector<std::vector<Node> >, int, int);
    void executeIterativeMatrix(Node **, int, int);
    void executeRecursiveList(std::vector<std::vector<search::Node> >, int , int);
    void executeRecrusiveMatrix(Node **, int , int);
private:
int matrixSize = 0;
};


#endif //LAB02_DFS_H
