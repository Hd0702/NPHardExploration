//
// Created by Hayden Donofrio on 10/25/18.
//

#include "Decorator.h"
#include <iostream>
Decorator::Decorator(BaseDecorator * b2):br(b2) {}
//Delegation class
void Decorator::execute() {
    br->execute();
}
void Decorator::setMatrix(Node ** a, int size) {
    br->setMatrix(a, size);
}
void Decorator::stats(char *type, unsigned int time, int nodes, double distance) {
    br->stats(type, time, nodes, distance);
}

std::vector<int> Decorator::bestNeighbor(std::vector<int> &current, Node **matrix) {
    //this method takes the current solution and finds the best neighbor for it
    //our neighborhood is all solutions with two cities switched
    //current looks like 1,2,3,4,5,6,1
    double bestDist = calculateDistance(current, matrix);
    std::vector<int> bestSolution = current;
    for (int i =1; i < current.size()-1; i++){
        for(int j = i+1; j < current.size()-1; j++){
            std::vector<int> temp = current;
            std::swap(temp[i],temp[j]);
            double tDist = calculateDistance(temp, matrix);
            if(tDist < bestDist){
                bestDist = tDist;
                bestSolution = temp;
            }
        }
    }
    return bestSolution;
}
double Decorator::calculateDistance(std::vector<int> &current, Node **matrix) {
    double total = 0;
    std::vector<int> temp = current;
    for (int i = 1; i < current.size(); i++) {
        if(current[i] <= current.size() && current[i] != 0)
            total += matrix[current[i - 1] - 1][current[i] - 1].distance;
        else {
            i++;
        }
    }
    return total;
}
