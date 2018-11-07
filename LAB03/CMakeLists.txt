cmake_minimum_required(VERSION 3.9)
project(LAB03)

set(CMAKE_CXX_STANDARD 17)

add_executable(LAB03 main.cpp  Decorator.cpp Decorator.h Salesman.cpp Salesman.h  AlgoBuilder.cpp AlgoBuilder.h BaseDecorator.h Reader.cpp Reader.h AlgoFactory.cpp AlgoFactory.h BruteForce.cpp BruteForce.h Dynamic.cpp Dynamic.h Node.h)