//
// Created by Hayden Donofrio on 11/13/18.
//

#ifndef LAB03_GENETIC_H
#define LAB03_GENETIC_H
#include "Decorator.h"

class Genetic: public Decorator {
public:
    Genetic(BaseDecorator * br): Decorator(br){}
    void execute();
    unsigned int run();
    void setMatrix(Node**, int size);
private:
    std::vector<int> ox1(std::vector<int>&, std::vector<int>&);
    void showStats(unsigned int);
    char *strs [6]  = { "Full PMX", "Order 1 crossover", "Back PMX", "Current/Total", "LastHalfs/2", "Superior Split",};
    std::vector<std::vector<int> > population;
    int matrixSize;
    int MutationChance = 5;
    double bestDistance = INT32_MAX;
    std::vector<int> bestSolution;
    Node** Matrix;
    int selection = 0;
    int probSelect;
    std::vector<std::pair<unsigned int, double> > times;
    std::vector<int> CreateChild( std::vector<int>&, std::vector<int>&);
};


#endif //LAB03_GENETIC_H
