cmake_minimum_required(VERSION 3.13.5)

project(RefurekuLibrary)

# Add Refureku library
set(RefurekuLibraryTarget Refureku)
add_library(${RefurekuLibraryTarget}
				STATIC
					Source/Exceptions/ArgCountMismatch.cpp
					Source/Exceptions/TypeMismatch.cpp
					Source/Exceptions/ReturnTypeMismatch.cpp
					Source/Exceptions/ArgTypeMismatch.cpp
					Source/Exceptions/BadNamespaceFormat.cpp
					Source/Exceptions/OutOfRange.cpp

					Source/TypeInfo/TypePart.cpp
					Source/TypeInfo/Type.cpp
					Source/TypeInfo/Entity.cpp
					Source/TypeInfo/EntityCast.cpp
					Source/TypeInfo/EnumValue.cpp
					Source/TypeInfo/DefaultEntityRegisterer.cpp
					Source/TypeInfo/Database.cpp

					Source/TypeInfo/Properties/SimpleProperty.cpp
					Source/TypeInfo/Properties/ComplexProperty.cpp
					Source/TypeInfo/Properties/PropertyGroup.cpp

					Source/TypeInfo/Namespaces/Namespace.cpp
					Source/TypeInfo/Namespaces/NamespaceFragment.cpp
					Source/TypeInfo/Namespaces/NamespaceFragmentRegisterer.cpp

					Source/TypeInfo/Archetypes/Archetype.cpp
					Source/TypeInfo/Archetypes/FundamentalArchetype.cpp
					Source/TypeInfo/Archetypes/Enum.cpp
					Source/TypeInfo/Archetypes/Struct.cpp
					Source/TypeInfo/Archetypes/Class.cpp
					Source/TypeInfo/Archetypes/ArchetypeRegisterer.cpp
					Source/TypeInfo/Archetypes/GetArchetype.cpp

					Source/TypeInfo/Variables/VariableBase.cpp
					Source/TypeInfo/Variables/Variable.cpp
					Source/TypeInfo/Variables/FieldBase.cpp
					Source/TypeInfo/Variables/Field.cpp
					Source/TypeInfo/Variables/StaticField.cpp

					Source/TypeInfo/Functions/FunctionBase.cpp
					Source/TypeInfo/Functions/Function.cpp
					Source/TypeInfo/Functions/MethodBase.cpp
					Source/TypeInfo/Functions/Method.cpp
					Source/TypeInfo/Functions/StaticMethod.cpp
					Source/TypeInfo/Functions/FunctionParameter.cpp
				)

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