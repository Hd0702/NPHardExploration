//
// Created by Hayden Donofrio on 10/28/18.
//

#include "Reader.h"
#include "AlgoBuilder.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Node.h"
#include <sstream>
#include<cmath>
int Reader::size = 0;
Node** Reader::Read(const char * fileName) {
    std::vector<std::vector<Node> > matrix;
    std::ifstream file(fileName);
    if(!file) {
        std::cerr << fileName << " could not be opened" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string reader;
    while(getline(file, reader)) {
        size ++;
        std::stringstream line(reader);
        std::string breaker;
        std::getline(line, breaker, ',');
        int start = stoi(breaker);
        Node add;
        add.id = start;
        std::vector<Node> items;
        std::getline(line,breaker, ',');
        add.x = stol(breaker);
        std::getline(line,breaker, ',');
        add.y = stol(breaker);
        std::getline(line,breaker, ',');
        add.z = stol(breaker);
        items.push_back(add);
        matrix.push_back(items);
    }
    for(int i =0; i < matrix.size(); i++){
        std::vector<Node> inner;
        for(int j = 0; j < matrix.size(); j++){
            Node look;
            if(i != j){
                //distance is the difference from the original to the current node source
                look.id = j+1;
                look.x = -matrix[i][0].x + matrix[j][0].x;
                look.y = -matrix[i][0].y+ matrix[j][0].y;
                look.z = -matrix[i][0].z+ matrix[j][0].z;
                look.distance = sqrt(pow(look.x,2) + pow(look.y,2) + pow(look.z,2));
                matrix[i].push_back(look);
            }
        }
    }
    return CreateMatrix(matrix);
}
Node ** Reader::CreateMatrix( std::vector<std::vector<Node> > mat) {
    Node ** matrix = new Node*[size];
    for (int i =0; i < size; i++){
        matrix[i] = new Node[size];
    }
    int i =0;
    for (auto & j: mat) {
       for(auto &k: j){
           matrix[i][k.id-1] = k;
       }
        i++;
    }
    return matrix;
}