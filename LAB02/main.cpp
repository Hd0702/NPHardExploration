#include <iostream>
#include <string>
#include "search.h"
int main(int argc, char ** argv) {
//TODO REMEMBER TO RUN EACH TEST 100 TIMES AND NORMALIZE
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
        //path string is the formatted strings for proper file names
        //algos->load(path.c_str(), inputTypes[i]);
        algos->execute(start, end);
        algos->save(sortTypes[q]);
    }
    delete algos;
    return 0;
}