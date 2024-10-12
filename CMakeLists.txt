include(FetchContent)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

cmake_minimum_required(VERSION 3.20)
project(r-type)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/)
set(XERCES_USE_ICU OFF)

set(OPENGL_SILENT TRUE)
find_package(OpenGL REQUIRED)

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1
FetchContent_MakeAvailable(fmt)

add_subdirectory(dependencies/glfw-3.4)
add_subdirectory(dependencies/freetype-VER-2-13-3)
add_subdirectory(dependencies/glm)
add_subdirectory(dependencies/assimp-5.4.3)
add_subdirectory(dependencies/boost-1.86.0)

file(GLOB_RECURSE SOURCES src/*.cpp)
include_directories(include)
add_library(r-type STATIC ${SOURCES})
target_link_libraries(r-type Boost::iostreams fmt::fmt)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(dependencies/glm/)
include_directories(dependencies/assimp-5.4.3/include)
include_directories(${BOOST_INCLUDE_DIRS})

file(GLOB_RECURSE CLIENT_SOURCES client/src/*.cpp)
include_directories(client/include client/include/GUI client/include/Maths dependencies/stb/include dependencies/rapidobj/include dependencies/json-0.0.1/include)


include_directories(${OPENGL_INCLUDE_DIRS})

add_executable(r-type_client ${CLIENT_SOURCES})

target_link_libraries(r-type_client r-type)
target_link_libraries(r-type_client glfw)
target_link_libraries(r-type_client ${OPENGL_LIBRARIES})
target_link_libraries(r-type_client ${GLUT_LIBRARIES})
target_link_libraries(r-type_client freetype)
target_link_libraries(r-type_client glm)
target_link_libraries(r-type_client assimp)
target_link_libraries(r-type_client fmt::fmt)

file(GLOB_RECURSE SERVER_SOURCES server/src/*.cpp)
include_directories(server/include)
add_executable(r-type_server ${SERVER_SOURCES})

target_link_libraries(r-type_server r-type)
target_link_libraries(r-type_server fmt::fmt)


add_subdirectory(lib)
