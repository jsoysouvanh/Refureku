cmake_minimum_required(VERSION 3.13.5)

project(RefurekuGenerator)

# Build dependencies
add_subdirectory(ThirdParty/Kodgen)

set(RefurekuGeneratorExeTarget RefurekuGenerator)
add_executable(${RefurekuGeneratorExeTarget} Source/main.cpp)

# Setup compilation definitions
if (RFK_DEV)
	target_compile_definitions(${RefurekuGeneratorExeTarget} PUBLIC RFK_DEV=1)
endif()

# Warning level
if (MSVC)
	string(REGEX REPLACE " /W3" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")	# Remove the default flag /W3 - get /W4 propagated from Kodgen
endif()

target_include_directories(${RefurekuGeneratorExeTarget} PUBLIC Include)

target_link_libraries(${RefurekuGeneratorExeTarget} PUBLIC Kodgen)

# Copy the RefurekuSettings template file next to the generated binary
add_custom_command(	TARGET ${RefurekuGeneratorExeTarget} PRE_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy
					${PROJECT_SOURCE_DIR}/RefurekuSettings.toml
					$<IF:$<BOOL:${MSVC}>,${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/RefurekuSettings.toml,${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RefurekuSettings.toml>)

add_subdirectory(LibraryGenerator)