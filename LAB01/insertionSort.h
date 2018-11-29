//
// Created by Hayden Donofrio on 9/1/18.
//

#ifndef LAB01_INSERTIONSORT_H
#define LAB01_INSERTIONSORT_H
//this is my implementation of templated insertion sort
template <typename T>
class insertionSort: public sort {
public:
    insertionSort(std::vector<T> &);
private:
    void sort(std::vector<T> &);
};
//the constructor starts the clock and runs each method and sends to stats
template <typename T>
insertionSort<T>::insertionSort(std::vector<T> & items) {
    auto start = std::chrono::high_resolution_clock::now();
    insertionSort::sort(items);
    auto end = std::chrono::high_resolution_clock::now();
    unsigned int total = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    sort::stats(total);
}
//the actual algorithm to sort items
template <typename T>
void insertionSort<T>::sort(std::vector<T> & items) {
    for(int i =0; i < items.size(); i++) {
        int temp = i;
        while(temp > 0 && items[temp-1]> items[temp]) {
            std::swap(items[temp], items[temp - 1]);
            temp--;
        }
    }
}
#endif //LAB01_INSERTIONSORT_H
