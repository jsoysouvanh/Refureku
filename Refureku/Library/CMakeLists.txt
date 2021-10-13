cmake_minimum_required(VERSION 3.13.5)

project(RefurekuLibrary)

# Add Refureku library
set(RefurekuLibraryTarget Refureku)
add_library(${RefurekuLibraryTarget}
				SHARED
					Source/Object.cpp

					Source/Properties/Property.cpp
					Source/Properties/Instantiator.cpp
					Source/Properties/ParseAllNested.cpp
					Source/Properties/PropertySettings.cpp

					Source/TypeInfo/TypePart.cpp
					Source/TypeInfo/Type.cpp
					Source/TypeInfo/Database.cpp

					Source/TypeInfo/Entity/Entity.cpp
					Source/TypeInfo/Entity/EntityHash.cpp
					Source/TypeInfo/Entity/EntityCast.cpp
					Source/TypeInfo/Entity/DefaultEntityRegisterer.cpp

					Source/TypeInfo/Namespace/Namespace.cpp
					Source/TypeInfo/Namespace/NamespaceFragment.cpp
					Source/TypeInfo/Namespace/NamespaceFragmentRegisterer.cpp

					Source/TypeInfo/Archetypes/Archetype.cpp
					Source/TypeInfo/Archetypes/FundamentalArchetype.cpp
					Source/TypeInfo/Archetypes/Enum.cpp
					Source/TypeInfo/Archetypes/EnumValue.cpp
					Source/TypeInfo/Archetypes/Struct.cpp
					Source/TypeInfo/Archetypes/ParentStruct.cpp
					Source/TypeInfo/Archetypes/ArchetypeRegisterer.cpp
					Source/TypeInfo/Archetypes/GetArchetype.cpp

					Source/TypeInfo/Archetypes/Template/ClassTemplate.cpp
					Source/TypeInfo/Archetypes/Template/TemplateParameter.cpp
					Source/TypeInfo/Archetypes/Template/TypeTemplateParameter.cpp
					Source/TypeInfo/Archetypes/Template/NonTypeTemplateParameter.cpp
					Source/TypeInfo/Archetypes/Template/TemplateTemplateParameter.cpp
					Source/TypeInfo/Archetypes/Template/TemplateArgument.cpp
					Source/TypeInfo/Archetypes/Template/TypeTemplateArgument.cpp
					Source/TypeInfo/Archetypes/Template/NonTypeTemplateArgument.cpp
					Source/TypeInfo/Archetypes/Template/TemplateTemplateArgument.cpp
					Source/TypeInfo/Archetypes/Template/ClassTemplateInstantiation.cpp
					Source/TypeInfo/Archetypes/Template/ClassTemplateInstantiationRegisterer.cpp

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

target_compile_definitions(${RefurekuLibraryTarget} PRIVATE REFUREKU_EXPORT)

# Setup compilation flags
if (MSVC)
	string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")	# Replace the default flag /W3 by /W4
	string(REGEX REPLACE "/GR" "/GR-" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")		# Replace the default flag /GR by /GR- to disable RTTI

	# Use rtti on Property file if specified
	if (RFK_GEN_PROPERTY_RTTI)
		set_source_files_properties(Source/TypeInfo/Properties/Property.cpp PROPERTIES COMPILE_FLAGS /GR)
	endif()

else()	# Clang or GCC
	target_compile_options(${RefurekuLibraryTarget} PRIVATE -Wall -Wextra -Wpedantic -fno-rtti -fvisibility-ms-compat -fvisibility-inlines-hidden)

	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND RFK_GEN_CODECOV_REPORT)
		target_compile_options(${RefurekuLibraryTarget} PUBLIC --coverage)
		target_link_options(${RefurekuLibraryTarget} PUBLIC --coverage)
	endif()

	# Use rtti on Property file if specified
	if (RFK_GEN_PROPERTY_RTTI)
		set_source_files_properties(Source/TypeInfo/Properties/Property.cpp PROPERTIES COMPILE_FLAGS -frtti)
	endif()

endif()

# Setup language requirements
target_compile_features(${RefurekuLibraryTarget} PUBLIC cxx_std_17)

target_include_directories(${RefurekuLibraryTarget}
							PUBLIC	Include/Public
							PRIVATE Include/Private)

#Force GTest to link with shared CRT since Refureku links with shared CRT
set(gtest_force_shared_crt ON CACHE BOOL "GTest use shared CRT (MD[d])" FORCE)
add_subdirectory(ThirdParty/GoogleTests)
add_subdirectory(Tests)