# Check versions
message(STATUS "CMake version: ${CMAKE_VERSION}")
cmake_minimum_required(VERSION 3.1)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set the project name
set(PNAME Octalot)
project(${PNAME})

include_directories(include)

# Glob all thr sources into their values
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h" "include/*.hpp")

add_executable(${PNAME} ${SOURCES} ${HEADERS})

# Follow the sub directory structure to add sub-filters in VS
# Gotta do it one by one unfortunately

foreach (source IN ITEMS ${SOURCES})
	if (IS_ABSOLUTE "${source}")

		get_filename_component(filename ${source} DIRECTORY)

		STRING(REGEX REPLACE "/" "\\\\" filename ${filename})
		
		string(REGEX MATCHALL "src(.*)" substrings ${filename})
		list(GET substrings 0 substring)
		
		SOURCE_GROUP(${substring} FILES ${source}) 
		
	endif()
endforeach()

foreach (source IN ITEMS ${HEADERS})
	if (IS_ABSOLUTE "${source}")

		get_filename_component(filename ${source} DIRECTORY)

		STRING(REGEX REPLACE "/" "\\\\" filename ${filename})
		
		string(REGEX MATCHALL "include(.*)" substrings ${filename})
		list(GET substrings 0 substring)
		
		SOURCE_GROUP(${substring} FILES ${source}) 
		
	endif()
endforeach()

if (NOT WIN32)
	target_link_libraries (${PNAME} -lpthread)
endif()

# Setup to use C++14
set_property(TARGET ${PNAME} PROPERTY CXX_STANDARD 14)

