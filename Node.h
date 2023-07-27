//
// Created by Hayden Donofrio on 11/1/18.
//

#ifndef LAB03_NODE_H
#define LAB03_NODE_H
class Node{
    friend bool operator <(Node & l, Node& r) {
        return l.id < r.id;
    }
public:
    double x = 0;
    double y = 0;
    double z = 0;
    double distance = 0;
    int id;

};
#endif //LAB03_NODE_H
