//
// Created by Hayden Donofrio on 9/20/18.
//

#ifndef LAB01_ALGOFACTORY_H
#define LAB01_ALGOFACTORY_H
//this forward decleration shows that we will be inclduing the file in the cpp
class algorithim;
class AlgoFactory {
public:
    enum AlgoClass { SORT = 0, SEARCH, HEURISTIC};
    static algorithim * Create(AlgoClass);
};


#endif //LAB01_ALGOFACTORY_H
