cmake_minimum_required(VERSION 3.10)

project(pathfinder)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(pathfinder src/pathfinder.cpp src/vec.cpp src/path.cpp src/util.cpp)
