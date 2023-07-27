//
// Created by Hayden Donofrio on 10/30/18.
//

#ifndef LAB03_ALGOFACTORY_H
#define LAB03_ALGOFACTORY_H

class BaseDecorator;
class AlgoFactory {
public:
    enum algos {BRUTEFORCE = 0, DYNAMIC, TABU, GENETIC, ANNEALING, SWARM};
    static BaseDecorator * Create(algos);
};


#endif //LAB03_ALGOFACTORY_H
