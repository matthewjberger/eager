# This was created using pieces of the abandoned cmake script for Ogre at:
# https://github.com/ogre3d/clean-project/blob/master/tools/cmake/common.cmake

cmake_minimum_required(VERSION 3.0)
project(Ogre3D)

# Set the proper paths for windows
# using the OGRE_HOME environment variable.
if(WIN32)
	set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
	set(OGRE_SAMPLES_INCLUDEPATH "$ENV{OGRE_HOME}/Samples/include")
endif(WIN32)

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

# CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
# differentiation between debug and release builds.
if (CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

# Support C++14
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

# Create file globs
file(GLOB_RECURSE PROJECT_HEADERS src/*.h)
file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
file(GLOB         PROJECT_CONFIGS CMakeLists.txt
                                  README.md
                                 .gitattributes
                                 .gitignore)

# Define source file groupings
source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Configs" FILES ${PROJECT_CONFIGS})

# Define the executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Define libraries to link to
target_link_libraries( ${PROJECT_NAME} ${OGRE_LIBRARIES}
                                       ${OIS_LIBRARIES}
                                       ${OGRE_Overlay_LIBRARIES})

# Output to bin directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Copy configs to output folder after a successful build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/src/config
                   $<TARGET_FILE_DIR:${PROJECT_NAME}>)
