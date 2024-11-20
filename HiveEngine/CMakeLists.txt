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

    add_subdirectory(dep/easy_profiler)
    target_link_libraries(HiveEngine PRIVATE easy_profiler)


#    Include directories
    target_include_directories(HiveEngine PRIVATE src)
    target_include_directories(HiveEngine PRIVATE dep/raylib/src)
    target_include_directories(HiveEngine PRIVATE dep/entt/src)

#    Precompiled header
    target_precompile_headers(HiveEngine PRIVATE src/hvpch.h)

    install(TARGETS HiveEngine
            EXPORT HiveEngineExport
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME)

    install(DIRECTORY src/ DESTINATION include/hiveengine FILES_MATCHING PATTERN "*.h")
else ()
    message("Unsupported backend")
endif ()




