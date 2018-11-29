//
// Created by Hayden Donofrio on 11/9/18.
//

#include "Tabu.h"
#include <algorithm>
#include <chrono>
#include <string>
#include <random>
void Tabu::execute() {
    //we should come up with an original solution here, start hill climbing
    //save each time we get a new best solution
    //TODO:include checking if tabu list is greater than max number of combinations, if it reaches the max number, quit
    std::vector<int> listSizes = {100, 500, 1000};
    std::vector<int> starting;
    std::srand(time(NULL));
    auto rng = std::default_random_engine {};
    std::vector<int> temp;
    for(int j =2; j < matrixSize+1; j++){ temp.push_back(j); }
    std::shuffle(std::begin(temp), std::end(temp), rng);
    temp.insert(temp.begin(), 1);
    temp.push_back(1);
        for(auto & s: listSizes) {
            listSize = s;
            for (int i =0; i < 3; i++) {
                selection = i;
                solution = temp;
                unsigned int time = run();
                if(times.size() == 0)
                    times.push_back(std::make_pair(1, Decorator::calculateDistance(starting, Matrix)));
                showStats(time);
                solution.clear();
                TabuList.clear();
                times.clear();
            }
        }

    //now we can focus on hill climbing and the tabu list
}
//TODO: change taboolist size for multiple types of lists
unsigned int Tabu::run() {
    //get best solution until we hit a peak
    //this is hill climbing, need to add tabu list no
    auto t1 = std::chrono::high_resolution_clock::now();
    TabuList.push_back(solution);
    unsigned int i =0;
    double bestLocal = Decorator::calculateDistance(solution, Matrix);
    double globalBest = bestLocal;
    std::vector<int> bestLocalVec = solution;
    std::vector<int> bestGlobalVec = solution;
    while(i < matrixSize*2000 && globalBest != matrixSize) {
        std::vector<int> temp = bestNeighbor(solution);
        double a = Decorator::calculateDistance(temp, Matrix);
        if(a < globalBest) {
            auto t2 = std::chrono::high_resolution_clock::now();
            double time = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
            times.push_back(std::make_pair(time, a));
            bestGlobalVec = temp;
            globalBest = a;
        }
        solution = temp;
        i++;
        TabuList.push_back(solution);
        if(i > listSize)
            TabuList.pop_front();
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
}
void Tabu::setMatrix(Node ** m, int size) {
    Matrix = m;
    matrixSize = size;
}
//other best neighbor attempts
//pick the first element to a number 1-size, then swap the first element with whichever index appears
//(basically same as before just less complete)
//2. swapping the last element whit all of the others
//1. complete swap, 2.front partial swap, 3. back partial swap
std::vector<int> Tabu::bestNeighbor(std::vector<int> &current) {
    //get the best solution, also the "least bad solution"
    double bestDist = Decorator::calculateDistance(current, Matrix);
    std::vector<int> bestSolution = current;
    double leastBadCount = INT32_MAX;
    int i= 1;
    if (selection == 2) {
        i = current.size()-3;
    }
    for (; i < current.size()-1; i++){
        int j;
        (selection == 2) ? j = 1 : j = i+1;
        for(; j < current.size()-1; j++){
            if(i != j) {
                std::vector<int> temp = current;
                std::swap(temp[i], temp[j]);
                double tDist = Decorator::calculateDistance(temp, Matrix);
                if (tDist < leastBadCount && std::find(TabuList.begin(), TabuList.end(), temp) == TabuList.end()) {
                    leastBadCount = tDist;
                    bestSolution = temp;
                }
            }
        }
        if (selection == 1) {
            break;
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

void Tabu::showStats(unsigned int time) {
    std::string format =  std::string("Tabu\nNeighbor Type: ") + neighbortypes[selection] +
            "\nTabu List Size: " + std::to_string(listSize);
    Decorator::stats((char*)format.c_str() , time, 0, times.back().second);

}