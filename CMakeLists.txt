cmake_minimum_required(VERSION 3.3)
project(hw513)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES hw513_main.cpp Polynomial.hpp)
add_executable(hw513 ${SOURCE_FILES})