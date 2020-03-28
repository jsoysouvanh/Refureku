cmake_minimum_required(VERSION 3.13.5)

project(RefurekuLibrary)

# Add Refureku library
set(RefurekuLibraryTarget Refureku_${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}_${CMAKE_BUILD_TYPE})
add_library(${RefurekuLibraryTarget}
				STATIC
					Source/TypeInfo/Entity.cpp
					Source/TypeInfo/Archetype.cpp
					Source/TypeInfo/Struct.cpp
					Source/TypeInfo/Class.cpp
					Source/TypeInfo/Field.cpp
					Source/TypeInfo/MethodBase.cpp
					Source/TypeInfo/Method.cpp
					Source/TypeInfo/StaticMethod.cpp
			)

# Setup language requirements
target_compile_features(${RefurekuLibraryTarget} PUBLIC cxx_std_17)

target_include_directories(${RefurekuLibraryTarget} PUBLIC Include)

add_subdirectory(Example)