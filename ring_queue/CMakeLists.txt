cmake_minimum_required(VERSION 3.8)
project(ring_queue)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c ring_queue.c ring_queue.h)
add_executable(ring_queue ${SOURCE_FILES})