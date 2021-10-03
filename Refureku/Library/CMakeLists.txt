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
					Source/TypeInfo/TypePart.cpp	#Delete this
					Source/TypeInfo/TypeAPI.cpp
					Source/TypeInfo/Type.cpp		#Delete this
					Source/TypeInfo/EnumValue.cpp	#Delete this
					Source/TypeInfo/DatabaseAPI.cpp
					Source/TypeInfo/Database.cpp	#Delete this

					Source/TypeInfo/Entity/Entity.cpp
					Source/TypeInfo/Entity/EntityHash.cpp
					Source/TypeInfo/Entity/EntityImplementation.cpp		#Delete this
					Source/TypeInfo/Entity/EntityCastAPI.cpp
					Source/TypeInfo/Entity/EntityCast.cpp				#Delete this
					Source/TypeInfo/Entity/DefaultEntityRegistererAPI.cpp
					Source/TypeInfo/Entity/DefaultEntityRegisterer.cpp	#Delete this

					Source/TypeInfo/Namespace/NamespaceAPI.cpp
					Source/TypeInfo/Namespace/Namespace.cpp						#Delete this
					Source/TypeInfo/Namespace/NamespaceFragmentAPI.cpp
					Source/TypeInfo/Namespace/NamespaceFragment.cpp				#Delete this
					Source/TypeInfo/Namespace/NamespaceFragmentRegistererAPI.cpp
					Source/TypeInfo/Namespace/NamespaceFragmentRegisterer.cpp	#Delete this

					Source/TypeInfo/Archetypes/ArchetypeAPI.cpp
					Source/TypeInfo/Archetypes/Archetype.cpp			#Delete this
					Source/TypeInfo/Archetypes/FundamentalArchetypeAPI.cpp
					Source/TypeInfo/Archetypes/FundamentalArchetype.cpp	#Delete this
					Source/TypeInfo/Archetypes/EnumAPI.cpp
					Source/TypeInfo/Archetypes/Enum.cpp					#Delete this
					Source/TypeInfo/Archetypes/EnumValueAPI.cpp
					Source/TypeInfo/Archetypes/StructAPI.cpp
					Source/TypeInfo/Archetypes/Struct.cpp				#Delete this
					Source/TypeInfo/Archetypes/Class.cpp				#Delete this
					Source/TypeInfo/Archetypes/ParentStruct.cpp
					Source/TypeInfo/Archetypes/ArchetypeRegistererAPI.cpp
					Source/TypeInfo/Archetypes/ArchetypeRegisterer.cpp	#Delete this
					Source/TypeInfo/Archetypes/GetArchetypeAPI.cpp
					Source/TypeInfo/Archetypes/GetArchetype.cpp			#Delete this
					Source/TypeInfo/Archetypes/ClassTemplate.cpp
					Source/TypeInfo/Archetypes/TemplateParameter.cpp
					Source/TypeInfo/Archetypes/TemplateArgument.cpp
					Source/TypeInfo/Archetypes/ClassTemplateInstantiation.cpp
					Source/TypeInfo/Archetypes/ClassTemplateInstantiationRegisterer.cpp

					Source/TypeInfo/Variables/VariableBaseAPI.cpp
					Source/TypeInfo/Variables/VariableBase.cpp	#Delete this
					Source/TypeInfo/Variables/VariableAPI.cpp
					Source/TypeInfo/Variables/Variable.cpp		#Delete this
					Source/TypeInfo/Variables/FieldBaseAPI.cpp
					Source/TypeInfo/Variables/FieldBase.cpp		#Delete this
					Source/TypeInfo/Variables/FieldAPI.cpp
					Source/TypeInfo/Variables/Field.cpp			#Delete this
					Source/TypeInfo/Variables/StaticFieldAPI.cpp
					Source/TypeInfo/Variables/StaticField.cpp	#Delete this

					Source/TypeInfo/Functions/FunctionBaseAPI.cpp
					Source/TypeInfo/Functions/FunctionBase.cpp			#Delete this
					Source/TypeInfo/Functions/FunctionAPI.cpp
					Source/TypeInfo/Functions/Function.cpp				#Delete this
					Source/TypeInfo/Functions/MethodBaseAPI.cpp
					Source/TypeInfo/Functions/MethodBase.cpp			#Delete this
					Source/TypeInfo/Functions/MethodAPI.cpp
					Source/TypeInfo/Functions/Method.cpp				#Delete this
					Source/TypeInfo/Functions/StaticMethodAPI.cpp
					Source/TypeInfo/Functions/StaticMethod.cpp			#Delete this
					Source/TypeInfo/Functions/FunctionParameterAPI.cpp
					Source/TypeInfo/Functions/FunctionParameter.cpp		#Delete this
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
							PUBLIC Include/Public
							PUBLIC Include/Private)	#TODO: Switch to PRIVATE once the public API is ready

add_subdirectory(Tests)