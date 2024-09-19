
file(GLOB_RECURSE SOURCES src/*.cpp)

include_directories(include)

add_library(message SHARED ${SOURCES})

target_include_directories(message PUBLIC ${PROJECT_SOURCE_DIR}/include)
