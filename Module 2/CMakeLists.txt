cmake_minimum_required(VERSION 2.6)
project(numb)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES numb.cpp)
add_executable(numb ${SOURCE_FILES})
