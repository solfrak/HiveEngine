set(CMAKE_CXX_STANDARD 20)


file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)
list(REMOVE_ITEM SOURCES src/hvpch.h)

add_library(Hive SHARED ${SOURCES})
target_include_directories(Hive PRIVATE src)
target_precompile_headers(Hive PRIVATE src/hvpch.h)

add_subdirectory(dep/raylib)
target_include_directories(Hive PRIVATE dep/raylib/src)
target_link_libraries(Hive PRIVATE raylib_static)
