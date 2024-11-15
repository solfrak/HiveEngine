function(add_dll_copy_to_target target)
    add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:HiveEngine> $<TARGET_FILE_DIR:${target}>
            COMMENT "Copying HiveEngine.dll to ${target} directory"
    )
endfunction()

add_executable(Demo_Empty demo_empty/main.cpp)
target_include_directories(Demo_Empty PRIVATE ${CMAKE_SOURCE_DIR}/HiveEngine/src)
target_link_libraries(Demo_Empty PRIVATE HiveEngine)
add_dll_copy_to_target(Demo_Empty)

#Copy paste what is above for a new demo, just adjust the name and the path of the main.cpp