cmake_minimum_required(VERSION 3.12)
project(integrations_test)

set(CMAKE_CXX_STANDARD 14)

set(EXECUTE_APP Test_Compress_And_Decompress.cpp)

if (${WIN32})
  message(STATUS "Building on Windows")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -I C:/boost/include -L C:/boost/libs -lboost_system -lboost_filesystem")
endif()
if (${APPLE})
	message(STATUS "Building on MacOS")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -I /usr/local/boost-1.68.0/include -L /usr/local/boost-1.68.0/lib -lboost_system -lboost_filesystem")
endif ()

set(HEADER_LIB
        FileInfo.h
        RW_Interface.h
        RW_Liner.h
        ../Coder.hpp
        ../LZW.hpp)

set(SOURCE_LIB
        FileInfo.cpp
        RW_Interface.cpp
        RW_Liner.cpp
        ../LZW.cpp)

add_library(FileInfo STATIC ${SOURCE_LIB})
add_library(RW_Interface STATIC ${SOURCE_LIB})
add_library(RW_Liner STATIC ${SOURCE_LIB})
add_library(LZW STATIC ${SOURCE_LIB})


add_executable(integrations_test ${EXECUTE_APP})

target_link_libraries(integrations_test FileInfo RW_Interface RW_Liner LZW)