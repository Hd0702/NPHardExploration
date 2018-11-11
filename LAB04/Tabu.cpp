//
// Created by Hayden Donofrio on 11/9/18.
//

#include "Tabu.h"
#include <algorithm>
void Tabu::execute() {
    //we should come up with an original solution here, start hill climbing
    solution.push_back(Matrix[0][0].id);
    int row = 0;
    for(int j = 1; j < matrixSize; j++) {
        double smallest = INT32_MAX;
        int smlindx = 0;
        for (int i = 1; i < matrixSize; i++) {
            auto it = std::find(solution.begin(), solution.end(), i+1);
            if (it == solution.end() && Matrix[row][i].distance < smallest) {
                smallest = Matrix[row][i].distance;
                smlindx = i;
            }
        }
        solution.push_back(Matrix[row][smlindx].id);
        row = smlindx;
    }
    solution.push_back(1);
    run();
    //now we can focus on hill climbing and the tabu list
}
void Tabu::run() {
    //get best solution until we hit a peak
    //this is hill climbing, need to add tabu list no
    TabuList.push_back(solution);
    unsigned int i =0;
    double bestLocal = Decorator::calculateDistance(solution, Matrix);
    double globalBest = bestLocal;
    std::vector<int> bestLocalVec = solution;
    std::vector<int> bestGlobalVec = solution;
    while(i < matrixSize*500) {
        std::vector<int> temp = bestNeighbor(solution);
        double a = Decorator::calculateDistance(temp, Matrix);
        if(a < globalBest) {
            bestGlobalVec = temp;
            globalBest = a;
        }
        solution = temp;
        i++;
        TabuList.push_back(solution);
        if(i > 1000)
            TabuList.pop_front();
    }
    int jk = 0;
}
void Tabu::setMatrix(Node ** m, int size) {
    Matrix = m;
    matrixSize = size;
}

std::vector<int> Tabu::bestNeighbor(std::vector<int> &current) {
    //get the best solution, also the "least bad solution"
    double bestDist = Decorator::calculateDistance(current, Matrix);
    std::vector<int> bestSolution = current;
    std::vector<int> leastBad;
    double leastBadCount = INT32_MAX;
    for (int i =1; i < current.size()-1; i++){
        for(int j = i+1; j < current.size()-1; j++){
            std::vector<int> temp = current;
            std::swap(temp[i],temp[j]);
            double tDist = Decorator::calculateDistance(temp, Matrix);
            if(tDist < leastBadCount && std::find(TabuList.begin(), TabuList.end(), temp) == TabuList.end()){
                leastBadCount = tDist;
                bestSolution = temp;
            }
        }
    }
    return bestSolution;
}