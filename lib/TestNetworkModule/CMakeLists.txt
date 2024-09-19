file(GLOB_RECURSE TEST_NETWORK_MODULE_SOURCES src/*.cpp)

include_directories(../../include/)
include_directories(include)

add_library(TestnetworkModule SHARED ${TEST_NETWORK_MODULE_SOURCES})
