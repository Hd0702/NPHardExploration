//
// Created by Hayden Donofrio on 11/13/18.
//

#include "Genetic.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <queue>
#include <map>
//for timing and comparison, check best solution at 4s, 8s, 16s, etc....
//add end for optimal solution
void Genetic::execute() {
    //starting
    srand(time(NULL));
    auto rng = std::default_random_engine {};
    for(int i =0; i < 20; i++){
        std::vector<int> temp;
        for(int j =2; j < matrixSize+1; j++){
            temp.push_back(j);
        }
        std::shuffle(std::begin(temp), std::end(temp), rng);
        temp.insert(temp.begin(), 1);
        temp.push_back(1);
        population.push_back(temp);
    }
    std::vector<std::vector <int> > temp = population;
    std::vector<int> Mutations = {2,5,12};
    std::vector<int> selections = {0,1,2};
    std::vector<int> probSelects = {0, 1, 2};
    for(auto & mu: Mutations){
        MutationChance = mu;
        for(auto & se: selections) {
            selection = se;
            for(auto & pro : probSelects){
                population = temp;
                bestDistance = INT32_MAX;
                probSelect = 2;
                unsigned int time = run();
                showStats(time);
                times.clear();

            }
        }
    }
}
class CompareDist
{
public:
    bool operator()(std::pair<double,int> n1,std::pair<double,int> n2) {
        return n1.first>n2.first;
    }
};
unsigned int Genetic::run() {
    std::priority_queue<std::pair<double,int>,std::vector<std::pair<double,int>>,CompareDist> distances;
    auto t1 = std::chrono::high_resolution_clock::now();
    int po =0;
    while (bestDistance != matrixSize && po < matrixSize*2000) {
        int i = 0;
        double tot = 0;
        for (auto j = population.begin(); j != population.end(); j++) {
            double d = Decorator::calculateDistance(*j, Matrix);
            if (d < bestDistance) {
                auto t2 = std::chrono::high_resolution_clock::now();
                unsigned int time = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
                bestDistance = d;
                times.push_back(std::make_pair(time, bestDistance));
                bestSolution = *j;
            }
            distances.push(std::make_pair(d, i));
            i++;
            tot += d;
        }
        //now distances holds the order, we have to create probabilities now
        std::vector<std::pair<int, double> > probabilities;
        i = 0;
        double totalProb = 0;
        while (!distances.empty()) {
            std::pair<double, int> current = distances.top();
            distances.pop();
            double between = 1- (current.first / tot)*10;
            totalProb += between;
            probabilities.push_back(std::make_pair(current.second, between));
            i++;
        }
        //CALCULATING PERCENTAGES
        for(auto &p : probabilities){
            p.second /= totalProb;
        }
        if(probSelect == 1){
            for(int p =10; p < 20; p++){
                probabilities[p-10].second += (probabilities[p].second/2);
                probabilities[p].second /= 2;
            }
        }
        if(probSelect == 2){
            int j = 0;
            double percentage = 1.0;
            for(int p= 19; p > 9; p--) {
                probabilities[j].second += probabilities[p].second*percentage;
                probabilities[p].second -= probabilities[p].second*percentage;
                percentage -= .1;
                j++;
            }
        }
        //SELECTING PARENTS
        std::vector<std::vector<int> > newPopulation;
        for (int i = 0; i < 20; i++) {
            double limit = (rand() % 100 + 1) / 100.0;
            double limit2 = (rand() % 100 + 1) / 100.0;
            int p1ndex = -1;
            int p2ndex = -2;
            for (int j = 0; j < probabilities.size(); j++) {
                if (limit - probabilities[j].second <= 0 && p1ndex == -1) {
                    p1ndex = j;
                } else {
                    limit -= probabilities[j].second;
                }
                if (limit2 - probabilities[j].second <= 0 && p2ndex == -2)  {
                    p2ndex = j;
                } else {
                    limit2 -= probabilities[j].second;
                }
                if (p1ndex == p2ndex) {
                    (p1ndex == 0) ? p2ndex = 1 : p1ndex = p2ndex - 1;
                }
                if(p1ndex != -1 && p2ndex != -2) break;
            }
            if(p1ndex == -1) {p1ndex =0; }
            if(p2ndex == -2) {p2ndex = 0;}
            //CREATE CHILD
            std::vector<int> newChild = CreateChild( population[probabilities[p1ndex].first], population[probabilities[p2ndex].first]);
            newPopulation.push_back(newChild);
        }
        population = newPopulation;
        po++;
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
}
void Genetic::setMatrix(Node ** m , int size) {
    Matrix = m;
    matrixSize = size;
}

void Genetic::showStats(unsigned int time) {
    std::string format =  std::string("Genetic\nSelection Type: ") + strs[selection] +
                          "\nCrossover Type: " + strs[probSelect+3] +
                          "\nMutation Percent: " + std::to_string(MutationChance) +'%';
    Decorator::stats((char*)format.c_str() ,time, 0, times.back().second);
}
#include <iostream>
std::vector<int> Genetic::CreateChild( std::vector<int> & p1, std::vector<int> & p2) {
    //if selection = 0 do basic, if selection = 1, do front swapped with random, if selection = 2 do back swapped w/ rand
    std::vector<int> child = p1;
    std::random_device seeder;
    std::mt19937 engine(seeder());
    int limit;
    std::uniform_int_distribution<int> dist(1, matrixSize-1);
    if(selection == 1){
        //SEND TO OX1 IF SELECTION IS 1
        child =  ox1(p1, p2);
    }
    else {
        limit = rand() % matrixSize + 1;
        for (int i = 1; i < limit; i++) {
            int temp;
            if (selection == 2) {
                temp = p1[matrixSize - 2];
                child[matrixSize - 2] = p2[matrixSize - 2];
                auto iter = std::find(std::begin(child), std::end(child), p2[matrixSize - 2]);
                *iter = temp;
                break;
            }
            temp = child[i];
            auto iter = std::find(std::begin(child), std::end(child), p2[i]);
            *iter = temp;
            child[i] = p2[i];
        }
    }
    limit = rand() % 100;
    int limit2 = limit;
    if(MutationChance- limit >= 0) {
        while (limit == limit2) {
            limit = dist(engine);
            std::uniform_int_distribution<int> dist(1, matrixSize - 1);
            limit2 = dist(engine);
        }
        std::swap(child[limit], child[limit2]);
    }
    return child;
}
std::vector<int> Genetic::ox1(std::vector<int> & p1 , std::vector<int> & p2) {
    int limit = rand() % matrixSize+1;
    int limit2 = rand() % matrixSize+1;
    std::vector<int> child = p1;
    if(limit > limit2){
        std::swap(limit, limit2);
    }
    for(int i =1; i < matrixSize; i++){
        if(i == limit) {
            i = limit2+1;
            if(i >= matrixSize) break;
        }
        auto iter = std::find(std::begin(child)+limit, std::begin(child)+limit2+1, p2[i]);
        if(iter == std::begin(child)+limit2+1 && !((unsigned)(i-limit) <= (limit2-limit))) {
            auto iter = std::find(std::begin(child), std::end(child), p2[i]);
            *iter = child[i];
            child[i] = p2[i];
        }
    }
    return child;
}