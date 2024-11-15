function(add_dll_copy_to_target target)
    add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:HiveEngine> $<TARGET_FILE_DIR:${target}>
            COMMENT "Copying HiveEngine.dll to ${target} directory"
    )
endfunction()

add_executable(Demo_Logger demo_logging/main.cpp)
target_include_directories(Demo_Logger PRIVATE ${CMAKE_SOURCE_DIR}/HiveEngine/src)
target_link_libraries(Demo_Logger PRIVATE HiveEngine)
add_dll_copy_to_target(Demo_Logger)

add_executable(Demo_Profilling demo_profilling/main.cpp)
target_include_directories(Demo_Profilling PRIVATE ${CMAKE_SOURCE_DIR}/HiveEngine/src)
target_link_libraries(Demo_Profilling PRIVATE HiveEngine)
add_dll_copy_to_target(Demo_Profilling)

add_executable(Demo_Window demo_window/main.cpp)
target_include_directories(Demo_Window PRIVATE ${CMAKE_SOURCE_DIR}/HiveEngine/src)
target_link_libraries(Demo_Window PRIVATE HiveEngine)
add_dll_copy_to_target(Demo_Window)

#Copy paste what is above for a new demo, just adjust the name and the path of the main.cpp