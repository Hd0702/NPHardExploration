//
// Created by Hayden Donofrio on 10/30/18.
//

#ifndef LAB03_BRUTEFORCE_H
#define LAB03_BRUTEFORCE_H

#include "Decorator.h"
#include <vector>
#include "AlgoBuilder.h"
#include "Node.h"
#include <queue>
class BruteForce: public Decorator {
public:
    BruteForce(BaseDecorator * br): Decorator(br){}
    void execute();
    void run(int);
    void setMatrix(Node**, int size);
private:
    void showStats(unsigned int);
    Node** matrix;
    double totaldistance = 0;
    std::vector<Node> bestPath;
    std::vector<Node> path;
    double finalDistance = INT16_MAX;
    int matrixSize;
    int totalCount =  0;
};


#endif //LAB03_BRUTEFORCE_H
