//
// Created by Hayden Donofrio on 9/10/18.
//

#ifndef LAB02_SEARCH_H
#define LAB02_SEARCH_H


#include "algorithm.h"
#include <vector>
#include <string>
#include "Node.h"
class search: public algorithm {
public:
    search() = default;
    ~search();
    void load(const char*, const char *, const char *);
    void execute(int, int);
    void display();
    void stats(std::list<int> finalPath,  unsigned int time ,int nodesExplored=0, double distance =0, double cost =0,std::string type = "");
    void select(int);
    void save(const char*);
    void configure();
    Node** cloneMatrix();
private:
    int matrixSize = 1;
    std::vector<std::vector<Node> > adjList;
    static algorithm::searches searchType;
    static std::string algoType;
    Node ** matrix;
};

#endif //LAB02_SEARCH_H
