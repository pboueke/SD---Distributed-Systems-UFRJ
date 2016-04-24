cmake_minimum_required(VERSION 3.5)
project(sd)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES proj1/signals/pt1/program1.cpp)
set(SOURCE_FILES proj1/signals/pt2/program2.cpp)
add_executable(signals1 ${SOURCE_FILES})
add_executable(signals2 ${SOURCE_FILES})