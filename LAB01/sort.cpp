//
// Created by Hayden Donofrio on 9/1/18.
//

#include "sort.h"
#include <iostream>
#include <fstream>
#include "bubbleSort.h"
#include "insertionSort.h"
#include "mergeSort.h"

void sort::load(const char * fileName) {
    data.clear();
    std::cout <<"Loading: " << fileName << std::endl;
    std::ifstream file(fileName);
    if(!file) {
        std::cerr << fileName <<" could not be opened" << std::endl;
        exit(EXIT_FAILURE);
    }
    else {
        int item = 0;
        file >> item;
        file.ignore();
        while(file.good()) {
            file >>item;
            data.push_back(item);
            file.ignore();
            if(file.eof()) break;
        }
    }
    file.close();
}
//executes sort
void sort::execute() {
    if(sortType == Bubble) {
        //bubbleSort<int> bubble(data);
    }
    else if(sortType == Merge) {
        mergeSort<int> merge(data);
    }
    else if(sortType == Insertion) {
        //insertionSort<int> insert(data);
    }
}
//prints data to screen (probably wont be used)
void sort::display() {

}
//last
void sort::stats(){

}
//sets sort type
void sort::select(algorithm::sorts item) {
    sortType = item;
}
//saves to file
void sort::save(const char * fileName) {
    //std::cout <<"Saving: " << fileName << std::endl;
}
//this method should be blank
void sort::configure() {

}