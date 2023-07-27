//
// Created by Hayden Donofrio on 10/25/18.
//

#include "Decorator.h"
#include <iostream>
#include <random>
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
    //get the best solution, also the "least bad solution"
    double bestDist = Decorator::calculateDistance(current, matrix);
    std::vector<int> bestSolution = current;
    double leastBadCount = INT32_MAX;
    int i= 1;
    for (; i < current.size()-1; i++){
        int j;
        for(; j < current.size()-1; j++){
            if(i != j) {
                std::vector<int> temp = current;
                std::swap(temp[i], temp[j]);
                double tDist = Decorator::calculateDistance(temp, matrix);
                if (tDist < leastBadCount) {
                    leastBadCount = tDist;
                    bestSolution = temp;
                }
            }
        }
    }
    if (std::equal(bestSolution.begin(), bestSolution.end(), current.begin())){
        bestSolution.erase(bestSolution.begin());
        bestSolution.pop_back();
        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(bestSolution), std::end(bestSolution), rng);
        bestSolution.insert(bestSolution.begin(), 1);
        bestSolution.push_back(1);
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
