//
// Created by Hayden Donofrio on 9/10/18.
//

#include "AStar.h"
#include <queue>
#include <iostream>

AStar::AStar(std::vector<std::vector<Node> > &adjList, Node **matrix, int start, int end, int size) : matrixSize(size) {
    executeList(adjList, start, end);
    Node **copy = new Node *[matrixSize];
    for (int j = 0; j < matrixSize; j++) {
        copy[j] = new Node[matrixSize];
        for (int h = 0; h < matrixSize; h++) {
            copy[j][h] = matrix[j][h];
        }
    }
    executeMatrix(copy, start, end);
    for (int i = 0; i < matrixSize; i++) {
        delete[] copy[i];
    }
    delete[]copy;
}

void AStar::executeList(std::vector<std::vector<Node> > adjList, int start, int end) {
    int nodesSearched = 1;
    int distance = 0;
    auto begin = std::chrono::high_resolution_clock::now();
    std::priority_queue<Node> items;
    //set starting location
    int counter = 0;
    for (auto &J: adjList) {
        J[0].distance = INT32_MAX;
        J[0].weight = INT32_MAX;
    }
    adjList[start - 1][0].distance = 0;
    adjList[start - 1][0].weight = 0;
    //update og distance values
    for (auto J = adjList[start - 1].begin(); J != adjList[start - 1].end(); J++) {
        adjList[J->data - 1][0].distance = J->distance;
        adjList[J->data - 1][0].weight = J->weight;
    }
    for (auto &J: adjList) {
        items.push(J[0]);
    }
    auto location = adjList[start - 1].begin();
    location->visited = true;
    int totalWeight = 0;
    Node min;
    min.data = start;
    while (!items.empty()) {
        //skip first node
        if (min.data != start) {
            totalWeight = min.weight;
            adjList[min.data - 1][0].visited = true;
        } else {
            min = *location;
            min.distance = 0;
            min.weight = 0;
        }
        if (items.top().data == end && items.top().data != INT32_MAX) {
            std::list<int> path;
            auto finish = std::chrono::high_resolution_clock::now();
            unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(finish - begin).count();
            auto iter = adjList[items.top().data - 1].begin();
            while (iter->prev != nullptr) {
                path.push_front(iter->data);
                iter = (adjList[iter->prev->data - 1].begin());
            }
            path.push_front(start);
            search::stats(path, total, nodesSearched, items.top().distance, items.top().weight, "List");
            return;
        }
        //loop through each vertex
        items.pop();
        for (auto loop = adjList[min.data - 1].begin() + 1; loop != adjList[min.data - 1].end(); loop++) {
            //update each item
            //u = min
            if (!adjList[loop->data - 1][0].visited && !loop->visited &&
                min.distance + loop->distance + (loop->weight + totalWeight) <=
                adjList[loop->data - 1][0].distance + adjList[loop->data - 1][0].weight) {
                adjList[loop->data - 1][0].distance = min.distance + loop->distance;
                adjList[loop->data - 1][0].weight = totalWeight + loop->weight;
                loop->visited = true;
                nodesSearched++;
                adjList[loop->data - 1][0].prev = &adjList[min.data - 1][0];
                items.push(adjList[loop->data - 1][0]);
            }
        }
        //loop through each vertex and update its value
        min = items.top();
    }
}

void AStar::executeMatrix(Node **matrix, int start, int end) {
    int nodesSearched = 1;
    int distance = 0;
    auto begin = std::chrono::high_resolution_clock::now();
    std::priority_queue<Node> items;
    //set starting location
    int counter = 0;
    for (int i = 0; i < matrixSize; i++) {
        matrix[i][i].distance = INT32_MAX;
        matrix[i][i].weight = INT32_MAX;
    }
    matrix[start - 1][start - 1].distance = 0;
    matrix[start - 1][start - 1].weight = 0;
    for (int i = 0; i < matrixSize; i++) {
        if (matrix[start - 1][i].data != 0) {
            matrix[i][i].distance = matrix[start - 1][i].distance;
        }
    }
    //update og distance values
    for (int i = 0; i < matrixSize; i++) {
        items.push(matrix[i][i]);
    }
    matrix[start - 1][start - 1].visited = true;
    Node min;
    min.distance = 0;
    min.data = start;
    while (!items.empty()) {
        //skip first node
        if (min.data != start) {
            min = items.top();
            matrix[min.data - 1][min.data - 1].visited = true;
        }
        if (min.data == end && min.data != INT32_MAX) {
            auto finish = std::chrono::high_resolution_clock::now();
            unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(finish - begin).count();
            std::list<int> path;
            auto iter = &matrix[end - 1][end - 1];
            while (iter->prev != nullptr) {
                path.push_front(iter->data);
                iter = &(matrix[iter->prev->data - 1][iter->prev->data - 1]);
            }
            path.push_front(start);
            search::stats(path, total, nodesSearched, items.top().distance, items.top().weight, "Matrix");
            return;
        }
        //loop through each vertex
        items.pop();
        for (int i = 0; i < matrixSize; i++) {
            //for(auto loop = matrix[min.data-1].begin()+1; loop != adjList[min.data-1].end(); loop++) {
            //update each item
            if (matrix[min.data - 1][i].data != 0) {
                nodesSearched++;
                if (!matrix[i][i].visited && !matrix[min.data - 1][i].visited) {
                    //we need to get minimum distance in unvisited nodes
                    if (min.distance + matrix[min.data - 1][i].distance +
                        (matrix[min.data - 1][i].weight + min.weight) <=
                        (matrix[i][i].distance + matrix[i][i].weight)) {
                        matrix[i][i].distance = min.distance + matrix[min.data - 1][i].distance;
                        matrix[min.data - 1][i].visited = true;
                        matrix[i][i].weight = min.weight + matrix[min.data - 1][i].weight;
                        Node NodeWithIndex = matrix[i][i];
                        matrix[i][i].prev = &matrix[min.data - 1][min.data - 1];
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