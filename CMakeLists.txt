cmake_minimum_required(VERSION 3.12)
project(CompressionEngine)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(CompressionEngine
    src/compress.cpp
    src/huffman.cpp
    src/lwz.cpp
    src/quadtree.cpp
    src/main.cpp)
