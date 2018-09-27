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
    int searched = 1;
    int matrixSize;
    std::vector<int> finalPath;
    std::queue<int> bfsQueue;
    std::vector<std::list<int> > path;
    std::vector<int>searchSize;
    int officialStart = 0;
};


#endif //LAB02_BFS_H
