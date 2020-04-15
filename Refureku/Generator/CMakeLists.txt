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