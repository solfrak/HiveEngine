set(CMAKE_CXX_STANDARD 20)

#Dependencies

#You can just comment out this if you don't want to work with raylib
set(BACKEND raylib)

# For linux build, will set the default visibility to hidden (hidden by default on windows using MSVC)
#set(CMAKE_CXX_VISIBILITY_PRESET hidden)
#set(CMAKE_CXX_VISIBILITY_INLINES_HIDDEN 1)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(BACKEND STREQUAL "raylib")
    file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)
    add_library(HiveEngine SHARED ${SOURCES})
    target_compile_definitions(HiveEngine PRIVATE HEXPORTS)

#    Dependencies
    add_subdirectory(dep/raylib)
    target_link_libraries(HiveEngine PRIVATE raylib)

    add_library(perfetto STATIC dep/perfetto/perfetto.cc dep/perfetto/perfetto.h)
    target_link_libraries(HiveEngine PRIVATE perfetto ${CMAKE_THREAD_LIBS_INIT})


#    Include directories
    target_include_directories(HiveEngine PRIVATE src)
    target_include_directories(HiveEngine PRIVATE dep/raylib/src)
    target_include_directories(HiveEngine PRIVATE dep/entt/src)
    target_include_directories(HiveEngine PRIVATE dep/perfetto)

#    Precompiled header
    target_precompile_headers(HiveEngine PRIVATE src/hvpch.h)
#    target_precompile_headers(HiveEngine PRIVATE dep/perfetto/perfetto.h)


    if (MSVC)
        target_compile_options(perfetto PRIVATE "/bigobj")
        target_link_libraries(HiveEngine PRIVATE ws2_32)
        add_definitions(-DWIN32_LEAN_AND_MEAN -DNOMINMAX)
        target_compile_options(HiveEngine PRIVATE "/permissive-")
    endif (MSVC)

else ()
    message("Unsupported backend")
endif ()




