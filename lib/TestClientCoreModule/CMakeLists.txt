file(GLOB_RECURSE TEST_CLIENT_CORE_MODULE_SOURCES src/*.cpp)

include_directories(../../include/)
include_directories(include)

add_library(TestClientCoreModule SHARED ${TEST_CLIENT_CORE_MODULE_SOURCES})
