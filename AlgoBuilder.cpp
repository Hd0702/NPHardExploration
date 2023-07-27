//
// Created by Hayden Donofrio on 10/28/18.
//

#include "AlgoBuilder.h"
void AlgoBuilder::setAlgo( AlgoFactory::algos alg) {
    switch(alg){
        case AlgoFactory::BRUTEFORCE:
            algo = (BruteForce *)AlgoFactory::Create(alg);
            break;
        case AlgoFactory::DYNAMIC:
            algo = (Dynamic*)AlgoFactory::Create(alg);
            break;
        default:
            algo = (BruteForce*)AlgoFactory::Create(alg);
    }
}
Node ** AlgoBuilder::getMatrix(){
    return matrix;
};
void AlgoBuilder::setMatrix(Node** & mat) {
    matrix = mat;
}
BaseDecorator * AlgoBuilder::getAlgo(){
    return algo;
}

void AlgoBuilder::setSize(int a) {
    size =a;
}
void AlgoBuilder::start() {
    algo->setMatrix(matrix, size);
    algo->execute();
}