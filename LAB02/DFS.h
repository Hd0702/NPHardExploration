//
// Created by Hayden Donofrio on 9/10/18.
//

#ifndef LAB02_DFS_H
#define LAB02_DFS_H
#include <vector>
#include "search.h"

class dfs: public search {
public:
    dfs(std::vector<std::vector<Node> > , Node **, int, int, int);
    void executeIterativeList(std::vector<std::vector<Node> >, int, int);
    void executeIterativeMatrix(Node **, int, int);
    //TODO:Reset vector to refrece and create clones
    void executeRecursiveList(std::vector<std::vector<search::Node> >, int , int);
    void executeRecrusiveMatrix(Node **, int , int);
private:
int matrixSize = 0;
};


#endif //LAB02_DFS_H
