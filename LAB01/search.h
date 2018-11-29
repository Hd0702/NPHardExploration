//
// Created by Hayden Donofrio on 9/10/18.
//

#ifndef LAB01_SEARCH_H
#define LAB01_SEARCH_H


#include "algorithm.h"
#include <vector>
#include <string>
#include <list>

class search: public algorithm {
public:
    search() = default;
    ~search();
    void load(const char*, const char *);
    void execute();
    void display();
    void stats(unsigned int);
    void select(int);
    void save(const char*);
    void configure();
private:
    std::vector<std::list<int> > adjList;
    algorithm::searches searchType;
    int ** matrix;
};

#endif //LAB01_SEARCH_H
