cmake_minimum_required(VERSION 3.28)
project(r-type)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

file(GLOB SOURCES src/*.cpp)

add_compile_options(-g3 -ggdb)

add_executable(r-type ${SOURCES})

target_link_libraries(r-type GL glfw)