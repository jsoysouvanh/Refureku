cmake_minimum_required(VERSION 3.13.5)

project(RefurekuGenerator)

# Build dependencies
add_subdirectory(ThirdParty/Kodgen)

set(RefurekuGeneratorExeTarget RefurekuGenerator)
add_executable(${RefurekuGeneratorExeTarget} Source/main.cpp)

target_include_directories(${RefurekuGeneratorExeTarget} PUBLIC Include)

target_link_libraries(${RefurekuGeneratorExeTarget} PUBLIC Kodgen)

if (RFK_DEV)

	# Setup compilation definitions
	target_compile_definitions(${RefurekuGeneratorExeTarget} PUBLIC RFK_DEV=1)

	if (NOT MSVC) # Clang or GCC
		target_compile_options(${RefurekuGeneratorExeTarget} PUBLIC -fsanitize=address -fno-omit-frame-pointer)
		target_link_options(${RefurekuGeneratorExeTarget} PUBLIC -fsanitize=address -fno-omit-frame-pointer)
	endif()

endif()

if (MSVC)

	# Setup warning level
	string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")	# Remove the default flag /W3
	target_compile_options(${RefurekuGeneratorExeTarget} PRIVATE /W4 /MP)

else ()	# Clang or GCC

	target_compile_options(${RefurekuGeneratorExeTarget} PRIVATE -Wall -Wextra -Wpedantic)

endif()


# Copy the RefurekuSettings template file next to the generated binary
add_custom_command(	TARGET ${RefurekuGeneratorExeTarget} PRE_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy
					${PROJECT_SOURCE_DIR}/RefurekuSettings.toml
					$<IF:$<BOOL:${MSVC}>,${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/RefurekuSettings.toml,${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RefurekuSettings.toml>)

add_subdirectory(LibraryGenerator)