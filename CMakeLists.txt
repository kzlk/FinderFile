cmake_minimum_required(VERSION 3.25)
project(FileFinder)

set(CMAKE_CXX_STANDARD 20)

add_executable(FileFinder main.cpp  FInder.cpp Finder.h ThreadPool.h NewThreadPool.h)
