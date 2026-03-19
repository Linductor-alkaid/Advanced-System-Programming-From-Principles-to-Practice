cmake_minimum_required(VERSION 3.16)
project(AdvancedSystemProgrammingExamples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

find_package(Threads REQUIRED)

add_subdirectory(ch01)
add_subdirectory(ch02)
add_subdirectory(ch03)
