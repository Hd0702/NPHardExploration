//
// Created by Hayden Donofrio on 9/1/18.
//

#ifndef LAB01_SORT_H
#define LAB01_SORT_H

#include "algorithm.h"
//this is the overall class for implemnting sorts based off enums
class sort: public algorithm {
public:
    sort() = default;
public:
    void load(const char*);
    void execute();
    void display();
    void stats();
    void select(sorts);
    void save(const char*);
    void configure();
};


#endif //LAB01_SORT_H
