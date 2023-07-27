//
// Created by Hayden Donofrio on 10/28/18.
//

#ifndef LAB03_ALGOBUILDER_H
#define LAB03_ALGOBUILDER_H
#include <vector>
#include "AlgoFactory.h"
#include "BruteForce.h"
#include "Dynamic.h"
#include "Node.h"
#include "Reader.h"
class BaseDecorator;
//this class saves all the data and reads it
class AlgoBuilder {
public:
    Node ** getMatrix();
    void setMatrix(Node** & mat);
    BaseDecorator * getAlgo();
    void setAlgo( AlgoFactory::algos alg);
    void setSize(int a);
    void start();
private:
    Node** matrix; //TODO: getters and setters
    BaseDecorator * algo;
    int size;
};


#endif //LAB03_ALGOBUILDER_H
