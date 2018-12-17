cmake_minimum_required(VERSION 3.12)
project(compressor)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(compressor
        my_test/Test_Selector.cpp
        Coder.hpp
        Huffman.cpp
        Huffman.hpp
        LZW.cpp
        LZW.hpp
        Selector.cpp
        Selector.hpp)
