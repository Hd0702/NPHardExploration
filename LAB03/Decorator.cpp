//
// Created by Hayden Donofrio on 10/25/18.
//

#include "Decorator.h"
Decorator::Decorator(BaseDecorator * b2):br(b2) {}
//Delegation class
void Decorator::execute() {
    br->execute();
}
void Decorator::setMatrix(Node ** a, int size) {
    br->setMatrix(a, size);
}
void Decorator::stats(char *type, unsigned int time, int nodes, double distance) {
    br->stats(type, time, nodes, distance);
}