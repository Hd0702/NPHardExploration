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

void generateData::reverse(int size) {
    std::ofstream output;
    output.open("Reverse" + std::to_string(size) + ".txt");
    for(int i = size-1; i >= 0; i--) {
        output << i << "\n";
    }
    output.close();
}

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
    for(int i =0; i < size * .8; i++) {
        std::uniform_int_distribution<std::mt19937::result_type> rand(1, 10000);
        auto iter = uniqueVals.find(rand(rng));
        if(iter != uniqueVals.end()) {
            int temp = iter->second;
            iter->second = ++temp;
        }
        else  {
            uniqueVals.emplace(rand(rng), 1);
            i--;
        }
    }
    std::vector<int> shuffle;
    for(auto const& item : uniqueVals){
        if(item.second > 1) {
            for(int i = item.second; i > 0; i--)
                shuffle.push_back(item.first);
        }
    }
    auto engine = std::default_random_engine{};
    std::shuffle(shuffle.begin(), shuffle.end(), engine );
    for(auto & k : shuffle) {
        output << k << "\n";
    }
    output.close();
}