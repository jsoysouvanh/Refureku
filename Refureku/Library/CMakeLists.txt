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

					Source/TypeInfo/TypePartAPI.cpp
					Source/TypeInfo/TypeAPI.cpp
					Source/TypeInfo/DatabaseAPI.cpp

					Source/TypeInfo/Entity/Entity.cpp
					Source/TypeInfo/Entity/EntityHash.cpp
					Source/TypeInfo/Entity/EntityCastAPI.cpp
					Source/TypeInfo/Entity/DefaultEntityRegistererAPI.cpp

					Source/TypeInfo/Namespace/Namespace.cpp
					Source/TypeInfo/Namespace/NamespaceFragmentAPI.cpp
					Source/TypeInfo/Namespace/NamespaceFragmentRegistererAPI.cpp

					Source/TypeInfo/Archetypes/ArchetypeAPI.cpp
					Source/TypeInfo/Archetypes/FundamentalArchetypeAPI.cpp
					Source/TypeInfo/Archetypes/EnumAPI.cpp
					Source/TypeInfo/Archetypes/EnumValueAPI.cpp
					Source/TypeInfo/Archetypes/StructAPI.cpp
					Source/TypeInfo/Archetypes/ParentStruct.cpp
					Source/TypeInfo/Archetypes/ArchetypeRegistererAPI.cpp
					Source/TypeInfo/Archetypes/GetArchetypeAPI.cpp

					Source/TypeInfo/Archetypes/Template/ClassTemplateAPI.cpp
					Source/TypeInfo/Archetypes/Template/TemplateParameterAPI.cpp
					Source/TypeInfo/Archetypes/Template/TemplateArgumentAPI.cpp
					Source/TypeInfo/Archetypes/Template/ClassTemplateInstantiationAPI.cpp
					Source/TypeInfo/Archetypes/Template/ClassTemplateInstantiationRegistererAPI.cpp

					Source/TypeInfo/Variables/VariableBaseAPI.cpp
					Source/TypeInfo/Variables/VariableAPI.cpp
					Source/TypeInfo/Variables/FieldBaseAPI.cpp
					Source/TypeInfo/Variables/FieldAPI.cpp
					Source/TypeInfo/Variables/StaticFieldAPI.cpp

					Source/TypeInfo/Functions/FunctionBaseAPI.cpp
					Source/TypeInfo/Functions/FunctionAPI.cpp
					Source/TypeInfo/Functions/MethodBaseAPI.cpp
					Source/TypeInfo/Functions/MethodAPI.cpp
					Source/TypeInfo/Functions/StaticMethodAPI.cpp
					Source/TypeInfo/Functions/FunctionParameterAPI.cpp
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
	target_compile_options(${RefurekuLibraryTarget} PRIVATE -Wall -Wextra -Wpedantic -fno-rtti -fvisibility-ms-compat -fvisibility-inlines-hidden)

	# Use rtti on Property file if specified
	if (GEN_PROPERTY_RTTI)
		set_source_files_properties(Source/TypeInfo/Properties/Property.cpp PROPERTIES COMPILE_FLAGS -frtti)
	endif()

endif()

# Setup language requirements
target_compile_features(${RefurekuLibraryTarget} PUBLIC cxx_std_17)

target_include_directories(${RefurekuLibraryTarget}
							PUBLIC	Include/Public
							PRIVATE Include/Private)

add_subdirectory(Tests)