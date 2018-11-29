#include <iostream>
#include "AlgoBuilder.h"
#include "Reader.h"
#include <string>
#include <ctime>
#include "AlgoFactory.h"
int main() {
    AlgoBuilder j;
    std::string op = "nodes.txt";
    auto mat = Reader::Read(op.c_str());
    int a = Reader::getSize();
    j.setMatrix(mat);
    for(int i =2; i < 4; i ++) {
        j.setAlgo(AlgoFactory::algos(i));
        j.setSize(a);
        j.start();
    }
    return 0;
}