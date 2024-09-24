cmake_minimum_required(VERSION 3.20)
project(r-type)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/)

add_subdirectory(dependencies/glfw-3.4)

find_package(OpenGL REQUIRED)

add_subdirectory(lib)

file(GLOB_RECURSE SOURCES src/*.cpp)

include_directories(include)

add_compile_options(-ggdb)

add_library(r-type STATIC ${SOURCES})

file(GLOB_RECURSE CLIENT_SOURCES client/src/*.cpp)
include_directories(client/include client/include/GUI)
add_executable(r-type_client ${CLIENT_SOURCES})
target_link_libraries(r-type_client r-type glfw ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} z)

find_package(ZLIB REQUIRED)

if (ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIRS})
    message(STATUS "Zlib found: ${ZLIB_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Please install Zlib !")
endif()

file(GLOB_RECURSE SERVER_SOURCES server/src/*.cpp)
include_directories(server/include)
add_executable(r-type_server ${SERVER_SOURCES})
target_link_libraries(r-type_server r-type z)
