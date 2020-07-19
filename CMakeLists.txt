cmake_minimum_required(VERSION 3.10)

project(pathfinder)

# C++ 17
set (CMAKE_CXX_STANDARD 17)

# Choose output directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src/include)

# Add a format target
add_custom_target(format COMMAND clang-format -style=file -i src/*.cpp include/*.hpp)

add_executable(pathfinder src/pathfinder.cpp src/vec.cpp src/path.cpp src/util.cpp src/simulate.cpp src/circle.cpp)
