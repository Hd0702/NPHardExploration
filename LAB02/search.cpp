//
// Created by Hayden Donofrio on 9/10/18.
//
#include "search.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include "dfs.h"
#include "bfs.h"
#include "Dijkstra.h"
#include "AStar.h"

//load in fileName and create list or matrix
std::string search::algoType = "";
algorithm::searches search::searchType = DFS;
std::vector<std::list<int> > search::finalPath;
std::vector<int> search::nodesExplored;
std::string search::algoContainer;
std::vector<unsigned  int> search::tTime;
std::vector<double> search::distance;
std::vector<double> search::cost;
std::vector<std::string> search::types;

void search::load(const char *searchName, const char *Weights, const char *distance) {
    matrixSize = 0;
    adjList.clear();
    std::ifstream open(searchName);
    if (!open) {
        std::cerr << searchName << " could not be opened";
        exit(EXIT_FAILURE);
    }
    std::ifstream weights(Weights);
    if (!weights) {
        std::cerr << Weights << " could not be opened";
        exit(EXIT_FAILURE);
    }
    std::ifstream distances(distance);
    if (!distances) {
        std::cerr << distance << " could not be opened";
        exit(EXIT_FAILURE);
    }
    //first get datapoints
    std::string reader = "";
    while (getline(open, reader)) {
        matrixSize++;
        std::stringstream line(reader);
        int item = 0;
        std::string breaker;
        std::vector<Node> points;
        //get first
        std::getline(line, breaker, ',');
        Node add;
        add.x = 0;
        add.y = 0;
        add.z = 0;
        add.weight = 0;
        add.data = std::stod(breaker);
        points.push_back(add);
        //seperate Node stuct for respective Node
        //set pointers to new nodes
        while (std::getline(line, breaker, ',')) {
            Node add;
            add.x = 0;
            add.y = 0;
            add.z = 0;
            add.weight = 0;
            add.data = std::stod(breaker);
            points.push_back(add);
        }
        adjList.push_back(points);
    }
    reader.clear();
    //now beginning positions for each
    int counter = 0;
    while (getline(distances, reader)) {
        std::stringstream line(reader);
        int item = 0;
        double coords[3];
        std::string breaker;
        //seperate Node stuct for respective Node
        std::getline(line, breaker, ',');
        double index = std::stod(breaker);
        int counterin = 0;
        while (std::getline(line, breaker, ',')) {
            coords[counterin++] = std::stod(breaker);
        }
        adjList[counter][0].x = coords[0];
        adjList[counter][0].y = coords[1];
        adjList[counter][0].z = coords[2];
        adjList[counter][0].distance = pow(coords[0], 2) + pow(coords[1], 2) + pow(coords[2], 2);
        counter++;
    }
    //now calculate the rest of the distance
    for (int i = 0; i < matrixSize; i++) {
        //go through each Node and calculate distance based off data
        auto start = adjList[i].begin();
        for (auto iter = adjList[i].begin() + 1; iter != adjList[i].end(); iter++) {
            auto firstNew = adjList[iter->data - 1].begin();
            iter->distance = pow((firstNew->x - start->x), 2) +
                             pow((firstNew->y - start->y), 2) +
                             pow((firstNew->z - start->z), 2);
        }
    }
    //now for weights
    reader.clear();
    while (getline(weights, reader)) {
        std::stringstream line(reader);
        std::string breaker;
        //seperate Node stuct for respective Node
        std::getline(line, breaker, ',');
        int firstitem = std::stod(breaker);
        auto first = adjList[firstitem - 1].begin();
        //now get second
        std::getline(line, breaker, ',');
        int seconditem = std::stod(breaker);
        std::getline(line, breaker, ',');
        double weight = std::stod(breaker);
        for (auto &x: adjList[firstitem - 1]) {
            if (x.data == seconditem) {
                x.weight = weight;
            }
        }
        //now get weight
    }
    //now for matrix
    open.clear();
    open.seekg(0, std::ios::beg);
    matrix = new Node *[matrixSize];
    for (int i = 0; i < matrixSize; i++) {
        matrix[i] = new Node[matrixSize];
    }
    reader.clear();
    int row = 0;
    while (getline(open, reader)) {
        int adjcounter = 1;
        std::stringstream line(reader);
        std::string breaker;
        //remove first element
        std::getline(line, breaker, ',');
        while (std::getline(line, breaker, ',')) {
            int print = std::stod(breaker);
            matrix[row][print - 1] = adjList[row][adjcounter++];
        }
        row++;
    }
    for (int o = 0; o < matrixSize; o++) {
        for (int p = 0; p < matrixSize; p++) {
            if (p == o) {
                matrix[p][o].data = p + 1;
            }
        }
    }
    open.close();
    weights.close();
    distances.close();
}

//maybe just run execute 100 times, save each time and send its stats
void search::execute(int start, int end) {
    Node **copy = cloneMatrix();
    if (searchType == DFS) {
        search::algoType = "DFS";
        dfs A(adjList, copy, start, end, matrixSize);
    } else if (searchType == BFS) {
        search::algoType = "BFS";
        bfs B(adjList, copy, start, end, matrixSize);
    } else if (searchType == DIJSKTRA) {
        search::algoType = "Dijkstra";
        Dijkstra C(adjList, copy, start, end, matrixSize);
    } else if (searchType == A) {
        search::algoType = "A*";
        AStar D(adjList, copy, start, end, matrixSize);
    }
    for (int i = 0; i < matrixSize; i++) {
        delete[] copy[i];
    }
    delete[] copy;
}

void search::display() {

}

void search::stats(std::list<int> finalPath, unsigned int time, int nodesExplored, double distance, double cost,
                   std::string type) {
    //might want to change this to sending in values and pushing them based on enum
    std::cout << "\nAlgorithim: " << search::algoType << std::endl;
    std::cout << "Type: " << type << std::endl;
    search::types.push_back(search::algoType + " " + type);
    algoContainer = type;
    std::cout << "Final Path: ";
    for (auto iter = finalPath.begin(); iter != finalPath.end(); iter++) {
        std::cout << *iter << " ";
    }
    search::finalPath.push_back(finalPath);
    std::cout << "\nNodes searched: " << nodesExplored << std::endl;
    search::nodesExplored.push_back(nodesExplored);
    std::cout << "Time taken(microseconds) " << time << std::endl;
    search::tTime.push_back(time);
    std::cout << "Distance Taken: " << distance << std::endl;
    search::distance.push_back(distance);
    if (searchType == A) {
        std::cout << "Total cost: " << cost << std::endl;
        search::cost.push_back(cost);
    }
}

void search::select(int select) {
    searchType = algorithm::searches(select);
}

//Perform test 100 times and record both raw and normalized values into output file
void search::save(const char *fileName) {
    std::ifstream check(fileName);

    std::ofstream out;
    // std::ios::app is the open mode "append" meaning
    // new data will be written to the end of the file.
    out.open(fileName, std::ios::app);
    if(!check.good()) {
        out << "Search Type,Time,Start,End,Number of Nodes,Path,Distance,Total Nodes Visited,Cost\n";
    }
    check.close();
    int counter = 0;
    for(auto & item : search::finalPath) {
        out << types[counter] << "," << search::tTime[counter] << "," << item.front() << "," << item.back() << ","
            <<item.size() << ",";
        for(auto element = item.begin(); element != item.end(); element++){
            if(*element != item.back())
                out << *element << "->";
        }
        out << item.back() << "," << search::distance[counter] << "," << search::nodesExplored[counter];
        if (searchType == A) { out << "," << search::cost[counter]; }
        out << '\n';
        counter++;
    }
    search::nodesExplored.clear();
    search::tTime.clear();
    search::finalPath.clear();
    search::distance.clear();
    search::types.clear();
    out.close();

}

void search::configure() {
}

Node **search::cloneMatrix() {
    Node **copy = new Node *[matrixSize];
    for (int i = 0; i < matrixSize; i++) {
        copy[i] = new Node[matrixSize];
        for (int j = 0; j < matrixSize; j++) {
            copy[i][j] = matrix[i][j];
        }
    }
    return copy;
}

search::~search() {
    if (matrixSize > 1) {
        for (int i = 0; i < matrixSize; i++)
            delete[] matrix[i];
        delete[] matrix;
    }
}