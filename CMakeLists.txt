cmake_minimum_required(VERSION 3.17)
project(MultiThreading)

set(CMAKE_CXX_STANDARD 20)

add_executable(MultiThreading main.cpp)

target_link_libraries(MultiThreading pthread)