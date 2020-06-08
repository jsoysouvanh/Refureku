cmake_minimum_required(VERSION 3.13.5)

project(KodgenLibrary)

# Setup output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)	# .dll / .so
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)	# .lib / .a
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)	# .exe

set(KodgenTargetLibrary Kodgen)

add_library(${KodgenTargetLibrary}
				STATIC
					Source/Properties/SimplePropertyRule.cpp
					Source/Properties/ComplexPropertyRule.cpp
					Source/Properties/ComplexProperty.cpp
					Source/Properties/PropertyRules.cpp
					Source/Properties/PropertyGroup.cpp
					Source/Properties/PropertyParsingSettings.cpp
	
					Source/InfoStructures/EntityInfo.cpp
					Source/InfoStructures/FieldInfo.cpp
					Source/InfoStructures/MethodInfo.cpp
					Source/InfoStructures/StructClassInfo.cpp
					Source/InfoStructures/EnumInfo.cpp
					Source/InfoStructures/EnumValueInfo.cpp
					Source/InfoStructures/ParsingInfo.cpp
					Source/InfoStructures/TypeInfo.cpp
	
					Source/Parsing/EParsingError.cpp
					Source/Parsing/ParsingError.cpp
					Source/Parsing/PropertyParser.cpp
					Source/Parsing/EntityParser.cpp
					Source/Parsing/ClassParser.cpp
					Source/Parsing/FieldParser.cpp
					Source/Parsing/MethodParser.cpp
					Source/Parsing/EnumParser.cpp
					Source/Parsing/EnumValueParser.cpp
					Source/Parsing/FileParser.cpp
	
					Source/Misc/EAccessSpecifier.cpp
					Source/Misc/Helpers.cpp
					Source/Misc/DefaultLogger.cpp
	
					Source/CodeGen/FileGenerator.cpp
					Source/CodeGen/EFileGenerationError.cpp
					Source/CodeGen/FileGenerationError.cpp
					Source/CodeGen/GeneratedFile.cpp
			)

# Setup warning level
if (MSVC)
	string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")	# Remove the default flag /W3
	target_compile_options(${KodgenTargetLibrary} PUBLIC /W4)
else()	# Clang or GCC
	target_compile_options(${KodgenTargetLibrary} PUBLIC -Wall -Wextra -Wpedantic)
endif()

# Setup compilation definitions
if (KODGEN_DEV)
	target_compile_definitions(${KodgenTargetLibrary} PRIVATE KODGEN_DEV=1)
endif()

# Setup language requirements
target_compile_features(${KodgenTargetLibrary} PUBLIC cxx_std_17)

# Setup include directories
target_include_directories(${KodgenTargetLibrary}
							PUBLIC
								Include
								Libraries/Include)

# Setup link directories
target_link_directories(${KodgenTargetLibrary}
							PUBLIC
								Libraries/x64/Static
								Libraries/x64/Shared)

# Link to required libraries
target_link_libraries(${KodgenTargetLibrary}
						INTERFACE
							$<$<AND:$<CXX_COMPILER_ID:Clang>,$<VERSION_LESS:${CMAKE_CXX_COMPILER_VERSION},9.0>>:stdc++fs>	#filesystem	pre Clang-9
							$<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:${CMAKE_CXX_COMPILER_VERSION},9.0>>:stdc++fs>	#filesystem	pre GCC-9
							clang
)

# Copy libclang shared library to the bin folder
if (WIN32)
	add_custom_command(	TARGET ${KodgenTargetLibrary} POST_BUILD
						COMMAND ${CMAKE_COMMAND} -E copy
						${PROJECT_SOURCE_DIR}/Libraries/x64/Shared/libclang.dll
						${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libclang.dll)
endif()

add_subdirectory(Tests)
add_subdirectory(Examples)