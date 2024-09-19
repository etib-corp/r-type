cmake_minimum_required(VERSION 3.20)
project(r-type)

set(CMAKE_CXX_STANDARD 20)
set(BOOST_ENABLE_CMAKE ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

file(GLOB_RECURSE SHARED_SOURCES src/*.cpp)
file(GLOB_RECURSE SERVER_SOURCES server/src/*.cpp)

include_directories(include)
include_directories(NetworkModule/include)
include_directories(message/include)
include_directories(server/include)

add_subdirectory(NetworkModule)
add_subdirectory(message)

add_library(r-type SHARED ${SHARED_SOURCES})
target_include_directories(r-type PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(r-type_server ${SERVER_SOURCES})
target_link_libraries(r-type_server PRIVATE r-type)
target_link_libraries(r-type_server PRIVATE message)

# add_subdirectory(graphical)
