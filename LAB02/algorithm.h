//
// Created by Hayden Donofrio on 9/1/18.
//

#ifndef LAB02_ALGORITHM_H
#define LAB02_ALGORITHM_H
#include <list>
#include <string>
/*this class is the pure virtual class that sort implements from
* I made it pure virtual for easy expandability for a possible search in lab2
*/
class algorithm {
public:
    enum searches {DFS = 0, BFS, DIJSKTRA, A};
    //Takes a filename as and can read input data file
    virtual ~algorithm() {};
    virtual void load(const char *, const char *, const char *) = 0;
    //Executes the search algorithm
    virtual void execute(int, int) = 0;
    //Prints solution to screen
    virtual void display() = 0;
    //Prints algorithm name, execution time and number of records analyzed to screen
    virtual void stats(std::list<int> finalPath,  unsigned int time ,int nodesExplored=0, double distance =0, double cost =0 ,std::string type = "" ) = 0;
    //enum or int or id passed as input and loads corresponding algorithm to interface
    virtual void select(int) = 0;
    //Saves solution to file path given as input
    virtual void save(const char *) = 0;
    //Future expandability
    virtual void configure() = 0;
};
#endif //LAB02_ALGORITHM_H
