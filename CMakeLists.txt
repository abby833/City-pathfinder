cmake_minimum_required(VERSION 3.10)

project(CityPathFinder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(navigator 
    src/main.cpp 
    src/graph.cpp 
    src/trie.cpp
)