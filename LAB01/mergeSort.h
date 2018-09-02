//
// Created by Hayden Donofrio on 9/1/18.
//

#ifndef LAB01_MERGESORT_H
#define LAB01_MERGESORT_H

#include "sort.h"
#include <vector>
#include <string>

template <typename T>
class mergeSort : public sort{
public:
    mergeSort(std::vector<T> &);

private:
    void split(std::vector<T> & , int, int);
    void merge(std::vector<T> &, int, int, int);
};

template <typename T>
mergeSort<T>::mergeSort(std::vector<T> & input)  {
    auto start = std::chrono::high_resolution_clock::now();
    split(input, 0, input.size()-1);
    auto end = std::chrono::high_resolution_clock::now();
    unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    sort::stats(total);
}

template <typename T>
void mergeSort<T>::split(std::vector<T> & items, int low, int high) {
    if (low < high) {
        int pivot = (low + high)/2;
        split(items, low, pivot);
        split(items, pivot+1, high);
        merge(items, low, high, pivot);
    }
}

template <typename T>
void mergeSort<T>::merge(std::vector<T> & items, int low, int high, int pivot) {
    int i = low;
    int j = pivot+1;
    std::vector<T> temp;
    while(i <= pivot && j <= high){
        if(items[i] < items[j]) {
            temp.push_back(items[i++]);
        }
        else{
            temp.push_back(items[j++]);
        }
    }
    while(i <= pivot) {
        temp.push_back(items[i++]);
    }
    while(j <= high) {
        temp.push_back(items[j++]);
    }
    for(int a =low; a <= high; a++) {
        items[a] = temp[a-low];
    }
}
#endif //LAB01_MERGESORT_H
