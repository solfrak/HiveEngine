cmake_minimum_required(VERSION 3.30.5)
option(swarm_use_vulkan "Enable Vulkan support" OFF)

# Find Vulkan and set up nvrhi options BEFORE adding nvrhi subdirectory
if(swarm_use_vulkan STREQUAL "ON")
 find_package(Vulkan REQUIRED)
 set(NVRHI_WITH_VULKAN ON CACHE BOOL "" FORCE)
endif()

add_subdirectory(extern/nvrhi)

add_library(swarm STATIC)
target_include_directories(swarm PUBLIC include PRIVATE src)
target_precompile_headers(swarm PRIVATE include/swarm/precomp.h)

# Link against Hive (core module)
target_link_libraries(swarm PUBLIC hive)

# Add source files here
target_sources(swarm PRIVATE
        src/swarm/swarm.cpp
)

if(swarm_use_vulkan STREQUAL "ON")
 add_subdirectory(extern/vk-bootstrap)
 target_compile_definitions(swarm PUBLIC SWARM_VULKAN_ENABLED)
 target_sources(swarm PRIVATE
         src/swarm/backend/vulkan/vulkanloader.cpp
         src/swarm/backend/vulkan/swarmvk.cpp
         src/swarm/backend/vulkan/vkinstance.cpp
         src/swarm/backend/vulkan/vkphysicaldevice.cpp
         src/swarm/backend/vulkan/vksurface.cpp
         src/swarm/backend/vulkan/vkdevice.cpp
         src/swarm/backend/vulkan/vkswapchain.cpp

         src/swarm/backend/vulkan/platform/linux/vksurface.linux.cpp
         src/swarm/backend/vulkan/platform/linux/vksurface.linux.wayland.cpp
         src/swarm/backend/vulkan/platform/linux/vksurface.linux.x11.cpp
 )

 target_link_libraries(swarm PUBLIC Vulkan::Vulkan nvrhi_vk vk-bootstrap)
endif()

target_link_libraries(swarm PUBLIC nvrhi)
