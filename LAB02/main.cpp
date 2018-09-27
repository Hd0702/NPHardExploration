#include <iostream>
#include <string>
#include "search.h"
#include <ctime>
//get stats from seach that returns thing
int main(int argc, char ** argv) {
    srand(time(0));
    const char * sortTypes[4] = {"DFS", "BFS", "DIJKSTRA" , "A*" };
    algorithm * algos = new search();
    int start, end = 1;
    if(argc >= 3) {
        start = atoi(argv[1]);
        end = atoi(argv[2]);
    }
    //loop through all algo types and their corresponding sizes
    algos->load("graph.txt", "weights.txt", "positions.txt");
    for(int q = 0; q < 4; q++) {
        algos->select(q);
        start = rand() % 16 +1;
        end = rand() % 16 +1;
        algos->execute(start, end);
        algos->save("finalPaths.csv");
    }
    delete algos;
    return 0;
}