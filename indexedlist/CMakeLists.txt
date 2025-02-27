cmake_minimum_required(VERSION 3.27)
project(indexedlist)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(indexedlist
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        IndexedList.cpp
        IndexedList.h
        ListIterator.cpp
        ListIterator.h
        ShortTest.cpp
        ShortTest.h)
