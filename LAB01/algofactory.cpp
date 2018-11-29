//
// Created by Hayden Donofrio on 9/20/18.
//

#include "algofactory.h"
#include "sort.h"
#include "algorithm.h"

algorithm * AlgoFactory::Create(AlgoClass type) {
    algorithm * pointAlgo;
    switch(type){
        case AlgoClass ::SORT:
            pointAlgo = new sort::sort();
            break;
        case AlgoClass ::SEARCH:
            //pointAlgo = new Search:
            break;
        case AlgoClass ::HEURISTIC:
            //pointAlgo = new Heurisitc
            break;
        default:
            pointAlgo = nullptr;
    }
}