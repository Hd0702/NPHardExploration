//
// Created by Hayden Donofrio on 9/10/18.
//
#include <stack>
#include "dfs.h"
#include <iostream>
#include <random>
dfs::dfs(std::vector<std::vector<Node> >  adjList, Node ** matrix, int start, int end, int Size) :officialStart(start) {
    //now we execute both
    matrixSize = Size;
    officialStart =start;
    executeIterativeList(adjList, start, end);
    executeIterativeMatrix(matrix, start, end);
    finalPath.clear();
    auto begin = std::chrono::high_resolution_clock::now();
    executeRecursiveList(adjList,start, end, 0);
    auto finish = std::chrono::high_resolution_clock::now();
    auto final = std::chrono::duration_cast<std::chrono::microseconds>(finish-begin).count();
    std::list<int> path;
    searchSize.clear();
    RecursivePaths.clear();
    search::stats(finalPath[0], final, searched, finalPath[0].size()-1, 0, "Recursive List");
    finalPath.clear();
    path.clear();
    distaces.clear();
    searched = 0;
    for(int j =0; j < matrixSize; j++) {
        matrix[j][0].distance = 0;
        for (int h = 0; h < matrixSize; h++) {
            matrix[h][j].visited = false;
            matrix[h][j].prev = nullptr;
        }
    }
    begin = std::chrono::high_resolution_clock::now();
    executeRecrusiveMatrix(matrix, start, end, 0);
    finish = std::chrono::high_resolution_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::microseconds>(finish-begin).count();
    search::stats(finalPath[0], total, searched, finalPath[0].size()-1, 0, "Recrusive Matrix");
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
            std::list<int> path;
            auto iter = adjList[item.data-1].begin();
            while (iter->prev != nullptr) {
                path.push_front(iter->data);
                iter = (adjList[iter->prev->data - 1].begin());
            }
            path.push_front(start);
            auto finish = std::chrono::high_resolution_clock::now();
            unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(finish-begin).count();
            search::stats(path, total, nodesSearched, path.size()-1, 0, "Iterative List");
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
                adjList[iter->data - 1][0].prev = &adjList[item.data - 1][0];
                Items.push(*iter);
            }
            counter++;
        }
    }
}
void dfs::executeIterativeMatrix(Node ** matrix, int start, int end) {
    int nodesSearched = 1;
    int thisDistance =0;
    auto begin = std::chrono::high_resolution_clock::now();
    std::stack<int> Items;
    Node *iter = &matrix[start-1][start-1];
    iter->visited = true;
    Items.push(start);
    while(Items.size() != 0) {
        //get top of stack
        int item = Items.top();
        if(item == end) {
            auto finish = std::chrono::high_resolution_clock::now();
            unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(finish-begin).count();
            iter = &matrix[item-1][item-1];
            std::list<int> path;
            while (iter->prev != nullptr) {
                path.push_front(iter->data);
                iter = &(matrix[iter->prev->data - 1][iter->prev->data - 1]);
            }
            finalPath.push_back(path);
            path.push_front(start);
            stats(path, total, nodesSearched, path.size()-1, 0 ,"Iterative Matrix");
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
                    thisDistance += matrix[item-1][i].distance;
                    matrix[i][i].distance = matrix[item-1][i].distance + matrix[item-1][item-1].distance;
                    matrix[i][i].prev = &matrix[item-1][item-1];
                    Items.push(i+1);
                }
            }
        }
    }
}

void dfs::executeRecursiveList(std::vector<std::vector<Node> > & adjList, int start, int end, int thisDistance) {
    if(start == end) {
        std::list<int> path;
        auto iter = &adjList[end-1][0];
        while(iter->prev != nullptr){
            path.push_front(iter->data);
            iter = iter->prev;
        }
        path.push_front(officialStart);
        finalPath.push_back(path);
        searchSize.push_back(searched);
        return;
    }
    adjList[start-1][0].visited = true;
    for(auto iter = adjList[start-1].begin()+1; iter != adjList[start-1].end(); iter++) {
        searched++;
        if(!adjList[iter->data-1][0].visited) {
            adjList[iter->data-1][0].visited = true;
            adjList[start-1][0].next = &(adjList[iter->data-1][0]);
            adjList[iter->data-1][0].prev = &adjList[start-1][0];
            thisDistance += iter->distance;
            dfs::executeRecursiveList(adjList, iter->data, end, thisDistance);
        }
    }
}

void dfs::executeRecrusiveMatrix(Node ** matrix, int start, int end, int thisDistance) {
    if (start == end) {
        std::list<int> path;
        Node * iter = &matrix[end-1][end-1];
        while(iter->prev != nullptr){
            path.push_front(iter->data);
            iter = &(matrix[iter->prev->data-1][iter->prev->data-1]);
        }
        searchSize.push_back(searched);
        path.push_front(officialStart);
        finalPath.push_back(path);
        return;
    }
    matrix[start-1][start-1].visited = true;
    for(int i =0; i < matrixSize; i++){
        searched++;
        if(matrix[start-1][i].data != 0 && !matrix[i][i].visited && start-1 != i) {
            matrix[i][i].prev = &matrix[start-1][start-1];
            thisDistance += matrix[start-1][i].distance;
            dfs::executeRecrusiveMatrix(matrix, i + 1, end, thisDistance);
        }
    }
}