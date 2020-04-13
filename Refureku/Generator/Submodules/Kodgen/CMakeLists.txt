cmake_minimum_required(VERSION 3.13.5)

project(KodgenLibrary)

# Setup output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY Lib/${CMAKE_BUILD_TYPE}/${CMAKE_CXX_COMPILER_ARCHITECTURE_ID})	# .dll / .so
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY Lib/${CMAKE_BUILD_TYPE}/${CMAKE_CXX_COMPILER_ARCHITECTURE_ID})	# .lib / .a
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY Bin/${CMAKE_BUILD_TYPE}/${CMAKE_CXX_COMPILER_ARCHITECTURE_ID})	# .exe

set(KodgenTargetLibrary Kodgen)

add_library(${KodgenTargetLibrary}
				STATIC
					Source/Properties/SimplePropertyRule.cpp
					Source/Properties/ComplexPropertyRule.cpp
					Source/Properties/ComplexProperty.cpp
					Source/Properties/PropertyRules.cpp
					Source/Properties/PropertyGroup.cpp
	
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
if (DEV)
	target_compile_definitions(${KodgenTargetLibrary} PRIVATE KODGEN_DEV=1)
endif()

# Setup compilation options
target_compile_options(${KodgenTargetLibrary} PUBLIC $<$<CXX_COMPILER_ID:Clang>:-stdlib=libc++>)

# Setup language requirements
target_compile_features(${KodgenTargetLibrary} PUBLIC cxx_std_17)

# Setup include directories
target_include_directories(${KodgenTargetLibrary}
							PUBLIC
								Include
								Libraries/Include)

# Setup link directories
target_link_directories(${KodgenTargetLibrary} PUBLIC
							Libraries/x64/Static
							Libraries/x64/Shared)

# Link to required libraries (mostly libclang dependencies)
target_link_libraries(${KodgenTargetLibrary}
						INTERFACE
							$<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<VERSION_LESS:${CMAKE_CXX_COMPILER_VERSION},9.0>>:stdc++fs>	#filesystem	pre Clang-9/GCC-9
							$<$<CXX_COMPILER_ID:Clang>:c++ c++abi>
							clang
)

add_subdirectory(Tests)
add_subdirectory(Examples)