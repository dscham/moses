# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.8)

project("Moses" VERSION 0.0.2)

add_executable(Moses_Win64 src/main.cpp)
