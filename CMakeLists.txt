cmake_minimum_required(VERSION 3.20)
project(r-type)

set(CMAKE_CXX_STANDARD 20)
set(BOOST_ENABLE_CMAKE ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

file(GLOB_RECURSE SERVER_SOURCES src/server/*.cpp)
file(GLOB_RECURSE CLIENT_SOURCES src/client/*.cpp)

include_directories(include)

include(FetchContent)

message(STATUS "Fetching Boost")

FetchContent_Declare(
    Boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.86.0
)

FetchContent_MakeAvailable(Boost)

message(STATUS "Boost source dir: ${boost_SOURCE_DIR}")

include_directories(${boost_SOURCE_DIR})

add_executable(r-type_server ${SERVER_SOURCES})
add_executable(r-type_client ${CLIENT_SOURCES})

target_link_libraries(r-type_server PRIVATE Boost::system)

target_link_libraries(r-type_client PRIVATE Boost::system)
