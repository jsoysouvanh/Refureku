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
					Source/TypeInfo/Methods/Exceptions/ArgCountMismatchException.cpp
					Source/TypeInfo/Methods/Exceptions/ReturnTypeMismatchException.cpp
					Source/TypeInfo/Methods/Exceptions/ArgTypeMismatchException.cpp)

# Setup compilation flags
if (MSVC)
	string(REGEX REPLACE " /W[0-4]" " /W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")	# Replace the default flag /W3 by /W4
	string(REGEX REPLACE " /GR" " /GR-" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")		# Replace the default flag /GR by /GR- to disable RTTI
else()	# Clang or GCC
	target_compile_options(${RefurekuLibraryTarget} PRIVATE -Wall -Wextra -Wpedantic -fno-rtti)
endif()

# Setup language requirements
target_compile_features(${RefurekuLibraryTarget} PUBLIC cxx_std_17)

target_include_directories(${RefurekuLibraryTarget} PUBLIC Include)

add_subdirectory(Tests)