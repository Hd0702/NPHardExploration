//
// Created by Hayden Donofrio on 9/1/18.
//

#ifndef LAB01_SORT_H
#define LAB01_SORT_H

#include "algorithm.h"
#include <vector>
#include <string>
//this is the overall class for implementing sorts based off enums
//it inherits from algorithm and uses all sort types
class sort: public algorithm {
public:
    sort() = default;
    sort(const sort &);
    void load(const char*, const char *);
    void execute();
    void display();
    void stats(unsigned int);
    void select(int);
    void save(const char*);
    void configure();
    //ADDING BUILDER FUNCTIONALITY
    enum Configuration { RECURSIVE = 0, ITERATIVE, LIST, MATRIX };
    void setExecutionType(sort::Configuration exe);
    void setStorageType(Configuration );
    void getConfiguration();
    //prototype
    algorithm * Clone();

private:
    Configuration executionType;
    Configuration storageType;
    static std::string algoType;
    static int dataSize;
    static std::string dataType;
    std::vector<int> data;
    algorithm::sorts sortType;
};


#endif //LAB01_SORT_H
