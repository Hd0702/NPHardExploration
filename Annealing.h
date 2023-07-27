//
// Created by Hayden Donofrio on 12/2/18.
//

#ifndef LAB03_ANNEALING_H
#define LAB03_ANNEALING_H
#include "Decorator.h"

class Annealing: public Decorator {
public:
    Annealing(BaseDecorator* br): Decorator(br){}
    void execute();
    void setMatrix(Node**, int);
    void stats(unsigned int time);
private:
    char * selections[3] = {"Decrease by 2", "Decrease by 5", "Decrease by 10 slowly"};
    void run();
    std::vector<int> getNeighbor(std::vector<int> & current);
    std::vector<int> solution;
    std::vector<std::pair<unsigned int, double> > times;
    Node** matrix;
    int matrixSize;
    std::vector<int> bestSolution;
    double bestDistance;
    int selection;
    int temprature;
};


#endif //LAB03_ANNEALING_H
