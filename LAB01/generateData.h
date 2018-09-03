//
// Created by Hayden Donofrio on 8/31/18.
//

#ifndef LAB01_GENERATEDATA_H
#define LAB01_GENERATEDATA_H

/* this class is responsible for the
 * creation of all input files with each data size
*/
class generateData {
public:
    generateData() = default;
    void start();
private:
    void random(int);
    void reverse(int);
    void twentyPercent(int);
    void thirtyPercent(int);
    int sizes[4] = {10, 1000, 10000, 100000};
};


#endif //LAB01_GENERATEDATA_H
