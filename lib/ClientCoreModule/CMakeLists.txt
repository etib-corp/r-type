file(GLOB_RECURSE CLIENT_CORE_MODULE_SOURCES src/*.cpp)

include_directories(../../include/)
include_directories(include)

add_library(ClientCoreModule SHARED ${CLIENT_CORE_MODULE_SOURCES})
