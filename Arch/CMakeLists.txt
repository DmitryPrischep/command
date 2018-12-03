cmake_minimum_required(VERSION 3.12)
project(Arch)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -I /usr/local/boost-1.68.0/include -L /usr/local/boost-1.68.0/lib -lboost_system -lboost_filesystem")
set(HEADER_LIB
        FileInfo.h
        RW_Interface.h
        RW_Liner.h)
set(SOURCE_LIB
        FileInfo.cpp
        RW_Interface.cpp
        RW_Liner.cpp)

add_library(FileInfo STATIC ${SOURCE_LIB})
add_library(RW_Interface STATIC ${SOURCE_LIB})
add_library(RW_Liner STATIC ${SOURCE_LIB})
add_library(Union STATIC ${SOURCE_LIB})

add_executable(Arch main.cpp)
#add_executable(main ${SOURCE_EXE})

target_link_libraries(Arch FileInfo RW_Interface RW_Liner Union)