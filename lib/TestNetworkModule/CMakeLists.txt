file(GLOB_RECURSE TEST_NETWORK_MODULE_SOURCES src/*.cpp)

if (WIN32)
    add_compile_options(-DLIBRARY_EXPORTS)
endif(WIN32)

include_directories(../../include/)
include_directories(include)

add_library(TestNetworkModule SHARED ${TEST_NETWORK_MODULE_SOURCES})
