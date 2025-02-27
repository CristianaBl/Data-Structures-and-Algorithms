cmake_minimum_required(VERSION 3.27)
project(priorityqueue)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(priorityqueue
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        PriorityQueue.cpp
        PriorityQueue.h
        ShortTest.cpp
        ShortTest.h)
