cmake_minimum_required(VERSION 3.13.5)

project(RefurekuLibrary)

# Add Refureku library
set(RefurekuLibraryTarget Refureku_${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}_${CMAKE_BUILD_TYPE})
add_library(${RefurekuLibraryTarget}
				STATIC
					Source/TypeInfo/Entity.cpp
					Source/TypeInfo/PropertyGroup.cpp
					Source/TypeInfo/Archetypes/Archetype.cpp
					Source/TypeInfo/Archetypes/Struct.cpp
					Source/TypeInfo/Archetypes/Class.cpp
					Source/TypeInfo/Fields/FieldBase.cpp
					Source/TypeInfo/Fields/Field.cpp
					Source/TypeInfo/Fields/StaticField.cpp
					Source/TypeInfo/Methods/MethodBase.cpp
					Source/TypeInfo/Methods/Method.cpp
					Source/TypeInfo/Methods/StaticMethod.cpp
					Source/TypeInfo/Type.cpp
					Source/TypeInfo/Database.cpp
			)

# Setup language requirements
target_compile_features(${RefurekuLibraryTarget} PUBLIC cxx_std_17)

target_include_directories(${RefurekuLibraryTarget} PUBLIC Include)

add_subdirectory(Example)