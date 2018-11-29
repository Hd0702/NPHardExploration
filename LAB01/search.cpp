//
// Created by Hayden Donofrio on 9/10/18.
//

#include "search.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
//load in fileName and create list or matrix
search::~search() {
    //destruct adj matrix here
}

void search::load(const char * fileName, const char * loadType) {
    adjList.clear();
    int matrixSize = 0;
    std::ifstream open(fileName);
    if(!open) {
        std::cerr << fileName << " could not be opened";
        exit(EXIT_FAILURE);
    }
    std::string reader = "";
    while(getline(open, reader)) {
        matrixSize++;
        std::stringstream line(reader);
        int item = 0;
        std::string breaker;
        std::list<int> points;
        while(std::getline(line, breaker, ',')){
            int print = std::stoi(breaker);
            points.push_back(print);
        }
        adjList.push_back(points);
    }
    //now for matrix
    open.clear();
    open.seekg(0, std::ios::beg);
    matrix = new int*[matrixSize];
    for(int i =0; i < matrixSize; i++) {
        matrix[i] = new int[matrixSize];
        for(int x = 0; x < matrixSize; x++)
            matrix[i][x] = 0;
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