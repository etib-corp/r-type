file(GLOB_RECURSE ASIO_NETWORK_MODULE_SOURCES src/*.cpp)

include_directories(../../include/)
include_directories(include)

include(FetchContent)

FetchContent_Declare(
    Boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.86.0
)

FetchContent_MakeAvailable(Boost)

include_directories(asio INTERFACE ${boost_asio_SOURCE_DIR}/include)

add_library(AsioNetworkModule SHARED ${ASIO_NETWORK_MODULE_SOURCES})

target_link_libraries(AsioNetworkModule PRIVATE Boost::asio)
