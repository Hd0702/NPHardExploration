//
// Created by Hayden Donofrio on 9/23/18.
//

#include "Node.h"
bool operator < (const Node & lhs, const Node & rhs){
    return (lhs.distance+ lhs.weight) > (rhs.distance + rhs.weight);
}
