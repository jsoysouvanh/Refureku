cmake_minimum_required(VERSION 3.14.0)

project(RefurekuGenerator)

# Build dependencies
add_subdirectory(ThirdParty/Kodgen)

set(RefurekuGeneratorExeTarget RefurekuGenerator)
add_executable(${RefurekuGeneratorExeTarget} Source/main.cpp)

target_include_directories(${RefurekuGeneratorExeTarget} PRIVATE Include)

target_link_libraries(${RefurekuGeneratorExeTarget} PRIVATE Kodgen)

set_target_properties(${RefurekuGeneratorExeTarget} PROPERTIES
						BUILD_RPATH_USE_ORIGIN TRUE
						SKIP_BUILD_RPATH FALSE)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set_target_properties(${RefurekuGeneratorExeTarget} PROPERTIES
							MACOSX_RPATH TRUE
							BUILD_RPATH "@executable_path")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set_target_properties(${RefurekuGeneratorExeTarget} PROPERTIES
							BUILD_RPATH "\$ORIGIN")
endif()

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