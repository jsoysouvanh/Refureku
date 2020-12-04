cmake_minimum_required(VERSION 3.13.5)

project(RefurekuTests)

###########################################
#		Configure the tests
###########################################

set(RefurekuTestsTarget RefurekuTests)
add_executable(${RefurekuTestsTarget}
					ExampleClass.cpp
					ExampleClass2.cpp
					CustomString.cpp
					ThirdPartyEnumReflectionCode.cpp
					Test.cpp
					GeneratedCodeInCpp.cpp

					RefurekuTests.cpp
				)

# Link to RefurekuLibrary
target_link_libraries(${RefurekuTestsTarget} PRIVATE ${RefurekuLibraryTarget})

# Create the command to run RefurekuGenerator
set(RefurekuGeneratorExeName RefurekuGenerator)
set(RunTestGeneratorTarget RunRefurekuTestGenerator)

add_custom_target(${RunTestGeneratorTarget}
					WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
					COMMAND ${RefurekuGeneratorExeName})

# Run the RefurekuGenerator BEFORE building the project to refresh generated files
add_dependencies(${RefurekuTestsTarget} ${RunTestGeneratorTarget})

# Add include directories
target_include_directories(${RefurekuTestsTarget} PRIVATE Include)

add_test(NAME ${RefurekuTestsTarget} COMMAND ${RefurekuTestsTarget})