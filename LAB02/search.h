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
    //Search Type,Time,Start,End,Number of Nodes,Path,Distance,Total Nodes Visited
    //DFS Recursive,0,10,4,0.8125,10->6->2->1->5->9->13->14->15->11->7->3->4,0.245098,1,Adjacency List
    static std::vector<std::list<int> > finalPath;
    static std::vector<unsigned int> tTime ;
    static std::vector<int> nodesExplored;
    static std::string algoContainer;
    static std::vector<std::string> types;
    static std::vector<double> distance;
    static std::vector<double> cost;
    std::vector<std::vector<Node> > adjList;
    static algorithm::searches searchType;
    static std::string algoType;
    Node ** matrix;
};

#endif //LAB02_SEARCH_H
