include(FetchContent)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

cmake_minimum_required(VERSION 3.20)
project(r-type)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/)


if (UNIX OR APPLE)
    add_compile_options(-g3 -ggdb -O0)
endif()

add_subdirectory(dependencies/lion-engine)

file(GLOB_RECURSE CLIENT_SOURCES client/src/*.cpp)
message("${LION_ENGINE_INCLUDE_DIR}")
include_directories(client/include client/include/game dependencies/lion-engine/include include)


if (UNIX OR APPLE)
    add_executable(r-type_client ${CLIENT_SOURCES})

    target_link_libraries(r-type_client lion-engine)
endif()

file(GLOB_RECURSE SERVER_SOURCES server/src/*.cpp)
include_directories(server/include)
add_executable(r-type_server ${SERVER_SOURCES})

target_link_libraries(r-type_server lion-engine)
