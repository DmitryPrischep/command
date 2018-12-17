cmake_minimum_required(VERSION 3.12)
project(btest)

set(CMAKE_CXX_STANDARD 14)

include_directories(C:/boost-prefix/include/boost-1_68)

add_executable(btest
		C:/boost-prefix/lib/libboost_system-mgw81-mt-x64-1_68.a 
		C:/boost-prefix/lib/libboost_filesystem-mgw81-mt-x64-1_68.a
        main.cpp)
