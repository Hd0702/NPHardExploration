cmake_minimum_required(VERSION 3.9)
project(LAB02)

set(CMAKE_CXX_STANDARD 17)

add_executable(LAB02 main.cpp algorithm.h search.cpp search.h dfs.cpp dfs.h bfs.cpp bfs.h Dijkstra.cpp Dijkstra.h AStar.cpp AStar.h Node.cpp Node.h)