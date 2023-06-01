cmake_minimum_required(VERSION 3.25)
project(c-algorithm)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(lib)
add_subdirectory(src bin)
add_subdirectory(test)
