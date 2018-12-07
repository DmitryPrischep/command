cmake_minimum_required(VERSION 3.12)
project(command)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -I /usr/local/boost-1.68.0/include -L /usr/local/boost-1.68.0/lib -lboost_system -lboost_filesystem")

set(HEADER_LIB
        FileInfo.h
        Write_Liner.h
        Read_Arch.h
        Test_Interface.h
        Recovery_Arch.h
        )
set(SOURCE_LIB
        FileInfo.cpp
        Write_Liner.cpp
        Read_Arch.cpp
        Test_Interface.cpp
        Recovery_Arch.cpp
        )

add_library(FileInfo STATIC ${SOURCE_LIB} )
add_library(Write_Liner STATIC ${SOURCE_LIB})
add_library(Read_Arch STATIC ${SOURCE_LIB})
add_library(Test_Interface STATIC ${SOURCE_LIB})
add_library(Recovery_Arch STATIC ${SOURCE_LIB})

add_executable(command main.cpp
        FileInfo Write_Liner Read_Arch Test_Interface
        Recovery_Arch)