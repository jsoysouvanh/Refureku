cmake_minimum_required(VERSION 3.13.5)

project(Kodgen)

# Handle specific flags for each supported compiler
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	
	# Nothing at the moment

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	
	# Nothing at the moment

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

	# Nothing at the moment

else()
	
	message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER_ID} is not supported for this project, please use Clang, GCC or MSVC")

endif()

# Information messages about cmake version and compiler
message("Cmake:		${CMAKE_VERSION}")
message("Compiler:	${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

# Enable tests
enable_testing()

add_subdirectory(Kodgen)