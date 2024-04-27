cmake_minimum_required(VERSION 3.10)
project(dost)

# Compiler flags
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_subdirectory(lib)
add_subdirectory(tui)
# add_subdirectory(gui)
