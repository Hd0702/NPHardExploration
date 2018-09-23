//
// Created by Hayden Donofrio on 9/10/18.
//

#ifndef LAB02_SEARCH_H
#define LAB02_SEARCH_H


#include "algorithm.h"
#include <vector>
#include <string>

class search: public algorithm {
public:
    struct Node {
        int data = 0;
        double distance= 0.0;
        double x= 0; //only used for calculating distances
        double y = 0;
        double z = 0;
        bool visited = false;
        int weight = 0;
        //TODO might want to add predecessor to node struct to return shortest path
        //we flip this operator so smaller shorter paths are at front of priority queue
        friend bool operator <(const Node & lhs, const Node & rhs){
            return (lhs.distance+ lhs.weight) > (rhs.distance + rhs.weight);
        }
    };
    search() = default;
    ~search();
    void load(const char*, const char *, const char *);
    void execute();
    void display();
    void stats(unsigned int);
    void select(int);
    void save(const char*);
    void configure();
private:
    int matrixSize = 0;
    std::vector<std::vector<Node> > adjList;
    algorithm::searches searchType;
    Node ** matrix;
};

#endif //LAB02_SEARCH_H
