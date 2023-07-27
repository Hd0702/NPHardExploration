//
// Created by Hayden Donofrio on 10/28/18.
//

#ifndef LAB03_BASEDECORATOR_H
#define LAB03_BASEDECORATOR_H
#include "Node.h"
class BaseDecorator{
public:
    virtual void execute() = 0;
    virtual void setMatrix(Node**, int) = 0;
    virtual void stats(char * type, unsigned int time, int nodes, double distance) = 0;
};
#endif //LAB03_BASEDECORATOR_H
