//
// Created by Hayden Donofrio on 9/10/18.
//

#ifndef LAB02_DFS_H
#define LAB02_DFS_H
#include <vector>
#include "search.h"
#include <list>
class dfs: public search {
public:
    dfs(std::vector<std::vector<Node> > , Node **, int, int,int);
    void executeIterativeList(std::vector<std::vector<Node> >, int, int);
    void executeIterativeMatrix(Node **, int, int);
    //TODO:Reset vector to refrece and create clones
    void executeRecursiveList(std::vector<std::vector<Node> >&, int , int, int);
    void executeRecrusiveMatrix(Node **, int , int, int);
private:
    std::vector<std::list<int> > finalPath;
    std::vector<int> distaces;
    std::vector<int>searchSize;
    int matrixSize = 0;
    std::vector<std::vector<int> > RecursivePaths;
    int officialStart = 0;
    int searched = 0;
};


#endif //LAB02_DFS_H
