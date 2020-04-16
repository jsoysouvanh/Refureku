cmake_minimum_required(VERSION 3.13.5)

project(RefurekuGenerator)

# Build dependencies
add_subdirectory(Submodules/Kodgen)

# Add Refureku generator executable
set(RefurekuGeneratorTarget RefurekuGenerator)
add_executable(${RefurekuGeneratorTarget}
				Source/FileParser.cpp
				Source/GeneratedEntityCodeTemplate.cpp
				Source/GeneratedClassCodeTemplate.cpp
				Source/GeneratedEnumCodeTemplate.cpp
				Source/FileGenerator.cpp

				Source/main.cpp
				)

# Warning level
if (MSVC)
	string(REGEX REPLACE " /W3" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")	# Remove the default flag /W3 - get /W4 propagated from Kodgen
endif()

target_include_directories(${RefurekuGeneratorTarget} PRIVATE Include)

# Link to Kodgen library
target_link_libraries(${RefurekuGeneratorTarget} PRIVATE Kodgen)

# Copy the RefurekuSettings template file next to the generated binary
add_custom_command(	TARGET ${RefurekuGeneratorTarget} PRE_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy
					${PROJECT_SOURCE_DIR}/RefurekuSettings.toml
					${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RefurekuSettings.toml)