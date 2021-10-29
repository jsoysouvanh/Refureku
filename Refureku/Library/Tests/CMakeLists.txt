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
					Src/TypeTemplateClassTemplate.cpp
					Src/NonTypeTemplateClassTemplate.cpp
					Src/TemplateTemplateClassTemplate.cpp
					Src/MixedClassTemplate.cpp
					Src/TestStaticFields.cpp
					Src/TestFields.cpp
					Src/TestFieldBase.cpp
					Src/TestStaticMethods.cpp
					Src/TestMethods.cpp
					Src/BaseObject.cpp
					Src/TestMethodBase.cpp
					Src/TestDatabase.cpp
					Src/ManualEnumReflection.cpp
					Src/ManualClassReflection.cpp
					Src/ManualClassTemplateReflection.cpp
					Src/ManualVariableReflection.cpp
					Src/ManualFunctionReflection.cpp
					Src/ManualNamespaceReflection.cpp

					main.cpp)

# Add include directories
target_include_directories(${RefurekuTestsTarget} PRIVATE Include)

# Link to RefurekuLibrary
target_link_libraries(${RefurekuTestsTarget} PUBLIC ${RefurekuLibraryTarget} gtest)

if (MSVC)
	target_compile_options(${RefurekuTestsTarget} PRIVATE /MP /bigobj)
else()
endif()

# Create the command to run RefurekuGenerator
set(RefurekuGeneratorExeName RefurekuGenerator)
set(RunTestGeneratorTarget RunRefurekuTestGenerator)

add_custom_target(${RunTestGeneratorTarget}
					WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
					COMMAND "${RefurekuGeneratorExeName}" "${PROJECT_SOURCE_DIR}/RefurekuTestsSettings.toml") 

# Run the RefurekuGenerator BEFORE building the project to refresh generated files
add_dependencies(${RefurekuTestsTarget} ${RunTestGeneratorTarget})

add_test(NAME ${RefurekuTestsTarget} COMMAND ${RefurekuTestsTarget})