//
// Created by Hayden Donofrio on 9/1/18.
//

#include "sort.h"
#include <iostream>
#include <fstream>
#include "bubbleSort.h"
#include "insertionSort.h"
#include "mergeSort.h"

int sort::dataSize = 0;
std::string sort::algoType = "";
std::string sort::dataType ="";

sort::sort() {

}
void sort::load(const char * fileName, const char * fileType) {
    sort::dataSize = 0;
    sort::dataType = fileType;
    data.clear();
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
            sort::dataSize++;
            if(file.eof()) break;
        }
    }
    file.close();
}
//executes sort
void sort::execute() {
    if(sortType == Bubble) {
        sort::algoType = "Bubble";
        bubbleSort<int> bubble(data);
    }
    else if(sortType == Merge) {
        sort::algoType = "Merge";
        mergeSort<int> merge(data);
    }
    else if(sortType == Insertion) {
        sort::algoType = "Insertion";
        insertionSort<int> insert(data);
    }
}
//prints data to screen (probably wont be used)
void sort::display() {
    for(auto & item: data) {
        std::cout << item << std::endl;
    }
}
//Prints algorithm name, execution time and number of records analyzed to screen
void sort::stats(unsigned int time){
    std::cout << "Algorithm type: " << sort::algoType << std::endl;
    std::cout << "Data set type: " << sort::dataType << std::endl;
    std::cout << "Size (in ints): " << sort::dataSize << std::endl;
    std::cout << "Time taken(in microseconds): " << time << "\n" << std::endl;
}
//sets sort type
void sort::select(algorithm::sorts item) {
    sortType = item;
}
//saves to file
void sort::save(const char * fileName) {
    std::ofstream output(fileName);
    if(!output) {
        std::cerr << fileName << " could not be opened";
        exit(EXIT_FAILURE);
    }
    else {
        for(auto & item: data){
            output << item << std::endl;
        }
    }
    output.close();
}
//this method should be blank
void sort::configure() {

}