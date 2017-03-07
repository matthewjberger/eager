# This was created using pieces of the abandoned cmake script for Ogre at:
# https://github.com/ogre3d/clean-project/blob/master/tools/cmake/common.cmake

cmake_minimum_required(VERSION 3.0)
project(Ogre3D)

# Place targets into their own solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set the proper paths for windows
# using the OGRE_HOME environment variable.
if(MSVC)
    # Get the OGRE_HOME environment variable with unix slashes
    set(OGRE_HOME "$ENV{OGRE_HOME}")
    STRING(REGEX REPLACE "\\\\" "/" OGRE_HOME ${OGRE_HOME})

    # Set the paths to search relative to the SDK root
    set(CMAKE_MODULE_PATH "${OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
    set(OGRE_SAMPLES_INCLUDEPATH "${OGRE_HOME}/Samples/include")
    set(OGRE_BOOST_INCLUDE_PATH "${OGRE_HOME}/boost")
    set(OGRE_BOOST_LIBRARIES "${OGRE_HOME}/boost/lib")

    # Copy Media and Bin folders out to the repository
    file(COPY ${OGRE_HOME}/bin DESTINATION ${CMAKE_SOURCE_DIR})
    file(COPY ${OGRE_HOME}/media DESTINATION ${CMAKE_SOURCE_DIR})

    # Hide the console in visual studio projects in debug and release
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
endif(MSVC)

# Set the proper paths for linux/mac
if(UNIX)

    # Search for Ogre in some common locations
	if(EXISTS "/usr/local/lib/OGRE/cmake")

	  set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	  set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/Samples/Common/include/")

	elseif(EXISTS "/usr/lib/OGRE/cmake")

      # Otherwise, this one
	  set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	  set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/Samples/Common/include/")

    # apt-get installation
    # In that case environment var OGRE_HOME should be set, because .deb ogre
    # packages does not carry samples
	elseif(EXISTS "/usr/share/OGRE/cmake/modules")

	  set(CMAKE_MODULE_PATH "/usr/share/OGRE/cmake/modules/;${CMAKE_MODULE_PATH}")
	  set(OGRE_SAMPLES_INCLUDEPATH "$ENV{OGRE_HOME}/Samples/Common/include/")

	else ()
	  message(SEND_ERROR "Failed to find module path.")
	endif(EXISTS "/usr/local/lib/OGRE/cmake")
endif(UNIX)

# Support C++11
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_STANDARD 11)

# Set compiler flags
# -w Disables all warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")

# Find libraries
find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)

# Display an error if OIS was not found
if(NOT OIS_FOUND)
	message(SEND_ERROR "Failed to find OIS.")
endif()

# Add include directories
include_directories(${OGRE_INCLUDE_DIRS}
                    ${OIS_INCLUDE_DIRS}
                    ${OGRE_SAMPLES_INCLUDEPATH}
                    ${OGRE_Overlay_INCLUDE_DIRS})
# Add MSVC Boost include and library path
if(MSVC)
	include_directories(${OGRE_BOOST_INCLUDE_PATH})
	link_directories(${OGRE_BOOST_LIBRARIES})
endif(MSVC)

# Create file globs
file(GLOB_RECURSE PROJECT_HEADERS src/*.h)
file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
file(GLOB         PROJECT_CONFIGS CMakeLists.txt
                                  README.md
                                 .gitignore)

# Define source file groupings
source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Configs" FILES ${PROJECT_CONFIGS})

# Add configs to the source grouping for Visual Studio
if(MSVC)
    file(GLOB PROJECT_CONFIGS_WINDOWS_RELEASE src/config/windows/release/*.cfg)
    file(GLOB PROJECT_CONFIGS_WINDOWS_DEBUG   src/config/windows/debug/*.cfg)
    file(GLOB PROJECT_CONFIGS_UNIX            src/config/unix/*.cfg)

    source_group("Configs\\Windows_Configs\\Release" FILES ${PROJECT_CONFIGS_WINDOWS_RELEASE})
    source_group("Configs\\Windows_Configs\\Debug"   FILES ${PROJECT_CONFIGS_WINDOWS_DEBUG})
    source_group("Configs\\Unix_Configs"             FILES ${PROJECT_CONFIGS_UNIX})
endif(MSVC)

# Define the executable
add_executable( ${PROJECT_NAME} ${PROJECT_HEADERS}
                                ${PROJECT_SOURCES}
                                ${PROJECT_CONFIGS}
                                ${PROJECT_CONFIGS_WINDOWS_RELEASE}
                                ${PROJECT_CONFIGS_WINDOWS_DEBUG}
                                ${PROJECT_CONFIGS_UNIX})

# Define libraries to link to
target_link_libraries( ${PROJECT_NAME} ${OGRE_LIBRARIES}
                                       ${OIS_LIBRARIES}
                                       ${OGRE_Paging_LIBRARIES}
                                       ${OGRE_Terrain_LIBRARIES}
                                       ${OGRE_Property_LIBRARIES}
                                       ${OGRE_RTShaderSystem_LIBRARIES}
                                       ${OGRE_Volume_LIBRARIES}
                                       ${OGRE_Overlay_LIBRARIES}
                                       ${OGRE_MeshLodGenerator_LIBRARIES}
                                       ${OGRE_HLMS_LIBRARIES}
                                       ${OGRE_Bites_LIBRARIES})

# Output to bin directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if(MSVC)
    # Set the startup project
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

    # Set the working directory
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/debug)

    # Copy debug configs to output folder after a successful bug build
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                              COMMAND ${CMAKE_COMMAND} -E copy_directory
                              ${CMAKE_SOURCE_DIR}/src/config/windows/debug
                              $<TARGET_FILE_DIR:${PROJECT_NAME}>)

    # Copy release configs to output folder after a successful build
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                              COMMAND ${CMAKE_COMMAND} -E copy_directory
                              ${CMAKE_SOURCE_DIR}/src/config/windows/release
                              $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif(MSVC)

if(UNIX)
	# Copy configs to output folder after a successful build
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                              COMMAND ${CMAKE_COMMAND} -E copy_directory
                              ${CMAKE_SOURCE_DIR}/src/config/unix
                              $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif(UNIX)
