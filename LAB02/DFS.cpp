//
// Created by Hayden Donofrio on 9/10/18.
//
#include <stack>
#include <array>
#include "dfs.h"
dfs::dfs(std::vector<std::vector<Node> >  adjList, Node ** matrix, int start, int end, int Size) {
    //now we execute both
    matrixSize = Size;
    executeIterativeList(adjList, start, end);
    executeIterativeMatrix(matrix, start, end);
    //set matrix back to unvisited
    for(int i = 0; i < matrixSize; i++){
        for (int q =0; q<matrixSize; q++)
            matrix[i][q].visited = false;
    }
    executeRecursiveList(adjList ,start, end);
    executeRecrusiveMatrix(matrix, start, end);
}

void dfs::executeIterativeList(std::vector<std::vector<Node> >  adjList, int start, int end) {
//execute iterative search for adjlist
    std::stack<Node> Items;
    auto iter = adjList[start-1].begin();
    iter->visited = true;
    Items.push(*iter);
    while(Items.size() != 0) {
        //get top of stack
        Node item = Items.top();
        Items.pop();
        //now find all non-visited nodes and add them to the stack
        for(iter = adjList[item.data-1].begin()+1;iter != adjList[item.data-1].end(); iter++ ){
            if (iter->data == end){
                return;
            }
            //check og for visited
            auto checker = adjList[iter->data-1].begin();
            if(!checker->visited){
                //set instance to true and set starting place to true
                checker->visited = true;
                Items.push(*iter);
            }
        }
    }
}
void dfs::executeIterativeMatrix(Node ** matrix, int start, int end) {
    std::stack<int> Items;
    Node *iter = &matrix[start-1][0];
    iter->visited = true;
    Items.push(start);
    while(Items.size() != 0) {
        //get top of stack
        int item = Items.top();
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

void dfs::executeRecursiveList(std::vector<std::vector<search::Node> > adjList, int start, int end) {
    if(start == end)
        return;
    adjList[start-1][0].visited = true;
    for(auto iter = adjList[start-1].begin()+1; iter != adjList[start-1].end(); iter++) {
        if(!adjList[iter->data-1][0].visited) {

            dfs::executeRecursiveList(adjList, iter->data, end);
        }
    }
}

void dfs::executeRecrusiveMatrix(Node ** matrix, int start, int end) {
    if (start == end)
        return;
    matrix[start-1][start-1].visited = true;
    for(int i =0; i < matrixSize; i++){
        if(matrix[start-1][i].data != 0 && !matrix[i][i].visited)
            dfs::executeRecrusiveMatrix(matrix, i+1, end);
    }
}