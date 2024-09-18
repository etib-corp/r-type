cmake_minimum_required(VERSION 3.20)
project(r-type)

set(CMAKE_CXX_STANDARD 20)
set(BOOST_ENABLE_CMAKE ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(message)

file(GLOB_RECURSE SERVER_SOURCES server/src/*.cpp)
# file(GLOB_RECURSE CLIENT_SOURCES src/client/*.cpp)

# add_subdirectory(server/NetworkModule)

include_directories(server/include)

# add_executable(r-type_server ${SERVER_SOURCES})
# add_executable(r-type_client ${CLIENT_SOURCES})

# target_link_libraries(r-type_client PRIVATE Boost::system Boost::asio)
