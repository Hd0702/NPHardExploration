//
// Created by Hayden Donofrio on 9/10/18.
//

#include "AStar.h"
#include <queue>

AStar::AStar(std::vector<std::vector<Node> > &adjList, Node **matrix, int start, int end, int size): matrixSize(size) {
    executeList(adjList, start, end);
    executeMatrix(matrix,start, end);
}

void AStar::executeList(std::vector<std::vector<Node> > adjList, int start, int end) {
    //UPDATE TO ADD FOR TOTAL WEIGHTS
    std::priority_queue<Node> items;
    //set starting location
    int counter = 0;
    for(auto & J: adjList) {
        J[0].distance = INT32_MAX;
        J[0].weight = INT32_MAX;
    }
    //update og distance values
    for(auto J= adjList[start-1].begin(); J != adjList[start-1].end(); J++){
        adjList[J->data-1][0].distance = J->distance;
        adjList[J->data-1][0].weight = J->weight;
    }
    for(auto & J: adjList) {
        items.push(J[0]);
    }
    auto location = adjList[start-1].begin();
    location->visited = true;
    int totalWeight = 0;
    Node min;
    min.data = start;
    while(!items.empty()) {
        if(items.top().data == end && items.top().data != INT32_MAX)
            return;
        //skip first node
        if (min.data != start) {
            min = items.top();
            adjList[min.data-1][0].visited = true;
        }
        else {
            min = *location;
            min.distance = 0;
            min.weight = 0;
        }
        //loop through each vertex
        items.pop();
        for(auto loop = adjList[min.data-1].begin()+1; loop != adjList[min.data-1].end(); loop++) {
            //update each item
            //u = min
            if(!adjList[loop->data-1][0].visited && min.distance + loop->distance + (loop->weight + totalWeight) <= adjList[loop->data-1][0].distance + adjList[loop->data-1][0].weight) {
                adjList[loop->data-1][0].distance = min.distance + loop->distance;
                adjList[loop->data-1][0].weight = totalWeight + loop->weight;
                items.push(adjList[loop->data-1][0]);
            }
        }
        //loop through each vertex and update its value
        min = items.top();
    }
}

void AStar::executeMatrix(Node **matrix, int start, int end) {
    std::priority_queue<Node> items;
    //set starting location
    int counter = 0;
    for(int i =0; i < matrixSize; i++) {
        matrix[i][i].distance = INT32_MAX;
    }
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
    while(!items.empty()) {
        if(items.top().data == end && items.top().data != INT32_MAX)
            return;
        //skip first node
        if (min.data != start) {
            min = items.top();
            matrix[min.data-1][min.data-1].visited = true;
        }
        //loop through each vertex
        items.pop();
        for(int i = 0; i < matrixSize; i++){
            //for(auto loop = matrix[min.data-1].begin()+1; loop != adjList[min.data-1].end(); loop++) {
            //update each item
            if(matrix[min.data-1][i].data != 0) {
                if (!matrix[i][i].visited) {
                    if(min.distance + matrix[min.data - 1][i].distance +(matrix[min.data - 1][i].weight + min.weight) <= (matrix[i][i].distance + matrix[i][i].weight)) {
                        matrix[i][i].distance = min.distance + matrix[min.data - 1][i].distance;
                        matrix[i][i].weight = min.weight + matrix[min.data-1][i].weight;
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