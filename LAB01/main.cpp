#include <iostream>
#include <string>
#include "generateData.h"
#include "sort.h"
#include "search.h"
#include "algofactory.h"

int main() {
    /* run the below lines to generate input files in local directory
     * recommend running the following two lines the first time to populate possible build directory
     */

      generateData File;
      File.start();

    const int sizes[4] = {10, 1000, 10000, 100000};
    const char * inputTypes[4] = {"Random", "Reverse", "ThirtyPercent", "TwentyPercent"};
    const char * sortTypes[3] = {"Bubble", "Merge", "Insertion"};
    algorithm * algos = new sort();

    //loop through all algo types and their corresponding sizes
    algos->load("graph.txt", "Nothing");
    for(int q = 0; q <1; q++) {
        algos->select(q);
        for(int i=0; i < 4; i++) {
            for(int j =0; j<4; j++) {
                //path string is the formatted strings for proper file names
                std::string path = inputTypes[i] + std::to_string(sizes[j]) + ".txt";
                //algos->load(path.c_str(), inputTypes[i]);
                algos->execute();
                path = sortTypes[q]  + std::to_string(sizes[j]) +  inputTypes[i]  + ".txt";
                algos->save(path.c_str());
            }
        }
    }
    //New code
    sort * factoryAlgo = (sort*)AlgoFactory::Create(AlgoFactory::SEARCH);

    factoryAlgo->setExecutionType(sort::Configuration::ITERATIVE);
    factoryAlgo->setStorageType(sort::Configuration::LIST);
    factoryAlgo->select(sort::sorts::Bubble);
    //protoype
    //we can move clone to the factory to make it less code
    sort * proto = (sort*)(factoryAlgo->Clone());
    return 0;
}