file(GLOB_RECURSE TEST_CORE_MODULE_SOURCES src/*.cpp)

include_directories(../../include/)
include_directories(include)

add_library(TestCoreModule SHARED ${TEST_CORE_MODULE_SOURCES})
