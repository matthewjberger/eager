cmake_minimum_required(VERSION 3.0)
project(Ogre3D)

# Support C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")

include_directories(
    /usr/local/include/OGRE
    /usr/local/include/OGRE/Threading
    /usr/local/include/OGRE/Property
    /usr/local/include/OGRE/Overlay
    /usr/local/include/OGRE/Volume
    /usr/local/include/OGRE/RTShaderSystem
    /usr/local/include/OGRE/Paging
    /usr/local/include/OGRE/GLX
    /usr/local/include/OGRE/RenderSystems
    /usr/local/include/OGRE/Plugins
    /usr/local/include/OGRE/Terrain
    /usr/local/include/OGRE/RenderSystems/GL
    /usr/local/include/OGRE/RenderSystems/GL/GLX
    /usr/local/include/OGRE/RenderSystems/GL/GL
    /usr/local/include/OGRE/Plugins/PCZSceneManager
    /usr/local/include/OGRE/Plugins/OctreeSceneManager
    /usr/local/include/OGRE/Plugins/ParticleFX
    /usr/local/include/OGRE/Plugins/OctreeZone
    /usr/local/include/OGRE/Plugins/BSPSceneManager
    /usr/include/OIS
    )

# Add source files
file(GLOB PROJECT_SOURCES src/*.cpp)

# Define the executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Define libraries to link to
target_link_libraries( ${PROJECT_NAME} OgreMain OgreOverlay OIS boost_system )

# Output to bin directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Copy configs to output folder after a successful build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/src/config
                   $<TARGET_FILE_DIR:${PROJECT_NAME}>)
