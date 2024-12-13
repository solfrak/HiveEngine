add_executable(Sandbox main.cpp)
target_link_libraries(Sandbox PRIVATE Hive)
target_include_directories(Sandbox PRIVATE ../HiveEngine/src)