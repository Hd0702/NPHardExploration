//
// Created by Hayden Donofrio on 9/1/18.
//

#ifndef LAB01_BUBBLESORT_H
#define LAB01_BUBBLESORT_H
#include "sort.h"
#include <vector>

template<typename T>
class bubbleSort : public sort{
public:
    bubbleSort(std::vector<T> &);
    void begin(std::vector<T> &);

};

template <typename T>
bubbleSort<T>::bubbleSort(std::vector<T> & input) {
    auto start = std::chrono::high_resolution_clock::now();
    begin(input);
    auto end = std::chrono::high_resolution_clock::now();
    unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    sort::stats(total);
}

template <typename T>
void bubbleSort<T>::begin(std::vector<T> & data) {
    int size = data.size()-1;
    bool swapped = true;
    while(swapped) {
        swapped = false;
        for(int i =0; i < size; i ++) {
            if(data[i] > data[i+1]) {
                std::swap(data[i], data[i+1]);
                swapped = true;
            }
        }
    }
}
#endif //LAB01_BUBBLESORT_H
