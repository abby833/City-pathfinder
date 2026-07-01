cmake_minimum_required(VERSION 3.10)

project(CityPathFinder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

add_executable(navigator 
    src/main.cpp 
    src/graph.cpp 
    src/trie.cpp
)

add_executable(run_tests
    tests/test_main.cpp
    tests/test_engine.cpp
    src/graph.cpp
    src/trie.cpp
)