cmake_minimum_required(VERSION 3.13.5)

project(RefurekuLibrary)

# Add Refureku library
set(RefurekuLibraryTarget Refureku)
add_library(${RefurekuLibraryTarget}
				SHARED
					Source/Object.cpp

					Source/TypeInfo/TypePart.cpp
					Source/TypeInfo/Type.cpp
					Source/TypeInfo/EnumValue.cpp
					Source/TypeInfo/Database.cpp

					Source/TypeInfo/Entity/Entity.cpp
					Source/TypeInfo/Entity/EntityCast.cpp
					Source/TypeInfo/Entity/DefaultEntityRegisterer.cpp

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
					Source/TypeInfo/Archetypes/ClassTemplate.cpp
					Source/TypeInfo/Archetypes/TemplateParameter.cpp
					Source/TypeInfo/Archetypes/ClassTemplateInstance.cpp
					Source/TypeInfo/Archetypes/TemplateArgument.cpp
					Source/TypeInfo/Archetypes/ClassTemplateInstanceRegisterer.cpp

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

					Source/TypeInfo/Properties/Property.cpp
					Source/TypeInfo/Properties/CustomInstantiator.cpp
					Source/TypeInfo/Properties/ParseAllNested.cpp
					Source/TypeInfo/Properties/PropertySettings.cpp
				)

target_compile_definitions(${RefurekuLibraryTarget} PRIVATE REFUREKU_EXPORT)

# Setup compilation flags
if (MSVC)
	string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")	# Replace the default flag /W3 by /W4
	string(REGEX REPLACE "/GR" "/GR-" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")		# Replace the default flag /GR by /GR- to disable RTTI

	# Use rtti on Property file if specified
	if (GEN_PROPERTY_RTTI)
		set_source_files_properties(Source/TypeInfo/Properties/Property.cpp PROPERTIES COMPILE_FLAGS /GR)
	endif()

else()	# Clang or GCC
	target_compile_options(${RefurekuLibraryTarget} PRIVATE -Wall -Wextra -Wpedantic -fno-rtti -fvisibility=hidden)

	# Use rtti on Property file if specified
	if (GEN_PROPERTY_RTTI)
		set_source_files_properties(Source/TypeInfo/Properties/Property.cpp PROPERTIES COMPILE_FLAGS -frtti)
	endif()

endif()

# Setup language requirements
target_compile_features(${RefurekuLibraryTarget} PUBLIC cxx_std_17)

target_include_directories(${RefurekuLibraryTarget} PUBLIC Include)

add_subdirectory(Tests)