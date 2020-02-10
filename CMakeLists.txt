cmake_minimum_required(VERSION 3.15)

project(georhiau LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES) # for completion

include_directories(georhiau)

add_executable(georhiau georhiau/driver/main.cpp)

add_subdirectory(docs)
