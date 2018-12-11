//
// Created by Hayden Donofrio on 12/2/18.
//

#include "Annealing.h"
#include <random>
#include <cmath>
#include <string>

void Annealing::execute() {
    //decrease by 5 each time
    //decrease by 2 each time
    //decrease by 10 every 500 times
    //starting 5000, 500, 100
    srand((unsigned)time(NULL));
    std::vector<int> starting;
    std::srand(time(NULL));
    auto rng = std::default_random_engine {};
    std::vector<int> temp;
    for(int j =2; j < matrixSize+1; j++){ temp.push_back(j); }
    std::shuffle(std::begin(temp), std::end(temp), rng);
    temp.insert(temp.begin(), 1);
    temp.push_back(1);
    std::vector<int> tempratures = {5000, 500, 100};
    for(int i =0; i < 3; i++) {
        selection = i;
        for(auto & j : tempratures) {
            solution = temp;
            temprature = j;
            run();
            times.clear();
        }
    }

}

void Annealing::run() {
    auto start = std::chrono::high_resolution_clock::now();
    int a =0;
    int currentTemp = temprature;
    double currentEnergy = Decorator::calculateDistance(solution, matrix);
    int i =0;
    bestSolution = solution;
    bestDistance = currentEnergy;
    while(currentTemp > 0 && bestDistance != matrixSize) {
        a= currentEnergy;
        //now get a neighbor and check its fitness
        std::vector<int> temp = getNeighbor(solution);
        double newEnergy = Decorator::calculateDistance(temp, matrix);
        double pop = ((double)rand()/(double)RAND_MAX);
        double pop2 = std::exp((currentEnergy-newEnergy)/currentTemp);
        if(newEnergy < currentEnergy || pop2 - pop > 0) {
            solution = temp;
            if(newEnergy < bestDistance) {
                auto t2 = std::chrono::high_resolution_clock::now();
                unsigned int time = std::chrono::duration_cast<std::chrono::microseconds>(t2-start).count();
                times.push_back(std::make_pair(time, newEnergy));
                bestSolution = solution;
                bestDistance = newEnergy;
            }
            currentEnergy = newEnergy;
        }
        i++;
        if(selection != 2 && i == 50){
            (selection == 0) ? currentTemp -= 2 : currentTemp -=5;
            i = 0;
        }
        else if(i==500) {
            currentTemp -= 10;
            i=0;
        }

    }
    auto end = std::chrono::high_resolution_clock::now();
    unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    stats(total);
    //std::string format =  std::string("Annealing\nNeighbor Type: ") + neighbortypes[selection] +
    //                      "\nTabu List Size: " + std::to_string(listSize) + "\npath: " + a.c_str() + "\n";

    int q =0;
}

std::vector<int> Annealing::getNeighbor(std::vector<int> &current) {
    //this gets a random neighbor
    std::vector<std::vector<int> > solutions;
    for (int i =1 ; i < current.size()-1; i++){
        for(int j =1; j < current.size()-1; j++){
            if(i != j) {
                std::vector<int> temp = current;
                std::swap(temp[i], temp[j]);
                solutions.push_back(temp);
            }
        }
    }
    int p = rand() % solutions.size();
    return solutions[p];
}

void Annealing::setMatrix(Node ** mat, int size) {
    matrix = mat;
    matrixSize = size;
}

void Annealing::stats(unsigned int time) {
    std::string b ="";
    for(auto &j : solution){
        b+= std::to_string(j) + " ";
    }
    std::string format = std::string("Annealing\nStarting Temp: ") + std::to_string(temprature) + "\nDecrease type: "
                         + selections[selection] + "\nSolution: " + b;

    Decorator::stats((char*)format.c_str(), time,0,bestDistance );
}