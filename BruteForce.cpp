//
// Created by Hayden Donofrio on 10/30/18.
//

#include "BruteForce.h"
#include <iostream>
#include <string>
void BruteForce::execute() {
    Decorator::execute();
    std::cout << "Brute Force Execute" << std::endl;
    path.push_back(matrix[0][0]);
    auto start = std::chrono::high_resolution_clock::now();
    run(1);
    auto end = std::chrono::high_resolution_clock::now();
    unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    showStats(total);

}
void BruteForce::run(int loc) {
        for(int i =0; i < matrixSize; i++) {
            if(i != loc-1) {
                totalCount++;
                //checking loc wont work you should set unvisited
                //maybe use a current node and then remove that
                std::vector<Node>::iterator it = std::find_if(path.begin(), path.end(), [i] (Node s) { return s.id == i+1; } );
                if(it == path.end()) {
                    path.push_back(matrix[loc - 1][i]);
                    run(i + 1);
                }
            }
        }
    if(path.size() == matrixSize) {
        for (auto &item : path) {
            totaldistance += item.distance;
        }
        totaldistance += matrix[path.back().id - 1][0].distance;
        if (totaldistance < finalDistance) {
            finalDistance = totaldistance;
            bestPath= path;
            bestPath.push_back(matrix[path.back().id - 1][0]);
        }
        totaldistance = 0;
    }
    path.pop_back();
}
void BruteForce::setMatrix(Node** mat, int size){
    matrix = mat;
    matrixSize = size;
}
void BruteForce::showStats(unsigned int time) {
    std::string A = "Brute Force \n Path: ";
    for(auto &j : bestPath){
        A += std::to_string(j.id); + " ";
    }
    Decorator::stats((char*)A.c_str(), time, totalCount, finalDistance);
}