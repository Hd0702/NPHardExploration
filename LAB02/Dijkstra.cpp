//
// Created by Hayden Donofrio on 9/10/18.
//

#include "Dijkstra.h"
#include <map>
#include<queue>
#include <iostream>
Dijkstra::Dijkstra(std::vector<std::vector<Node> > adjList, Node **matrix, int start, int end, int size): matrixSize(size) {
    executeList(adjList, start, end);
    executeMatrix(matrix,start, end);
}

void Dijkstra::executeList(std::vector<std::vector<Node> > adjList, int start, int end) {
    int nodesSearched= 1; int distance = 0;
    auto begin = std::chrono::high_resolution_clock::now();
    std::priority_queue<Node> items;
    //set starting location
    int counter = 0;
    for(auto & J: adjList) {
        J[0].distance = INT32_MAX;
    }
    adjList[start-1][0].distance = 0;
    //update og distance values
    for(auto J= adjList[start-1].begin(); J != adjList[start-1].end(); J++){
        adjList[J->data-1][0].distance = J->distance;
    }
    for(auto & J: adjList) {
        items.push(J[0]);
    }
    auto location = adjList[start-1].begin();
    location->visited = true;
    Node min;
    min.data = start;
    while(!items.empty()) {
        //skip first node
        if (min.data != start) {
            min = items.top();
            adjList[min.data-1][0].visited = true;
        }
        else {
            min = *location;
            min.distance = 0;
        }
        if(items.top().data == end && items.top().data != INT32_MAX) {
            auto finish = std::chrono::high_resolution_clock::now();
            unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(finish-begin).count();
            std::list<int> path;
            auto iter = adjList[end-1].begin();
            while(iter->prev != nullptr){
                path.push_front(iter->data);
                iter = (adjList[iter->prev->data-1].begin());
            }
            path.push_front(start);
            search::stats(path, total, nodesSearched, items.top().distance, 0, " List");
            return;
        }
        //loop through each vertex
        items.pop();
        int counter =1;
        for(auto loop = adjList[min.data-1].begin()+1; loop != adjList[min.data-1].end(); loop++) {
            nodesSearched++;
            //update each item
            //u = min
            if(!adjList[loop->data-1][0].visited && min.distance + loop->distance <= adjList[loop->data-1][0].distance) {
                adjList[loop->data-1][0].distance = min.distance + loop->distance;
                adjList[loop->data-1][0].prev = &adjList[min.data-1][0];
                items.push(adjList[loop->data-1][0]);
            }
            counter++;
        }
        //loop through each vertex and update its value
        min = items.top();
    }

}

void Dijkstra::executeMatrix(Node **matrix, int start, int end) {
    int nodesSearched= 1; int distance = 0;
    auto begin = std::chrono::high_resolution_clock::now();
    std::priority_queue<Node> items;
    //set starting location
    //set all weights to 0
    int counter = 0;
    for(int i =0; i < matrixSize; i++) {
        matrix[i][i].distance = INT32_MAX;
    }
    matrix[start-1][start-1].distance = 0;
    for(int i =0; i < matrixSize; i++){
        if(matrix[start-1][i].data != 0) {
            matrix[i][i].distance = matrix[start-1][i].distance;
        }
    }
    //update og distance values
    for(int i =0; i < matrixSize; i++) {
        items.push(matrix[i][i]);
    }
    matrix[start-1][start-1].visited = true;
    Node min;
    min.distance = 0; min.data= start;
    for(int o = 0; o < matrixSize; o++){
        for(int p =0; p < matrixSize; p++){
            matrix[o][p].weight = 0;
        }
    }
    while(!items.empty()) {
        //skip first node
        if (min.data != start) {
            min = items.top();
            matrix[min.data-1][min.data-1].visited = true;
        }
        if(min.data == end && min.data != INT32_MAX) {
            auto finish = std::chrono::high_resolution_clock::now();
            unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(finish-begin).count();
            std::list<int> path;
            auto iter = &matrix[end-1][end-1];
            while(iter->prev != nullptr){
                path.push_front(iter->data);
                iter = &(matrix[iter->prev->data-1][iter->prev->data-1]);
            }
            path.push_front(start);
            search::stats(path, total, nodesSearched, items.top().distance, 0, "Matrix");
            return;
        }
        //loop through each vertex
        items.pop();
        for(int i = 0; i < matrixSize; i++){
            nodesSearched++;
            //update each item
            if(matrix[min.data-1][i].data != 0) {
                if (!matrix[i][i].visited) {
                    if(min.distance + matrix[min.data - 1][i].distance <= matrix[i][i].distance) {
                        matrix[i][i].distance = min.distance + matrix[min.data - 1][i].distance;
                        //adjList[loop->data-1][0].prev = &adjList[min.data-1][0];
                        matrix[i][i].prev = &matrix[min.data-1][min.data-1];
                        Node NodeWithIndex = matrix[i][i];
                        NodeWithIndex.data = i + 1;
                        items.push(NodeWithIndex);
                    }
                }
            }
        }
        //loop through each vertex and update its value
        min = items.top();
    }
}