cmake_minimum_required(VERSION 3.8)
project(untitled)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -pthread")


set(SOURCE_FILES main.c)
add_executable(untitled ${SOURCE_FILES})