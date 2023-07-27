//
// Created by Hayden Donofrio on 10/30/18.
//

#ifndef LAB03_DYNAMIC_H
#define LAB03_DYNAMIC_H

#include "Decorator.h"
#include <map>
#include <vector>
#include <vector>
class Dynamic: public Decorator {
public:
    Dynamic(BaseDecorator * br): Decorator(br){}
    void execute();
    double run(int, std::vector<int> path);
    void setMatrix(Node**, int size);
private:
    void showStats(unsigned int time);
    Node** matrix;
    int smlsl;
    int matrixSize;
    std::pair<int, double> * ar;
    std::vector<int> remaining;
    int totalcount = 0;
    double TDistance =0;
    std::map<std::pair<int, std::vector<int> >, double > storage;
};


#endif //LAB03_DYNAMIC_H
