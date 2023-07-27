//
// Created by Hayden Donofrio on 10/30/18.
//

#include "Dynamic.h"
#include <iostream>
void Dynamic::execute() {
    Decorator::execute();
    std::cout << "Dynamic Execute" << std::endl;
    //TODO: Make this dynamic
    ar = new std::pair<int, double>[matrixSize];
    for(int i =2; i< matrixSize+1; i++){
        remaining.push_back(i);
        ar[i-2].second = INT32_MAX;
    }
    ar[matrixSize-1].second = INT32_MAX;
    auto start = std::chrono::high_resolution_clock::now();
    TDistance = run(1, remaining)-1;
    auto end = std::chrono::high_resolution_clock::now();
    unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    ar[0].first = 1;
    TDistance += matrix[ar[matrixSize-1].first][0].distance;
    showStats(total);
}
double Dynamic::run(int loc, std::vector<int> path) {
    double smallest = INT32_MAX;
    double t = -1;
    int smlindx;
    if(storage.count(std::make_pair(loc, path)) == 0) {
        storage.emplace(std::make_pair(loc, path), 0);
        std::vector<double > holder;
        for(auto & j: path){
            //path is the values we have to grab each one and make new vector without element
            std::vector<int> temp;
            for(auto &l: path) {
                if (l != j) {
                    totalcount++;
                    temp.push_back(l);
                }
            }
            if(temp.size() > 0) {
                t = run(j, temp) + matrix[loc - 1][j - 1].distance;
                holder.push_back(t);
                if(t < smallest) {
                    smallest = t;
                    smlindx = j ;
                }
            }
            else if (temp.size() == 0) {
                t =  run(j, temp) + matrix[loc - 1][j - 1].distance;
                smallest = t;
                smlindx = j;
            }
        }
        if(t != -1) {
            if(ar[path.size()].second > smallest) {
                ar[path.size()].first = smlindx;
                ar[path.size()].second = smallest;
            }
            storage[std::make_pair(loc, path)] = smallest;
        }
        else {
            ar[0].first = loc;
            storage[std::make_pair(loc, path)] = matrix[loc - 1][0].distance;
        }
    }
    smlsl = smlindx;
    return storage[std::make_pair(loc, path)];
}

void Dynamic::setMatrix(Node** mat, int size){
    matrix = mat;
    matrixSize = size;
}

void Dynamic::showStats(unsigned int time) {
    Decorator::stats("Dynamic", time, totalcount, TDistance);
}