add_executable(Demo_Logger demo_logging/main.cpp)
target_include_directories(Demo_Logger PRIVATE ${CMAKE_SOURCE_DIR}/HiveEngine/src)
target_link_libraries(Demo_Logger PRIVATE HiveEngine)

add_executable(Demo_Profilling demo_profilling/main.cpp)
target_include_directories(Demo_Profilling PRIVATE ${CMAKE_SOURCE_DIR}/HiveEngine/src)
target_link_libraries(Demo_Profilling PRIVATE HiveEngine)

#Copy paste what is above for a new demo, just adjust the name and the path of the main.cpp