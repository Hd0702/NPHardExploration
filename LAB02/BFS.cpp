//
// Created by Hayden Donofrio on 9/10/18.
//

#include "bfs.h"
#include <iostream>
#include <list>

bfs::bfs(std::vector<std::vector<Node> > adjList, Node **matrix, int start, int end, int size) : officialStart(start) {
    //now we execute both
    matrixSize = size;
    officialStart = start;
    executeIterativeList(adjList, start, end);
    Node **copy = new Node *[matrixSize];
    for (int j = 0; j < matrixSize; j++) {
        copy[j] = new Node[matrixSize];
        for (int h = 0; h < matrixSize; h++) {
            copy[j][h] = matrix[j][h];
        }
    }
    executeIterativeMatrix(copy, start, end);
    for (int i = 0; i < matrixSize; i++) {
        delete[] copy[i];
    }
    delete[]copy;
    std::queue<int> queue;
    queue.push(officialStart);
    auto b = std::chrono::high_resolution_clock::now();
    executeRecursiveList(adjList, queue, end);
    auto f = std::chrono::high_resolution_clock::now();
    auto final = std::chrono::duration_cast<std::chrono::microseconds>(f - b).count();
    search::stats(path[0], final, searched, path[0].size()-1, 0, "Recursive List");
    //set up matrix stats and execute
    path.clear();
    searched = 1;
    copy = new Node *[matrixSize];
    for (int j = 0; j < matrixSize; j++) {
        copy[j] = new Node[matrixSize];
        for (int h = 0; h < matrixSize; h++) {
            copy[j][h] = matrix[j][h];
        }
    }
    std::queue<int> pass;
    pass.push(officialStart);
    auto begin = std::chrono::high_resolution_clock::now();
    executeRecrusiveMatrix(copy, pass, end);
    auto finish = std::chrono::high_resolution_clock::now();
    final = std::chrono::duration_cast<std::chrono::microseconds>(finish - begin).count();
    for (int i = 0; i < matrixSize; i++) {
        delete[] copy[i];
    }
    delete[]copy;
    search::stats(path[0], final, searched, path[0].size()-1, 0, "Recursive Matrix");
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
            unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(finish - begin).count();
            auto iter = adjList[current.data - 1].begin();
            while (iter->prev != nullptr) {
                path.push_front(iter->data);
                iter = (adjList[iter->prev->data - 1].begin());
            }
            path.push_front(start);
            search::stats(path, total, nodesSearched, path.size() - 1, 0, "Iterative List");
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
                adjList[iter->data - 1][0].distance = iter->distance + adjList[current.data - 1][0].distance;
                adjList[iter->data - 1][0].prev = &adjList[current.data - 1][0];
                items.push(*iter);
            }
            counter++;
        }
    }
}

void bfs::executeIterativeMatrix(Node **matrix, int start, int end) {
    int nodesSeached = 0;
    auto begin = std::chrono::high_resolution_clock::now();
    std::queue<int> Items;
    Node *iter = &matrix[start - 1][start - 1];
    iter->visited = true;
    Items.push(start);
    while (Items.size() != 0) {
        //get top of stack
        int item = Items.front();
        if (item == end) {
            auto finish = std::chrono::high_resolution_clock::now();
            unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(finish - begin).count();
            iter = &matrix[item - 1][item - 1];
            std::list<int> path;
            while (iter->prev != nullptr) {
                path.push_front(iter->data);
                iter = &(matrix[iter->prev->data - 1][iter->prev->data - 1]);
            }
            path.push_front(start);
            bfs::path.push_back(path);
            stats(path, total, nodesSeached, path.size() - 1, 0, "Iterative Matrix");
            return;
        }
        Items.pop();
        //now find all non-visited nodes and add them to the stack
        for (int i = 0; i < matrixSize; i++) {
            nodesSeached++;
            if (matrix[item - 1][i].data != 0 && item - 1 != i) {
                //check og for visited
                if (!matrix[i][i].visited) {
                    //set instance to true and set starting place to true
                    matrix[i][i].visited = true;
                    matrix[i][i].distance = matrix[item - 1][i].distance + matrix[item - 1][item - 1].distance;
                    matrix[i][i].prev = &matrix[item - 1][item - 1];
                    Items.push(i + 1);
                }
            }
        }
    }
}

void bfs::executeRecursiveList(std::vector<std::vector<Node> > &adjList, std::queue<int> &data, int end) {
    int location = data.front();
    if (location == end || data.empty()) {
        std::list<int> send;
        auto iter = adjList[end - 1].begin();
        while (iter->prev != nullptr) {
            send.push_front(iter->data);
            iter = (adjList[iter->prev->data - 1].begin());
        }
        send.push_front(officialStart);
        path.push_back(send);
        searchSize.push_back(searched);
        return;
    }
    data.pop();
    //set initial visit to true
    adjList[location - 1][0].visited = true;
    for (auto iter = adjList[location - 1].begin() + 1; iter != adjList[location - 1].end(); iter++) {
        searched++;
        if (!adjList[iter->data - 1][0].visited) {
            adjList[iter->data - 1][0].visited = true;
            adjList[iter->data - 1][0].prev = &adjList[location - 1][0];
            data.push(iter->data);
        }
    }
    bfs::executeRecursiveList(adjList, data, end);
}

void bfs::executeRecrusiveMatrix(Node **matrix, std::queue<int> &data, int end) {
    int location = data.front();
    if (location == end || data.empty()) {
        auto iter = &matrix[end - 1][end - 1];
        std::list<int> send;
        while (iter->prev != nullptr) {
            send.push_front(iter->data);
            iter = &(matrix[iter->prev->data - 1][iter->prev->data - 1]);
        }
        send.push_front(officialStart);
        path.push_back(send);
        searchSize.push_back(searched);
        return;
    }
    data.pop();
    //set initial visit to true
    matrix[location - 1][location - 1].visited = true;
    for (int i = 0; i < matrixSize; i++) {
        searched++;
        if (matrix[location - 1][i].data != 0 && !matrix[i][i].visited && location - 1 != i) {
            matrix[i][i].visited = true;
            matrix[i][i].prev = &matrix[location - 1][location - 1];
            data.push(i + 1);
        }
    }
    bfs::executeRecrusiveMatrix(matrix, data, end);
}