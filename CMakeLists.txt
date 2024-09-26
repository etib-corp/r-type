cmake_minimum_required(VERSION 3.20)
project(r-type)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

include(FetchContent)

FetchContent_Declare(
  freetype
  GIT_REPOSITORY https://github.com/freetype/freetype.git
  GIT_TAG        VER-2-13-3
)

FetchContent_MakeAvailable(freetype)


add_subdirectory(dependencies/glfw-3.4)

add_subdirectory(lib)

file(GLOB_RECURSE SOURCES src/*.cpp)

include_directories(include client/include  server/include)

add_library(r-type STATIC ${SOURCES})

file(GLOB_RECURSE CLIENT_SOURCES client/src/*.cpp)
include_directories(client/include client/include/GUI client/include/Maths dependencies/stb/include)
include_directories(${OPENGL_INCLUDE_DIRS})
add_executable(r-type_client ${CLIENT_SOURCES})
target_link_libraries(r-type_client r-type)
target_link_libraries(r-type_client glfw freetype)
target_link_libraries(r-type_client ${OPENGL_LIBRARIES})

file(GLOB_RECURSE SERVER_SOURCES server/src/*.cpp)
include_directories(server/include)
add_executable(r-type_server ${SERVER_SOURCES})
target_link_libraries(r-type_server r-type)
