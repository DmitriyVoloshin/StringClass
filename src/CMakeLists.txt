cmake_minimum_required(VERSION 3.16)

project(StringClass)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g3 -O0")
set(SRC_LIST main.cpp mString.cpp)

add_executable(StringClassTest ${SRC_LIST})
add_library(StringClass STATIC ${SRC_LIST})

