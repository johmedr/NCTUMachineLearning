cmake_minimum_required (VERSION 2.8.11)
project (NEOS)

set(EXECUTABLE_OUTPUT_PATH bin)

add_definitions("-std=c++11 -Wall -Wextra -ggdb -O3")
include_directories(include)

enable_testing() 
add_subdirectory(${CMAKE_SOURCE_DIR}/test) 

add_executable(linreg src/main.cpp)