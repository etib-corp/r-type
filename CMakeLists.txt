include(FetchContent)

cmake_minimum_required(VERSION 3.20)
project(r-type)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/)
set(XERCES_USE_ICU OFF)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

add_subdirectory(dependencies/glfw-3.4)
add_subdirectory(dependencies/zlib-1.3.1)
add_subdirectory(dependencies/xerces-c-3.2.5)
add_subdirectory(dependencies/freetype-VER-2-13-3)
add_subdirectory(dependencies/glm)


file(GLOB_RECURSE SOURCES src/*.cpp)
include_directories(include)
add_library(r-type STATIC ${SOURCES})

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(dependencies/glm/)

file(GLOB_RECURSE CLIENT_SOURCES client/src/*.cpp)
include_directories(client/include client/include/GUI)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/_deps/freetype-src/include ${CMAKE_CURRENT_BINARY_DIR}/_deps/freetype-src/include/freetype)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/_deps/xerces-c-src/src/xercesc/include ${CMAKE_CURRENT_BINARY_DIR}/_deps/xerces-c-src/src/xercesc/include/xercesc)
include_directories(${OPENGL_INCLUDE_DIRS})

add_executable(r-type_client ${CLIENT_SOURCES})

target_link_libraries(r-type_client r-type)
target_link_libraries(r-type_client glfw)
target_link_libraries(r-type_client ${OPENGL_LIBRARIES})
target_link_libraries(r-type_client ${GLUT_LIBRARIES})
target_link_libraries(r-type_client zlib)
target_link_libraries(r-type_client freetype)
target_link_libraries(r-type_client xerces-c)
target_link_libraries(r-type_client glm)

file(GLOB_RECURSE SERVER_SOURCES server/src/*.cpp)
include_directories(server/include)
add_executable(r-type_server ${SERVER_SOURCES})

target_link_libraries(r-type_server r-type)
target_link_libraries(r-type_server zlib)

add_subdirectory(lib)
