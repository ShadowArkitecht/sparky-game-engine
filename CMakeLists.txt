###################################################################################################
#
# Sparky Engine
# 2016 - Benjamin Carter (benjamin.mark.carter@hotmail.com)
#
# This software is provided 'as-is', without any express or implied warranty.
# In no event will the authors be held liable for any damages arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it freely,
# subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented;
#    you must not claim that you wrote the original software.
#    If you use this software in a product, an acknowledgement
#    in the product documentation would be appreciated but is not required.
#
# 2. Altered source versions must be plainly marked as such,
#    and must not be misrepresented as being the original software.
#
# 3. This notice may not be removed or altered from any source distribution.
#
###################################################################################################

###################
# Setup
###################
cmake_minimum_required(VERSION 2.8.3)

project(sparky)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/include)
#Add the library path of all the Window dependencies
set(DEP_LIBS ${CMAKE_SOURCE_DIR}/dependencies/lib)


###################
# SDL2
###################
# Find the headers and libraries
find_library(SDL2_LIBRARY NAMES SDL2 PATHS ${DEP_LIBS}/SDL2)
# Print the directory of the SDL2 libs.
message(STATUS "${SDL2_LIBRARY}")
# Include the SDL2Main lib if need be.
if (NOT SDL2_BUILDING_LIBRARY)

	find_library(SDL2MAIN_LIBRARY NAMES SDL2main PATHS ${DEP_LIBS}/SDL2)

	message(STATUS "${SDL2MAIN_LIBRARY}")

endif()

if (SDL2_LIBRARY)
	# State that SDL2 is linking
	message(STATUS "SDL2 is linking to project.")
	# Set all the libraries for use.
	set(SDL2_LIBRARIES ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY})
	# Include the SDL2 ibraries.
	link_libraries(${SDL2_LIBRARIES})

else()
	message(FATAL_ERROR "SDL2 has failed to be located!")
endif()


###################
# SDL_image
###################
# Find the SDL2_image library.
find_library(SDL_IMAGE_LIBRARY NAMES SDL2_image PATHS ${DEP_LIBS}/SDL_image)
# Print the result of the SDL2_image library.
message(STATUS "${SDL_IMAGE_LIBRARY}")

if (SDL_IMAGE_LIBRARY)
	# State that SDL2_image is linking
	message(STATUS "SDL2_image is linking to project.")
	# Link the SDL2 library
	link_libraries(${SDL_IMAGE_LIBRARY})

else()
	message(FATAL_ERROR "SDL2_image has failed to be located!")
endif()


###################
# OpenGL
###################
find_package(OpenGL REQUIRED)

if (OPENGL_FOUND)

	message(STATUS "OpenGL is linking to project.")
	link_libraries(${OPENGL_gl_LIBRARY})

else()
	message(FATAL_ERROR "OpenGL was not found!")
endif()


###################
# GLEW
###################
# GLEW lib name is different on anything but Windows...
if (WIN32)
	set(GLEW_LIB_NAME glew32)
else ()
	set(GLEW_LIB_NAME GLEW)
endif ()
# Find the GLEW library.
find_library(GLEW_LIBRARY NAMES ${GLEW_LIB_NAME} PATHS ${DEP_LIBS}/GLEW)
# State the status of the GLEW searching.
message(STATUS ${GLEW_LIBRARY})

if (GLEW_LIBRARY)

	message(STATUS "GLEW is linking to project.")
	# Link GLEW.
	link_libraries(${GLEW_LIBRARY})

endif()


###################
# Assimp
###################
find_library(ASSIMP_LIBRARY NAMES assimpd PATHS ${DEP_LIBS}/assimp)

message(STATUS "${ASSIMP_LIBRARY}")

if (ASSIMP_LIBRARY)

	message(STATUS "Assimp is linking to project.")
	# Link Assimp.
	link_libraries(${ASSIMP_LIBRARY})
endif()


###################
# libnoise
###################
find_library(LIBNOISE_LIBRARY NAMES libnoise PATHS ${DEP_LIBS}/libnoise)

message(STATUS "${LIBNOISE_LIBRARY}")

if (LIBNOISE_LIBRARY)

	message(STATUS "Libnoise is linking to project.")
	# Link libnoise.
	link_libraries(${LIBNOISE_LIBRARY})
endif()


###################
# Executable
###################
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /SAFESEH:NO")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /SAFESEH:NO")

file(GLOB HEADERS "include/sparky/core/*.hpp"       "include/sparky/core/*.inl"
				  "include/sparky/ext/*.h"          "include/sparky/ext/*.inl"
				  "include/sparky/generation/*.hpp" "include/sparky/generation/*.inl"
				  "include/sparky/input/*.hpp"      "include/sparky/input/*.inl"
				  "include/sparky/lighting/*.hpp"   "include/sparky/lighting/*.inl"
				  "include/sparky/math/*.hpp"       "include/sparky/math/*.inl"
				  "include/sparky/rendering/*.hpp"  "include/sparky/rendering/*.inl"
				  "include/sparky/utils/*.hpp"      "include/sparky/utils/*.inl"
				  ${CMAKE_SOURCE_DIR}/game.hpp)

file(GLOB SRC "src/core/*.cpp"
							"src/ext/*.cpp"
							"src/generation/*.cpp"
							"src/input/*.cpp"
							"src/lighting/*.cpp"
							"src/math/*.cpp"
							"src/rendering/*.cpp"
							"src/utils/*.cpp"
							${CMAKE_SOURCE_DIR}/game.cpp
							${CMAKE_SOURCE_DIR}/main.cpp)

add_executable(app ${HEADERS} ${SRC})

###################
# Post-Build
###################
# Window specific, Adds DLL's to the current build.
if (WIN32)
	add_custom_command(TARGET app POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/dependencies/bin/SDL" $<TARGET_FILE_DIR:app>)
	add_custom_command(TARGET app POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/dependencies/bin/SDL_image" $<TARGET_FILE_DIR:app>)
	add_custom_command(TARGET app POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/dependencies/bin/GL" $<TARGET_FILE_DIR:app>)
	add_custom_command(TARGET app POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/dependencies/bin/libnoise" $<TARGET_FILE_DIR:app>)
	add_custom_command(TARGET app POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/dependencies/bin/assimp" $<TARGET_FILE_DIR:app>)
endif()
