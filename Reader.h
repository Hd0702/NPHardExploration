//
// Created by Hayden Donofrio on 10/28/18.
//

#ifndef LAB03_READER_H
#define LAB03_READER_H
#include <vector>

#include "AlgoBuilder.h"
#include "Node.h"
class Reader {
public:
    static Node ** Read(const char * fileName);
    static void Write(char * fileName);
    static int getSize() {
        return size;
    }
private:
    static Node ** CreateMatrix( std::vector<std::vector<Node> > lst);
    static int size;
};


#endif //LAB03_READER_H
