add_executable(Demo_Empty demo_empty/main.cpp)
target_include_directories(Demo_Empty PRIVATE ${CMAKE_SOURCE_DIR}/HiveEngine/src)
target_link_libraries(Demo_Empty PRIVATE HiveEngine)

#Copy paste what is above for a new demo, just adjust the name and the path of the main.cpp