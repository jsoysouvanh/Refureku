cmake_minimum_required(VERSION 3.13.5)

project(RefurekuLibrary)

# Add Refureku library
set(RefurekuLibraryTarget Refureku_${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}_${CMAKE_BUILD_TYPE})
add_library(${RefurekuLibraryTarget}
				STATIC
					Source/TypeInfo/Type.cpp
					Source/TypeInfo/Struct.cpp
					Source/TypeInfo/Class.cpp
					Source/TypeInfo/Field.cpp
					Source/TypeInfo/Method.cpp)

# Setup language requirements
target_compile_features(${RefurekuLibraryTarget} PUBLIC cxx_std_17)

target_include_directories(${RefurekuLibraryTarget} PUBLIC Include)

add_subdirectory(Example)