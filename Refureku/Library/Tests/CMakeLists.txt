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
					CustomProperties.cpp
					ThirdPartyEnumReflectionCode.cpp
					Test.cpp
					Vector3.cpp
					AB.cpp
					GeneratedCodeInCpp.cpp

					ClassTemplates/TestClassAB.cpp
					ClassTemplates/SingleTypeTemplateClassTemplate.cpp
					ClassTemplates/MultipleTypeTemplateClassTemplate.cpp
					ClassTemplates/ComplexClassTemplate.cpp

					ReworkTest.cpp

					RefurekuTests.cpp
				)

# Link to RefurekuLibrary
target_link_libraries(${RefurekuTestsTarget} PRIVATE ${RefurekuLibraryTarget})

if (MSVC)
else()
	target_compile_options(${RefurekuTestsTarget} PRIVATE -fno-rtti)
endif()

# Create the command to run RefurekuGenerator
set(RefurekuGeneratorExeName RefurekuGenerator)
set(RunTestGeneratorTarget RunRefurekuTestGenerator)

add_custom_target(${RunTestGeneratorTarget}
					WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
					COMMAND "${RefurekuGeneratorExeName}" "${PROJECT_SOURCE_DIR}/RefurekuTestsSettings.toml")

# Run the RefurekuGenerator BEFORE building the project to refresh generated files
add_dependencies(${RefurekuTestsTarget} ${RunTestGeneratorTarget})

# Add include directories
target_include_directories(${RefurekuTestsTarget} PRIVATE Include)

add_test(NAME ${RefurekuTestsTarget} COMMAND ${RefurekuTestsTarget})