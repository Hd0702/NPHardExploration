//
// Created by Hayden Donofrio on 8/31/18.
//

#include "generateData.h"
#include <vector>
#include <fstream>
#include <random>
#include <map>

void generateData::start() {
    for(int & i : sizes) {
        random(i);
        reverse(i);
        thirtyPercent(i);
        twentyPercent(i);
    }
}

//we're just printing them in order until the size is reached
void generateData::random(int size){
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::ofstream output;
    output.open("Random" + std::to_string(size) + ".txt");
    for(int i = 0; i < size; i++){
        std::uniform_int_distribution<std::mt19937::result_type> rand(1, INT32_MAX);
        output << rand(rng) <<"\n";
    }
    output.close();
}
//prints item in a file in reverse order
void generateData::reverse(int size) {
    std::ofstream output;
    output.open("Reverse" + std::to_string(size) + ".txt");
    for(int i = size; i > 0 ; i--) {
        output << i << "\n";
    }
    output.close();
}
//thirty percent of the items are randomly generated
void generateData::thirtyPercent(int size) {
    std::vector<int> data;
    std::ofstream output;
    std::mt19937 rng;
    rng.seed(std::random_device()());
    output.open("ThirtyPercent" + std::to_string(size) + ".txt");
    for(int i = 0; i < size; i ++) {
        int insert = i;
        int mod = i%10;
        if(mod == 3 || mod == 6 || mod == 9) {
            std::uniform_int_distribution<std::mt19937::result_type> rand(1, 100000);
            insert = (rand(rng));
        }
        data.push_back(insert);
    }
    for(auto & key: data)
        output << key << "\n";
    output.close();
}
/* in this method i used two sets
 * uniqeVals- stores 20% of the unique values and prints them
 * repeateVals - checks uniquevals and adds new values
 */
void generateData::twentyPercent(int size) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::ofstream output;
    output.open("TwentyPercent" + std::to_string(size) + ".txt");
    std::map<int,int> uniqueVals;
    for(int i = 0; i < size * .2; i++) {
        std::uniform_int_distribution<std::mt19937::result_type> rand(1, INT32_MAX);
        //first 20 % unique values
        int put = rand(rng);
        uniqueVals.emplace(rand(rng), 1);
        output << rand(rng) << "\n";
    }
    //now for 80% that repeat
    std::map<int,int>repeatVals;
    int total = 0;
    int stopPoint = size *.8;
    while(total < stopPoint) {
        std::uniform_int_distribution<std::mt19937::result_type> rand(1, 10000);
        auto iter = repeatVals.find(rand(rng));
        if(uniqueVals.find(rand(rng)) == uniqueVals.end()) {
            if (iter != repeatVals.end()) {
                ++(iter->second);
                for (int i = 0; i < iter->second; i++) {
                    if (total == stopPoint) break;
                    else total++;
                }
            } else {
                repeatVals.emplace(rand(rng), 1);
            }
        }
    }
    //shuffle all items in a set since they are in order because a set is a tree
    std::vector<int> shuffle;
    //add all items in the set that repeat
    for(auto const& item : repeatVals){
        if(item.second > 1) {
            for(int i = item.second; i > 0; i--)
                shuffle.push_back(item.first);
        }
    }
    auto engine = std::default_random_engine{};
    std::shuffle(shuffle.begin(), shuffle.end(), engine );
    auto k = shuffle.begin();
    for(int i =0; i < total; i++) {
        output << *(k++) << "\n";
    }
    output.close();
}