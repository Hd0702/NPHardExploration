//
// Created by Hayden Donofrio on 11/9/18.
//

#ifndef LAB03_TABU_H
#define LAB03_TABU_H
#include "Decorator.h"
#include <vector>
#include <list>
class Tabu: public Decorator {
public:
    Tabu(BaseDecorator * br): Decorator(br){}
    void execute();
    unsigned int run();
    void setMatrix(Node**, int size);
private:
    std::vector<int> bestNeighbor(std::vector<int> & current);
    void showStats(unsigned int);
    char * neighbortypes[3] = {"Full swap", "Front swap", "Back swap"};
    int listSize;
    int selection;
    std::vector<std::pair<unsigned int, double> > times;
    std::list<std::vector<int> > TabuList;
    std::vector<int> solution;
    int matrixSize;
    Node** Matrix;
};


#endif //LAB03_TABU_H
