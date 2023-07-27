//
// Created by Hayden Donofrio on 10/25/18.
//

#ifndef LAB03_DECORATOR_H
#define LAB03_DECORATOR_H
#include "BaseDecorator.h"
#include "Node.h"
#include <vector>
class Decorator: public BaseDecorator{
    BaseDecorator * br;
public:
    Decorator(BaseDecorator * );
    void execute();
    void setMatrix(Node**, int);
    void stats(char * type, unsigned int time, int nodes, double distance);
protected:
    std::vector<int> bestNeighbor(std::vector<int> & current, Node ** matrix);
    double calculateDistance(std::vector<int> & current, Node ** matrix);
};


#endif //LAB03_DECORATOR_H
