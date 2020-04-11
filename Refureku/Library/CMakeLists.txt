cmake_minimum_required(VERSION 3.13.5)

project(RefurekuLibrary)

# Add Refureku library
set(RefurekuLibraryTarget Refureku)
add_library(${RefurekuLibraryTarget}
				STATIC
					Source/TypeInfo/TypePart.cpp
					Source/TypeInfo/Type.cpp
					Source/TypeInfo/Entity.cpp
					Source/TypeInfo/EnumValue.cpp
					Source/TypeInfo/Database.cpp
					Source/TypeInfo/Archetypes/Archetype.cpp
					Source/TypeInfo/Archetypes/Enum.cpp
					Source/TypeInfo/Archetypes/Struct.cpp
					Source/TypeInfo/Archetypes/Class.cpp
					Source/TypeInfo/Archetypes/ArchetypeRegisterer.cpp
					Source/TypeInfo/Fields/FieldBase.cpp
					Source/TypeInfo/Fields/Field.cpp
					Source/TypeInfo/Fields/StaticField.cpp
					Source/TypeInfo/Methods/MethodBase.cpp
					Source/TypeInfo/Methods/Method.cpp
					Source/TypeInfo/Methods/StaticMethod.cpp
					Source/TypeInfo/Methods/MethodParameter.cpp
					Source/TypeInfo/Methods/MethodError.cpp
			)

# Setup warning level
if (MSVC)
	string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")	# Remove the default flag /W3
	target_compile_options(${RefurekuLibraryTarget} PUBLIC /W4)
else()	# Clang or GCC
	target_compile_options(${RefurekuLibraryTarget} PUBLIC -Wall -Wextra -Wpedantic)
endif()

# Setup language requirements
target_compile_features(${RefurekuLibraryTarget} PUBLIC cxx_std_17)

target_include_directories(${RefurekuLibraryTarget} PUBLIC Include)

add_subdirectory(Example)
add_subdirectory(Tests)