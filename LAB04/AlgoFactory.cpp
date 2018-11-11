//
// Created by Hayden Donofrio on 10/30/18.
//

#include "AlgoFactory.h"
#include "BaseDecorator.h"
#include "Decorator.h"
#include "Salesman.h"
#include "BruteForce.h"
#include "Dynamic.h"
#include "Tabu.h"
BaseDecorator * AlgoFactory::Create(AlgoFactory::algos type){
    BaseDecorator * br;
    switch(type){
        case algos::BRUTEFORCE:
            br = new BruteForce(new Salesman());
            break;
        case algos::DYNAMIC:
            br = new Dynamic(new Salesman());
            break;
        case algos::TABU:
            br = new Tabu(new Salesman());
            break;
        default:
            br = new BruteForce(new Salesman());
    }
    return br;
}