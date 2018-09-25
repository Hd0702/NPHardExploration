//
// Created by Hayden Donofrio on 9/10/18.
//
#include <stack>
#include "dfs.h"
#include <iostream>
#include <list>
dfs::dfs(std::vector<std::vector<Node> >  adjList, Node ** matrix, int start, int end, int Size) :officialStart(start) {
    //now we execute both
    matrixSize = Size;
    executeIterativeList(adjList, start, end);
    executeIterativeMatrix(matrix, start, end);
    //set matrix back to unvisited
    for(int i = 0; i < matrixSize; i++){
        for (int q =0; q<matrixSize; q++)
            matrix[i][q].visited = false;
    }
    auto begin = std::chrono::high_resolution_clock::now();
    executeRecursiveList(adjList ,start, end);
    auto finish = std::chrono::high_resolution_clock::now();
    unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(finish-begin).count();
    std::list<int> path;
    for(int i =0; i < RecursivePaths[0].size(); i++){
        path.push_back(RecursivePaths[0][i]);
    }
    search::stats(path, total, searched, 0, 0, "Recursive List");
    path.clear();
    searched = 1;
    begin = std::chrono::high_resolution_clock::now();
    executeRecrusiveMatrix(matrix, start, end);
    finish = std::chrono::high_resolution_clock::now();
    total = std::chrono::duration_cast<std::chrono::microseconds>(finish-begin).count();
    for(int i =0; i < RecursivePaths[0].size(); i++){
       path.push_back(RecursivePaths[0][i]);
    }
    search::stats(path, total, searched, 0, 0, "Recrusive Matrix");
}

void dfs::executeIterativeList(std::vector<std::vector<Node> >  adjList, int start, int end) {
//execute iterative search for adjlist
    auto begin = std::chrono::high_resolution_clock::now();
    int nodesSearched = 1;
    std::stack<Node> Items;
    auto iter = adjList[start-1].begin();
    iter->visited = true;
    Items.push(*iter);
    while(Items.size() != 0) {
        //get top of stack
        Node item = Items.top();
        if (item.data == end){
            std::list<int> data;
            item.next = &adjList[item.data-1][item.data-1];
            iter = adjList[start-1].begin();
            data.push_back(start);
            while(iter->next != nullptr){

                iter = (adjList[iter->next->data-1].begin());
                data.push_back(iter->data);
            }
            data.push_back(end);
            auto finish = std::chrono::high_resolution_clock::now();
            unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(finish-begin).count();
            search::stats(data, total, nodesSearched, 0, 0, "Iterative List");
            return;
        }
        Items.pop();
        //now find all non-visited nodes and add them to the stack
        int counter = 1;
        for(iter = adjList[item.data-1].begin()+1;iter != adjList[item.data-1].end(); iter++ ){
            //check og for visited
            auto checker = adjList[iter->data-1].begin();
            nodesSearched++;
            if(!checker->visited){
                //set instance to true and set starting place to true
                checker->visited = true;
                adjList[item.data-1][0].next = &adjList[item.data-1][counter];
                Items.push(*iter);
            }
            counter++;
        }
    }
}
void dfs::executeIterativeMatrix(Node ** matrix, int start, int end) {
    int nodesSearched = 1;
    auto begin = std::chrono::high_resolution_clock::now();
    std::stack<int> Items;
    Node *iter = &matrix[start-1][start-1];
    iter->visited = true;
    Items.push(start);
    while(Items.size() != 0) {
        //get top of stack
        int item = Items.top();
        if(item == end) {
            std::list<int> path;
            path.push_back(start);
            while(iter->next != nullptr){
                iter = &(matrix[iter->next->data-1][iter->next->data-1]);
                path.push_back(iter->data);
            }
            path.push_back(end);
            auto finish = std::chrono::high_resolution_clock::now();
            unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(finish-begin).count();
            search::stats(path, total, nodesSearched, 0, 0, "Iterative Matrix");
            return;
        }
        Items.pop();
        //now find all non-visited nodes and add them to the stack
        for(int i = 0; i < matrixSize; i++){
            nodesSearched++;
            if(matrix[item-1][i].data != 0 && item-1 != i) {
                //check og for visited
                if (!matrix[i][i].visited) {
                    //set instance to true and set starting place to true
                    matrix[i][i].visited = true;
                    matrix[item-1][item-1].next = &matrix[i][i];
                    Items.push(i+1);
                }
            }
        }
    }
}

void dfs::executeRecursiveList(std::vector<std::vector<Node> > & adjList, int start, int end) {
    if(start == end) {
        std::vector<int> path;
        auto iter = adjList[officialStart-1].begin();
        while(iter->next != nullptr){
            path.push_back(iter->data);
            iter = (adjList[iter->next->data-1].begin());
        }
        path.push_back(end);
        RecursivePaths.push_back(path);
        return;
    }
    adjList[start-1][0].visited = true;
    for(auto iter = adjList[start-1].begin()+1; iter != adjList[start-1].end(); iter++) {
        searched++;
        if(!adjList[iter->data-1][0].visited) {
            adjList[start-1][0].next = &(adjList[iter->data-1][0]);
            dfs::executeRecursiveList(adjList, iter->data, end);
        }
    }
}

void dfs::executeRecrusiveMatrix(Node ** matrix, int start, int end) {
    if (start == end) {
        std::vector<int> path;
        Node * iter = &matrix[officialStart-1][officialStart-1];
        while(iter->next != nullptr){
            path.push_back(iter->data);
            iter = &(matrix[iter->next->data-1][iter->next->data-1]);
        }
        path.push_back(end);
        RecursivePaths.push_back(path);
        return;
    }
    matrix[start-1][start-1].visited = true;
    for(int i =0; i < matrixSize; i++){
        searched++;
        if(matrix[start-1][i].data != 0 && !matrix[i][i].visited && start-1 != i)
            dfs::executeRecrusiveMatrix(matrix, i+1, end);
    }
}