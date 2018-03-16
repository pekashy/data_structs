cmake_minimum_required(VERSION 3.8)
project(data_structs)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        test.c
        structure.c
        structure.h
        )

add_executable(data_structs test.c structure.c)