//
// Created by Hayden Donofrio on 9/10/18.
//

#include "bfs.h"

bfs::bfs(std::vector<std::vector<Node> >  adjList, Node ** matrix, int start, int end, int size) {
    //now we execute both
    matrixSize = size;
    executeIterativeList(adjList, start, end);
    for(int i = 0; i < matrixSize; i++){
        for (int q =0; q<matrixSize; q++)
            matrix[i][q].visited = false;
    }
    executeIterativeMatrix(matrix, start, end);
    //set matrix back to unvisited
    for(int i = 0; i < matrixSize; i++){
        for (int q =0; q<matrixSize; q++)
            matrix[i][q].visited = false;
    }
    bfsQueue.push(start);
    executeRecursiveList(adjList ,bfsQueue, end);
    std::queue<int> empty;
    std::swap(empty, bfsQueue);
    bfsQueue.push(start);
    executeRecrusiveMatrix(matrix, bfsQueue, end);
    for(int i = 0; i < matrixSize; i++){
        for (int q =0; q<matrixSize; q++)
            matrix[i][q].visited = false;
    }
}

void bfs::executeIterativeList(std::vector<std::vector<Node> > adjList, int start, int end) {
    std::queue<Node> items;
    auto iterStart = adjList[start-1].begin();
    iterStart->visited = true;
    items.push(*iterStart);
    while(items.size() != 0) {
        Node current = items.front();
        items.pop();
        //get all non-visited nodes and add them to the queue
        for(auto iter = adjList[current.data-1].begin()+1;iter != adjList[current.data-1].end(); iter++ ){
            if (iter->data == end){
                return;
            }
            //check og for visited
            auto checker = adjList[iter->data-1].begin();
            if(!checker->visited){
                //set instance to true and set starting place to true
                checker->visited = true;
                items.push(*iter);
            }
        }
    }
}

void bfs::executeIterativeMatrix(Node ** matrix, int start, int end) {
    std::queue<int> Items;
    Node *iter = &matrix[start-1][0];
    iter->visited = true;
    Items.push(start);
    while(Items.size() != 0) {
        //get top of stack
        int item = Items.front();
        Items.pop();
        //now find all non-visited nodes and add them to the stack
        for(int i = 0; i < matrixSize; i++){
            if(matrix[item-1][i].data != 0) {
                if (matrix[item - 1][i].data == end) {
                    return;
                }
                //check og for visited
                if (!matrix[i][i].visited) {
                    //set instance to true and set starting place to true
                    matrix[i][i].visited = true;
                    Items.push(i+1);
                }
            }
        }
    }
}

void bfs::executeRecursiveList(std::vector<std::vector<search::Node> >  adjList, std::queue<int> & data, int end) {
    int location = data.front();
    if(location == end || data.empty())
        return;
    data.pop();
    //set initial visit to true
    adjList[location-1][0].visited = true;
    for(auto iter = adjList[location-1].begin()+1; iter != adjList[location-1].end(); iter++) {
        if(!adjList[iter->data-1][0].visited) {
            adjList[iter->data-1][0].visited = true;
            data.push(iter->data);
        }
    }
    bfs::executeRecursiveList(adjList, data, end);
}

void bfs::executeRecrusiveMatrix(Node ** matrix, std::queue<int> & data, int end) {
    int location = data.front();
    if(location == end || data.empty())
        return;
    data.pop();
    //set initial visit to true
    matrix[location-1][location-1].visited = true;
    for(int i = 0; i < matrixSize; i++) {
        if(matrix[location-1][i].data != 0 && !matrix[i][i].visited) {
            matrix[i][i].visited = true;
            data.push(i+1);
        }
    }
    bfs::executeRecrusiveMatrix(matrix, data, end);
}