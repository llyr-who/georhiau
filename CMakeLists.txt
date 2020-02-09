cmake_minimum_required(3.10)

project(GeoRhiau LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES) # for completion

add_subdirectory(georhiau)
add_subdirectory(docs)
