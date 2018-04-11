cmake_minimum_required(VERSION 3.8)
project(Os1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES  osm.h osm.cpp)
add_executable(Os1 ${SOURCE_FILES})