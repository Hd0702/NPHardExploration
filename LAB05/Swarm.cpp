//
// Created by Hayden Donofrio on 12/3/18.
//

#include "Swarm.h"
#include <random>
#include <map>
void Swarm::execute() {

    std::vector<std::pair<std::vector<int>,std::pair<std::vector<int>, double> > >startPop;
    std::vector<std::vector<int> > startingV;
    std::srand ( unsigned ( std::time(0) ) );
    auto rng = std::default_random_engine {};
    for(int i =0; i < 20; i++){
        std::vector<int> temp;
        std::vector<int> tempv = {0,0};
        for(int j =2; j < matrixSize+1; j++){
            temp.push_back(j);
            tempv.push_back(0);
        }
        std::shuffle(std::begin(temp), std::end(temp), rng);
        temp.insert(temp.begin(), 1);
        temp.push_back(1);
        //starting velocities are all 0
        startingV.push_back(tempv);
        startPop.push_back(std::make_pair(temp, std::make_pair(temp, Decorator::calculateDistance(temp, matrix))));
    }
    std::vector<std::pair<int, int> > learning_factors =
            {std::make_pair(1, 3), std::make_pair(3, 1), std::make_pair(2, 2)};
    std::vector<int> maxVs = {matrixSize/5, matrixSize/4, matrixSize/2};

    for (auto & j : learning_factors){
        localLearning = j.first;
        globalLearning = j.second;

        for(auto & k : maxVs) {
            maxVelocity = k;
            population = startPop;
            velocities = startingV;
            bestDistance = INT32_MAX;
            unsigned int time = run();
            times.clear();
            stats(time);
        }
    }
}

unsigned int Swarm::run() {
    auto t1 = std::chrono::high_resolution_clock::now();
    int counter =0;
    while(counter != 10000 && bestDistance != matrixSize+1){
        //check each item in the population and assign local or global best
        for(auto &j: population){
            double currentDist= Decorator::calculateDistance(j.first, matrix);
            if(currentDist < j.second.second){
                j.second.first = j.first;
                j.second.second = currentDist;
            }
            if(currentDist < bestDistance){
                auto t2 = std::chrono::high_resolution_clock::now();
                unsigned int time = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
                times.push_back(std::make_pair(time, currentDist));
                bestDistance = currentDist;
                bestSolution = j.first;
            }
        }
        counter++;
        //now we calculate velocity
        for(int i =0; i < population.size(); i++){
            std::vector<int> newVelocity = setVelocity(i);
            auto q = newVelocity;
            //now we move to a new spot, if its not valid, calculate velocity again
            //add velocity to displacement and check if its a valid solution, otherwise go again
            std::vector<int> temp = population[i].first;
            std::map<int,int> counts;
            counts.emplace(1, 0);
            for(int j =1; j < population[i].first.size()-1; j++) {
                temp[j] += newVelocity[j];
                //do a map check here for validity
                if(temp[j] <= 1){
                    temp[j] = matrixSize + temp[j];
                }
                if(temp[j] > matrixSize){
                    temp[j] = abs(temp[j]-matrixSize+1);
                }
                while(true){
                    if(counts.count(temp[j]) == 0) {
                        counts.emplace(temp[j],0);
                        break;
                    }
                    else {
                        temp[j]++;
                        if(temp[j] > matrixSize)
                            temp[j] = 1;
                    }
                }
            }
            velocities[i] = newVelocity;
            population[i].first = temp;
        }

    }
    auto t2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
}

std::vector<int> Swarm::setVelocity(int popIndex) {
    std::vector<int> newVelocity = velocities[popIndex];
    double r1 = ((double)rand()/(double)RAND_MAX);
    double r2 = ((double)rand()/(double)RAND_MAX);
    double r3 =((double)rand()/(double)RAND_MAX);
    for(int i =1; i < population[popIndex].first.size()-1; i++){
        //loop through best local and subtract from current
        double add = population[popIndex].second.first[i] - population[popIndex].first[i];
        add *= r1*localLearning;
        //DEBUG
        if(abs(add) > maxVelocity) {
            (add < 0) ? add = -maxVelocity : add = maxVelocity;
        }
        double add2 = bestSolution[i] - population[popIndex].first[i];
        add2 *= r2*globalLearning;
        //DEBUG
        if(abs(add2) > maxVelocity) {
            (add2 < 0) ? add2 = -maxVelocity : add2 = maxVelocity;
        }
        double add3 = r3*newVelocity[i] + add2 + add;
        if(abs(add3) > maxVelocity) {
            (add3 < 0) ? add3 = -maxVelocity : add3 = maxVelocity;
        }
        newVelocity[i] = (int)std::round(add3);
    }
    return newVelocity;
}

void Swarm::setMatrix(Node ** Ma, int msize) {
    matrix = Ma;
    matrixSize = msize;
}

void Swarm::stats(unsigned int time) {
    std::string b ="";
    for(auto &j : bestSolution){
        b+= std::to_string(j) + " ";
    }
    std::string format = std::string("Particle Swarm\nLocal Learning Factor: ") + std::to_string(localLearning)
                         + "\nGlobal Learning Factor: " + std::to_string(globalLearning) + "\nMax Velocity: "
                         + std::to_string(maxVelocity) + "\nSolution: " + b;
    Decorator::stats((char*)format.c_str(), time,0,bestDistance );
}