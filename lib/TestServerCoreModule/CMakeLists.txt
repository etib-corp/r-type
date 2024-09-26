file(GLOB_RECURSE TEST_SERVER_CORE_MODULE_SOURCES src/*.cpp)

include_directories(../../include/)
include_directories(include)

add_library(TestServerCoreModule SHARED ${TEST_SERVER_CORE_MODULE_SOURCES})
