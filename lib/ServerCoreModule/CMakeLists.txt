file(GLOB_RECURSE CORE_MODULE_SOURCES src/*.cpp)

include_directories(../../include/)
include_directories(include)

add_library(CoreModule SHARED ${CORE_MODULE_SOURCES})
