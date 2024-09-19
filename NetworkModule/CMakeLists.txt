cmake_minimum_required(VERSION 3.20)
project(NetworkModule)

set(CMAKE_CXX_STANDARD 20)
set(BOOST_ENABLE_CMAKE ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE MODULES_SOURCES src/*.cpp)

include_directories(include)
include_directories(../include)
include(FetchContent)

message(STATUS "Fetching Boost")

FetchContent_Declare(
    Boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.86.0
)

FetchContent_MakeAvailable(Boost)

message(STATUS "Boost source dir: ${boost_SOURCE_DIR}")

include_directories(asio INTERFACE ${boost_asio_SOURCE_DIR}/include)

add_library(NetworkModule SHARED ${MODULES_SOURCES})

target_link_libraries(NetworkModule PRIVATE Boost::system Boost::asio)
