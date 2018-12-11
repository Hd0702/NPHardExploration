//
// Created by Hayden Donofrio on 10/25/18.
//

#ifndef LAB03_SALESMAN_H
#define LAB03_SALESMAN_H
//this is the class that implements decorator and does stuff
#include "Decorator.h"
#include "Node.h"
class Salesman:public BaseDecorator {
public:
    void execute();
    void setMatrix(Node**, int sizev);
    void stats(char * type, unsigned int time, int nodes, double distance);
};


#endif //LAB03_SALESMAN_H
