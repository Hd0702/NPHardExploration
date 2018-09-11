//
// Created by Hayden Donofrio on 9/10/18.
//

#include "search.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
//load in fileName and create list or matrix
search::~search() {
    //destruct adj matrix here
}

void search::load(const char * searchName, const char * Weights, const char * distance) {
    adjList.clear();
    int matrixSize = 0;
    std::ifstream open(searchName);
    if(!open) {
        std::cerr << searchName << " could not be opened";
        exit(EXIT_FAILURE);
    }
    std::ifstream weights(Weights);
    if(!weights) {
        std::cerr << Weights << " could not be opened";
        exit(EXIT_FAILURE);
    }
    std::ifstream distances(distance);
    if(!distances) {
        std::cerr << distance << " could not be opened";
        exit(EXIT_FAILURE);
    }
    //first get datapoints
    std::string reader = "";
    while(getline(open, reader)) {
        matrixSize++;
        std::stringstream line(reader);
        int item = 0;
        std::string breaker;
        std::vector<search::item> points;
        //seperate item stuct for respective item
        while(std::getline(line, breaker, ',')){
            search::item add;
            add.x =0; add.y =0; add.z=0; add.weight = 0;
            add.data = std::stoi(breaker);
            points.push_back(add);
        }
        adjList.push_back(points);
    }
    reader.clear();
    //now beginning positions for each
    int counter = 0;
    while(getline(distances, reader)) {
        std::stringstream line(reader);
        int item = 0;
        int coords[3];
        std::string breaker;
        //seperate item stuct for respective item
        std::getline(line, breaker, ',');
        int index = std::stoi(breaker);
        int counterin = 0;
        while (std::getline(line, breaker, ',')) {
            coords[counterin++] = std::stoi(breaker);
        }
        adjList[counter][0].x = coords[0];
        adjList[counter][0].y = coords[1];
        adjList[counter][0].z = coords[2];
        double add = sqrt(pow(coords[0],2) + pow(coords[1],2) + pow(coords[2],2));
        adjList[counter][0].distance= add;
        counter++;
    }
    //now calculate the rest of the distance
    for(int i =0; i < matrixSize; i++) {
        std::cout<< adjList[i].size() << std::endl;
    }
    for(int i =0; i < matrixSize; i ++) {
        //go through each item and calculate distance based off data
        auto start = adjList[i].begin();
        for (auto iter = adjList[i].begin() + 1; iter != adjList[i].end(); iter++) {
            auto firstNew = adjList[iter->data-1].begin();
            std::cout << iter->data << " ";
            iter->distance = sqrt(pow((firstNew->x - start->x), 2) +
                                  pow((firstNew->y - start->y), 2) +
                                  pow((firstNew->z - start->z), 2));
        }
        std::cout << "\n";
    }
    for(auto & k : adjList) {
        for(auto & j : k) {
            std::cout << "(" << j.data << " " << j.distance << ")";
        }
        std::cout << std::endl;
    }
    //now for weights

    //now for matrix
    open.clear();
    open.seekg(0, std::ios::beg);
    matrix = new int*[matrixSize];
    for(int i =0; i < matrixSize; i++) {
        matrix[i] = new int[matrixSize];
        for(int x = 0; x < matrixSize; x++) {
            matrix[i][x] = 0;
        }
    }
    reader.clear();
    int row = 0;
    while(getline(open, reader)) {
        std::stringstream line(reader);
        std::string breaker;
        //remove first element
        std::getline(line, breaker, ',');
        while(std::getline(line, breaker, ',')){
            int print = std::stoi(breaker);
            matrix[row][print-1] = 1;
        }
        row++;
    }
    for(int i =0; i < matrixSize; i ++) {
        for(int x =0 ;x < matrixSize; x ++) {
            std::cout << matrix[i][x] << " ";
        }
        std::cout << std::endl;
    }
    open.close();

}

void search::execute() {
    if(searchType == DFS){
        //dfs here plz
    }
    else if(searchType == BFS) {

    }
    else if(searchType == Dijsktra) {

    }
    else if(searchType == A) {

    }
}

void search::display() {

}

void search::stats(unsigned int time) {

}

void search::select(int select) {
    searchType = algorithm::searches (select);
}

void search::save(const char * fileName) {

}
void search::configure() {

}