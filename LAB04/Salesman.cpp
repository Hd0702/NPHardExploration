//
// Created by Hayden Donofrio on 10/25/18.
//

#include "Salesman.h"
#include <iostream>
void Salesman::execute() {
    std::cout << "Executing algorithim" << std::endl;

}
void Salesman::setMatrix(Node ** a, int size) {
    std::cout << "Setting Matrix" << std::endl;
}
void Salesman::stats(char *type, unsigned int time, int nodes, double distance) {
    //stats implementation in salesman because it is the same for all items
    std::cout << "Algo Type: " << type << "\n";
    std::cout << "Time in Microseconds: " << time << "\n";
    std::cout << "Nodes explored: " << nodes << "\n";
    std::cout << "Distance explored: " << distance << "\n\n";
}