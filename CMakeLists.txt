cmake_minimum_required(VERSION 3.25)
project(ant)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS -O3)

include_directories(ant
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(ant 
    src/main.cpp
    src/graph_handler.cpp
    src/acolony.cpp
    src/optimization/base_search.cpp
    src/optimization/aco_tuner.cpp
    src/optimization/exhaustive_search.cpp
    src/optimization/exhaustive_strategy.cpp
)

target_link_libraries(ant)