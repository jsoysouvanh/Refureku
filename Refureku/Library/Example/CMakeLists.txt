cmake_minimum_required(VERSION 3.13.5)

project(RefurekuUsageExample)

###########################################
#		Configure the demo project
###########################################

set(RefurekuDemoTarget RefurekuDemo)
add_executable(${RefurekuDemoTarget}
					Source/ExampleClass.cpp

					Source/main.cpp
				)

# Link to RefurekuLibrary
target_link_libraries(${RefurekuDemoTarget} PRIVATE ${RefurekuLibraryTarget})

# Create the command to run RefurekuGenerator
set(RefurekuGeneratorExeName RefurekuGenerator)
set(RunGeneratorTarget RunRefurekuGenerator)

# Pass our project source directory path to the generator (first argument)
add_custom_target(${RunGeneratorTarget} COMMAND ${RefurekuGeneratorExeName} ${PROJECT_SOURCE_DIR})

# Run the RefurekuGenerator BEFORE building the project to refresh generated files
add_dependencies(${RefurekuDemoTarget} ${RunGeneratorTarget})

# Add include directories
target_include_directories(${RefurekuDemoTarget} PRIVATE Include)