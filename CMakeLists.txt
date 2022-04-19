cmake_minimum_required(VERSION 3.21)
project(spanning_trees)

set(CMAKE_CXX_STANDARD 14)

add_executable(spanning_trees main.cpp unionFind.h Kruskal.h Graph.cpp Graph.h)
