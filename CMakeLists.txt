cmake_minimum_required(VERSION 3.12)
project(Arch)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -I /usr/local/boost-1.68.0/include -L /usr/local/boost-1.68.0/lib -lboost_system -lboost_filesystem")
set(PATH_TO_GOOGLETEST "/Users/howle/googletest-master")
set(HEADER_LIB
        FileInfo.h
        RW_Interface.h
        RW_Liner.h
        Test_RW_Interface.cpp)
set(SOURCE_LIB
        FileInfo.cpp
        RW_Interface.cpp
        RW_Liner.cpp
        Test_RW_Interface.cpp)

add_library(FileInfo STATIC ${SOURCE_LIB})
add_library(RW_Interface STATIC ${SOURCE_LIB})
add_library(RW_Liner STATIC ${SOURCE_LIB})
add_library(Test_RW_Interface STATIC ${SOURCE_LIB})

#Add the google test subdirectory
#include_directories(${PATH_TO_GOOGLETEST})
#include googletest/include dir
#include_directories(${PATH_TO_GOOGLETEST}/googletest/include)
#include the googlemock/include dir
#include_directories(${PATH_TO_GOOGLETEST}/googlemock/include)
add_executable(Arch main.cpp)

#Define your executable
#add_executable(EXECUTABLE_NAME ${SOURCE_FILES})
#Link with GoogleTest
#target_link_libraries(Arch gtest gtest_main)
#Link with GoogleMock
#target_link_libraries(Arch gmock gmock_main)

target_link_libraries(Arch FileInfo RW_Interface RW_Liner Test_RW_Interface)