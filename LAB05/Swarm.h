//
// Created by Hayden Donofrio on 12/3/18.
//

#ifndef LAB03_SWARM_H
#define LAB03_SWARM_H
#include "Decorator.h"
#include <string>

class Swarm: public Decorator {
public:
    Swarm(BaseDecorator* br): Decorator(br){}
    void execute();
    void setMatrix(Node**, int);
    void stats(unsigned int time);
private:
    unsigned int run();
    std::vector<std::pair<std::vector<int>,std::pair<std::vector<int>, double> > >population;
    Node** matrix;
    int matrixSize;
    std::vector<std::vector<int> > velocities;
    std::vector<int> bestSolution;
    std::vector<std::pair<unsigned int, double> > times;
    std::vector<int> setVelocity(int popIndex);
    int maxVelocity;
    int localLearning;
    int globalLearning;
    double bestDistance = INT32_MAX;
};


#endif //LAB03_SWARM_H
