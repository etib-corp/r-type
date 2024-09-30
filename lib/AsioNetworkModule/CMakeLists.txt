file(GLOB_RECURSE ASIO_NETWORK_MODULE_SOURCES src/*.cpp)

include_directories(../../include)
include_directories(include)

add_subdirectory(dependencies/boost-1.86.0)

include_directories(${boost_asio_SOURCE_DIR}/include)

add_library(AsioNetworkModule SHARED ${ASIO_NETWORK_MODULE_SOURCES})

target_link_libraries(AsioNetworkModule PRIVATE Boost::asio)
