cmake_minimum_required(VERSION 3.6)
project(linkedlist)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

set(SOURCE_FILES main.c linkedlist.h)
add_executable(linkedlist ${SOURCE_FILES})