//
// Created by Hayden Donofrio on 9/10/18.
//

#include "search.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include "dfs.h"
#include "bfs.h"
#include "Dijkstra.h"
#include "AStar.h"
//load in fileName and create list or matrix
search::~search() {
    //destruct adj matrix here
}

void search::load(const char * searchName, const char * Weights, const char * distance) {
    adjList.clear();
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
        std::vector<search::Node> points;
        //get first
        std::getline(line, breaker, ',');
        search::Node add;
        add.x =0; add.y =0; add.z=0; add.weight = 0;
        add.data = std::stod(breaker);
        points.push_back(add);
        //seperate Node stuct for respective Node
        //set pointers to new nodes
        while(std::getline(line, breaker, ',')){
            search::Node add;
            add.x =0; add.y =0; add.z=0; add.weight = 0;
            add.data = std::stod(breaker);
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
        double coords[3];
        std::string breaker;
        //seperate Node stuct for respective Node
        std::getline(line, breaker, ',');
        double index = std::stod(breaker);
        int counterin = 0;
        while (std::getline(line, breaker, ',')) {
            coords[counterin++] = std::stod(breaker);
        }
        adjList[counter][0].x = coords[0];
        adjList[counter][0].y = coords[1];
        adjList[counter][0].z = coords[2];
        adjList[counter][0].distance= pow(coords[0],2) + pow(coords[1],2) + pow(coords[2],2);
        counter++;
    }
    //now calculate the rest of the distance
    for(int i =0; i < matrixSize; i ++) {
        //go through each Node and calculate distance based off data
        auto start = adjList[i].begin();
        for (auto iter = adjList[i].begin() + 1; iter != adjList[i].end(); iter++) {
            auto firstNew = adjList[iter->data-1].begin();
            iter->distance = pow((firstNew->x - start->x), 2) +
                             pow((firstNew->y - start->y), 2) +
                             pow((firstNew->z - start->z), 2);
        }
    }
    //now for weights
    reader.clear();
    while(getline(weights, reader)) {
        std::stringstream line(reader);
        std::string breaker;
        //seperate Node stuct for respective Node
        std::getline(line, breaker, ',');
        int firstitem = std::stod(breaker);
        auto first = adjList[firstitem-1].begin();
        //now get second
        std::getline(line, breaker, ',');
        int seconditem = std::stod(breaker);
        std::getline(line, breaker, ',');
        int weight = std::stod(breaker);
        for(auto & x: adjList[firstitem-1]) {
            if (x.data == seconditem) {
                x.weight = weight;
            }
        }
        //now get weight
    }
    //now for matrix
    open.clear();
    open.seekg(0, std::ios::beg);
    matrix = new Node*[matrixSize];
    for(int i =0; i < matrixSize; i++) {
        matrix[i] = new Node[matrixSize];
    }
    reader.clear();
    int row = 0;
    while(getline(open, reader)) {
        int adjcounter =1;
        std::stringstream line(reader);
        std::string breaker;
        //remove first element
        std::getline(line, breaker, ',');
        while(std::getline(line, breaker, ',')) {
            int print = std::stod(breaker);
            matrix[row][print - 1] = adjList[row][adjcounter++];
        }
        row++;
    }
    for(int o = 0; o < matrixSize; o++){
        for(int p =0; p < matrixSize; p++){
            if(p == o){
                matrix[p][o].data = p+1;
            }
            std::cout << matrix[o][p].weight << " ";
        }
        std::cout << "\n";
    }std::cout << "\n";
    open.close();
    weights.close();
    distances.close();
}

void search::execute() {
    if(searchType == DFS){
        Node **temp = new Node*[matrixSize];
        for(int i =0; i <matrixSize; i++){
            temp[i] = new Node[matrixSize];
        }
        for(int i = 0; i < matrixSize; i++){
            for (int q =0; q<matrixSize; q++)
                temp[i][q] = matrix[i][q];
        }
        dfs A(adjList, matrix, 1 , 13, matrixSize);
    }
    else if(searchType == BFS) {
        Node **temp = new Node*[matrixSize];
        for(int i =0; i <matrixSize; i++){
            temp[i] = new Node[matrixSize];
        }
        for(int i = 0; i < matrixSize; i++){
            for (int q =0; q<matrixSize; q++)
                temp[i][q] = matrix[i][q];
        }
        bfs B(adjList, matrix, 1, 13, matrixSize);
    }
    else if(searchType == DIJSKTRA) {
        Node **temp = new Node*[matrixSize];
        for(int i =0; i <matrixSize; i++){
            temp[i] = new Node[matrixSize];
        }
        for(int i = 0; i < matrixSize; i++){
            for (int q =0; q<matrixSize; q++)
                temp[i][q] = matrix[i][q];
        }
        Dijkstra C(adjList, temp, 1, 13, matrixSize);
    }
    else if(searchType == A) {
        Node **temp = new Node*[matrixSize];
        for(int i =0; i <matrixSize; i++){
            temp[i] = new Node[matrixSize];
        }
        for(int i = 0; i < matrixSize; i++){
            for (int q =0; q<matrixSize; q++)
                temp[i][q] = matrix[i][q];
        }
        AStar D(adjList, temp, 1, 13, matrixSize);
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