//
// Created by Hayden Donofrio on 9/10/18.
//

#include "bfs.h"
#include <iostream>
#include <list>

bfs::bfs(std::vector<std::vector<Node> >  adjList, Node ** matrix, int start, int end, int size) : officialStart(start) {
    //now we execute both
    matrixSize = size;
    executeIterativeList(adjList, start, end);
    executeIterativeMatrix(matrix, start, end);
    //set matrix back to unvisited
    for(int i = 0; i < matrixSize; i++){
        for (int q =0; q<matrixSize; q++)
            matrix[i][q].visited = false;
    }
    bfsQueue.push(start);
    auto begin = std::chrono::high_resolution_clock::now();
    executeRecursiveList(adjList ,bfsQueue, end);
    auto finish = std::chrono::high_resolution_clock::now();
    unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(finish-begin).count();
    search::stats(finalPath, total, searched, 0, 0, "Recursive List");
    finalPath.clear();
    searched = 1;
    std::queue<int> empty;
    std::swap(empty, bfsQueue);
    bfsQueue.push(start);
    begin = std::chrono::high_resolution_clock::now();
    executeRecrusiveMatrix(matrix, bfsQueue, end);
    finish = std::chrono::high_resolution_clock::now();
    total = std::chrono::duration_cast<std::chrono::microseconds>(finish-begin).count();
    search::stats(finalPath, total, searched, 0, 0, "Recursive Matrix");
}

void bfs::executeIterativeList(std::vector<std::vector<Node> > adjList, int start, int end) {
    auto begin = std::chrono::high_resolution_clock::now();
    int nodesSearched = 1;
    std::queue<Node> items;
    auto iterStart = adjList[start - 1].begin();
    iterStart->visited = true;
    items.push(*iterStart);
    while (items.size() != 0) {
        Node current = items.front();
        if (current.data == end) {
            std::list<int> path;
            auto finish = std::chrono::high_resolution_clock::now();
            unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(finish-begin).count();
            auto iter = adjList[current.data-1].begin();
            path.push_front(end);
            while (iter->prev != nullptr) {
                path.push_front(iter->data);
                iter = (adjList[iter->prev->data - 1].begin());
            }
            path.push_front(start);
            search::stats(path, total, nodesSearched, 0, 0, "Iterative List");
            return;
        }
        items.pop();
        //get all non-visited nodes and add them to the queue
        int counter = 1;
        for (auto iter = adjList[current.data - 1].begin() + 1; iter != adjList[current.data - 1].end(); iter++) {
            nodesSearched++;
                //check og for visited
                auto checker = adjList[iter->data - 1].begin();
                if (!checker->visited) {
                    //set instance to true and set starting place to true
                    checker->visited = true;
                    adjList[current.data - 1][0].next = &adjList[current.data-1][counter];
                    adjList[iter->data - 1][0].prev = &adjList[current.data - 1][0];
                    items.push(*iter);
                }
                counter++;
            }
        }
    }

void bfs::executeIterativeMatrix(Node ** matrix, int start, int end) {
    int nodesSeached = 0;
    auto begin = std::chrono::high_resolution_clock::now();
    std::queue<int> Items;
    Node *iter = &matrix[start-1][start-1];
    iter->visited = true;
    Items.push(start);
    while(Items.size() != 0) {
        //get top of stack
        int item = Items.front();
        if (item == end) {
            auto finish = std::chrono::high_resolution_clock::now();
            unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(finish-begin).count();
            iter = &matrix[item-1][item-1];
            std::list<int> path;
            path.push_front(end);
            while (iter->prev != nullptr) {
                path.push_front(iter->data);
                iter = &(matrix[iter->prev->data - 1][iter->prev->data - 1]);
            }
            path.push_front(start);
            stats(path, total, nodesSeached, 0, 0 ,"Iterative Matrix");
            return;
        }
        Items.pop();
        //now find all non-visited nodes and add them to the stack
        for(int i = 0; i < matrixSize; i++){
            nodesSeached++;
            if(matrix[item-1][i].data != 0 && item-1 != i) {
                //check og for visited
                if (!matrix[i][i].visited) {
                    //set instance to true and set starting place to true
                    matrix[i][i].visited = true;
                    //adjList[iter->data - 1][0].prev = &adjList[current.data - 1][0];
                    matrix[i][i].prev = &matrix[item-1][item-1];
                    Items.push(i+1);
                }
            }
        }
    }
}

void bfs::executeRecursiveList(std::vector<std::vector<Node> > & adjList, std::queue<int> & data, int end) {
    int location = data.front();
    if(location == end || data.empty()) {
        auto iter = adjList[location-1].begin();
        while (iter->prev != nullptr) {
            finalPath.push_front(iter->data);
            iter = (adjList[iter->prev->data - 1].begin());
        }
        finalPath.push_front(officialStart);
        return;
    }
    data.pop();
    //set initial visit to true
    adjList[location-1][0].visited = true;
    for(auto iter = adjList[location-1].begin()+1; iter != adjList[location-1].end(); iter++) {
        searched++;
        if(!adjList[iter->data-1][0].visited) {
            adjList[iter->data-1][0].visited = true;
            adjList[iter->data-1][0].prev = &adjList[location-1][0];
            data.push(iter->data);
        }
    }
    bfs::executeRecursiveList(adjList, data, end);
}

void bfs::executeRecrusiveMatrix(Node ** matrix, std::queue<int> & data, int end) {
    int location = data.front();
    if(location == end || data.empty()) {
        auto iter = &matrix[location-1][location-1];
        while (iter->prev != nullptr) {
            finalPath.push_front(iter->data);
            iter = &(matrix[iter->prev->data - 1][iter->prev->data - 1]);
        }
        finalPath.push_front(officialStart);
        return;
    }
    data.pop();
    //set initial visit to true
    matrix[location-1][location-1].visited = true;
    for(int i = 0; i < matrixSize; i++) {
        searched++;
        if(matrix[location-1][i].data != 0 && !matrix[i][i].visited && location-1 != i) {
            matrix[i][i].visited = true;
            matrix[i][i].prev = &matrix[location-1][location-1];
            data.push(i+1);
        }
    }
    bfs::executeRecrusiveMatrix(matrix, data, end);
}