cmake_minimum_required(VERSION 3.28)

project(r-type)

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

set(CMAKE_CXX_STANDARD 20)

include_directories(include build/_deps/glfw-src/include)

file(GLOB SOURCES src/*.cpp)

add_executable(r-type ${SOURCES})

target_link_libraries(r-type glfw ${OPENGL_LIBRARIES})

