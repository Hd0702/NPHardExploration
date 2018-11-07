//
// Created by Hayden Donofrio on 10/25/18.
//

#ifndef LAB03_DECORATOR_H
#define LAB03_DECORATOR_H
#include "BaseDecorator.h"
#include "Node.h"
class Decorator: public BaseDecorator{
    BaseDecorator * br;
public:
    Decorator(BaseDecorator * );
    void execute();
    void setMatrix(Node**, int);
    void stats(char * type, unsigned int time, int nodes, double distance);
};


#endif //LAB03_DECORATOR_H
