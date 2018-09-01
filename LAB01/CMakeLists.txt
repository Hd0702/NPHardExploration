cmake_minimum_required(VERSION 3.9)
project(LAB01)

set(CMAKE_CXX_STANDARD 17)

add_executable(LAB01 main.cpp main.cpp generateData.cpp generateData.h algorithm.h sort.cpp sort.h mergeSort.h bubbleSort.h insertionSort.h)