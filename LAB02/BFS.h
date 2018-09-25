//
// Created by Hayden Donofrio on 9/10/18.
//

#ifndef LAB02_BFS_H
#define LAB02_BFS_H
#include <vector>
#include "search.h"
#include <queue>

class bfs: public search {
public:
    bfs(std::vector<std::vector<Node> > , Node **, int, int, int);
    void executeIterativeList(std::vector<std::vector<Node> >, int, int);
    void executeIterativeMatrix(Node **, int, int);
    void executeRecursiveList(std::vector<std::vector<Node> >&, std::queue<int> & , int);
    void executeRecrusiveMatrix(Node **, std::queue<int>& , int);
private:
    int matrixSize = 0;
    int searched = 1;
    std::list<int> finalPath;
    std::queue<int> bfsQueue;
    int officialStart = 0;
};


#endif //LAB02_BFS_H
