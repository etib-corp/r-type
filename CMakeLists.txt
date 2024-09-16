cmake_minimum_required(VERSION 3.20)
project(r-type)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

file(GLOB_RECURSE SERVER_SOURCES src/server/*.cpp)
file(GLOB_RECURSE CLIENT_SOURCES src/client/*.cpp)

include_directories(include)

add_executable(r-type_server ${SERVER_SOURCES})
add_executable(r-type_client ${CLIENT_SOURCES})

include(FetchContent)

FetchContent_Declare(
    Boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.86.0
)

FetchContent_MakeAvailable(Boost)

target_link_libraries(r-type_server Boost::boost)
target_link_libraries(r-type_client Boost::boost)
