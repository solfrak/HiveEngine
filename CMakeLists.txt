cmake_minimum_required(VERSION 3.30.5)
project(HiveEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(Hive)
#add_subdirectory(Swarm)
add_subdirectory(Terra)
add_subdirectory(Testbed)
add_subdirectory(Cells)
