//
// Created by Hayden Donofrio on 9/23/18.
//

#ifndef LAB02_NODE_H
#define LAB02_NODE_H


class Node {
public:
    //TODO: Remove XYZ from node and calculate locally
    Node() = default;
    int data = 0;
    double distance= 0.0;
    double x= 0; //only used for calculating distances from other nodes
    double y = 0;
    double z = 0;
    bool visited = false;
    double weight = 0;
    Node * next = nullptr;
    Node * prev = nullptr;
    //we flip this operator so smaller shorter paths are at front of priority queue
    friend bool operator <(const Node & lhs, const Node & rhs);
};


#endif //LAB02_NODE_H
