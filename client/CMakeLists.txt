cmake_minimum_required(VERSION 3.28)

project(r-type_client)

include(FetchContent)

message(STATUS "Fetching GLFW")
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
)

FetchContent_GetProperties(glfw)

if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)

    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)

set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add compile options for debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb")
endif()

include_directories(include include/GUI ${OPENGL_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS})

file(GLOB SOURCES src/*.cpp src/GUI/*.cpp)

add_executable(r-type_client ${SOURCES})

target_link_libraries(r-type_client GL glfw ${OPENGL_LIBRARIES} ${FREETYPE_LIBRARIES})
