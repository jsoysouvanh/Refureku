cmake_minimum_required(VERSION 3.13.5)

project(RefurekuTests)

###########################################
#		Configure the tests
###########################################

set(RefurekuTestsTarget RefurekuTests)
add_executable(${RefurekuTestsTarget}
					Src/TestStruct.cpp
					Src/TestClass.cpp
					Src/TestClass2.cpp
					Src/ForwardDeclaredClass.cpp
					Src/ConstructionTrackedClass.cpp
					Src/PropertyInheritance.cpp
					Src/TestFunctions.cpp
					Src/TestVariables.cpp
					Src/TestNamespace.cpp
					Src/TestEnum.cpp
					Src/TestProperties.cpp
					Src/SingleTypeTemplateClassTemplate.cpp
					Src/MultipleTypeTemplateClassTemplate.cpp
					Src/ComplexClassTemplate.cpp
					Src/TestStaticFields.cpp
					Src/TestFields.cpp
					Src/TestFieldBase.cpp
					
					main.cpp)

# Link to RefurekuLibrary
target_link_libraries(${RefurekuTestsTarget} PUBLIC ${RefurekuLibraryTarget} gtest)

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