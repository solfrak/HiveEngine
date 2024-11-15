set(CMAKE_CXX_STANDARD 20)

#include_directories(src)
#
#Dependencies

#You can just comment out this if you don't want to work with raylib
set(BACKEND raylib)

# For linux build, will set the default visibility to hidden
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_INLINES_HIDDEN 1)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(BACKEND STREQUAL "raylib")
    file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)
    add_library(HiveEngine SHARED ${SOURCES})
    target_compile_definitions(HiveEngine PRIVATE HEXPORTS)

#    Dependencies
    add_subdirectory(dep/raylib)
    add_library(stb_image STATIC dep/stb_image/stb_image.cpp dep/stb_image/stb_image.h)
    target_link_libraries(HiveEngine PRIVATE stb_image raylib)


#    Include directories
    target_include_directories(HiveEngine PRIVATE src)
    target_include_directories(HiveEngine PRIVATE dep/raylib/src)
    target_include_directories(HiveEngine PRIVATE dep/entt/src)
    target_include_directories(HiveEngine PRIVATE dep/easy_profiler/easy_profiler_core)

#    Precompiled header
    target_precompile_headers(HiveEngine PRIVATE src/hvpch.h)
else ()
    message("Unsupported backend")
endif ()




