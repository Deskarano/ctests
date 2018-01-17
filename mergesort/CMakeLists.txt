cmake_minimum_required(VERSION 3.6)
project(mergesort)

set(CMAKE_C_FLAGS -lpthread)

set(SOURCE_FILES main.c)
add_executable(mergesort ${SOURCE_FILES})