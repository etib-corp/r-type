file(GLOB_RECURSE ASIO_NETWORK_MODULE_SOURCES src/*.cpp ../../src/*.cpp)

include_directories(../../include)
include_directories(include)

add_library(NetworkModule SHARED ${ASIO_NETWORK_MODULE_SOURCES})

target_link_libraries(NetworkModule PRIVATE Boost::asio Boost::system Boost::iostreams)
