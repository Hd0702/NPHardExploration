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
    struct item {
        int data;
        double distance;
        int x; //only used for calculating distance
        int y;
        int z;
        int weight;
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
    std::vector<std::vector<item> > adjList;
    algorithm::searches searchType;
    int ** matrix;
};

#endif //LAB02_SEARCH_H
