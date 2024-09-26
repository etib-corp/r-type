include(FetchContent)

cmake_minimum_required(VERSION 3.20)
project(r-type)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/)
set(XERCES_USE_ICU OFF)


set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

FetchContent_Declare(
  xerces-c
  GIT_REPOSITORY  https://github.com/apache/xerces-c.git
  GIT_TAG        v3.2.0
)

FetchContent_Declare(
  freetype
  GIT_REPOSITORY https://github.com/freetype/freetype.git
  GIT_TAG        VER-2-13-3
)

FetchContent_MakeAvailable(xerces-c freetype)

add_subdirectory(dependencies/glfw-3.4)

add_subdirectory(lib)

file(GLOB_RECURSE SOURCES src/*.cpp)

include_directories(include)

add_library(r-type STATIC ${SOURCES})

file(GLOB_RECURSE CLIENT_SOURCES client/src/*.cpp)
include_directories(client/include client/include/GUI)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/_deps/freetype-src/include ${CMAKE_CURRENT_BINARY_DIR}/_deps/freetype-src/include/freetype)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/_deps/xerces-c-src/src/xercesc/include ${CMAKE_CURRENT_BINARY_DIR}/_deps/xerces-c-src/src/xercesc/include/xercesc)
include_directories(${OPENGL_INCLUDE_DIRS})
add_executable(r-type_client ${CLIENT_SOURCES})
target_link_libraries(r-type_client r-type)

target_link_libraries(r-type_client glfw)
target_link_libraries(r-type_client ${OPENGL_LIBRARIES})
target_link_libraries(r-type_client freetype xerces-c)

file(GLOB_RECURSE SERVER_SOURCES server/src/*.cpp)
include_directories(server/include)
add_executable(r-type_server ${SERVER_SOURCES})
target_link_libraries(r-type_server r-type)
