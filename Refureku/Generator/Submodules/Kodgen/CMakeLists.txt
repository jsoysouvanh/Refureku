cmake_minimum_required(VERSION 3.13.5)

project(KodgenLibrary)

# Setup output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY Lib/${CMAKE_BUILD_TYPE}/${CMAKE_CXX_COMPILER_ARCHITECTURE_ID})	# .dll / .so
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY Lib/${CMAKE_BUILD_TYPE}/${CMAKE_CXX_COMPILER_ARCHITECTURE_ID})	# .lib / .a
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY Bin/${CMAKE_BUILD_TYPE}/${CMAKE_CXX_COMPILER_ARCHITECTURE_ID})	# .exe

# Setup warning level
if (MSVC)
	add_compile_options(/W4)
else()	# Clang or GCC
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

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
target_link_directories(${KodgenTargetLibrary} PUBLIC Libraries/x64/Static)

# Link to required libraries (mostly libclang dependencies)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(${KodgenTargetLibrary}
						INTERFACE
							$<$<CXX_COMPILER_ID:Clang>:c++>
							$<$<CXX_COMPILER_ID:Clang>:c++abi>
							$<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:${CMAKE_CXX_COMPILER_VERSION},9.0>>:stdc++fs>	#filesystem	pre GCC-9
							clang
							clangAST
							clangBasic
							clangDriver
							clangFrontend
							clangIndex
							clangLex
							clangSema
							clangSerialization
							clangTooling
							clangARCMigrate
							$<$<PLATFORM_ID:Linux>:dl>
							LLVMAArch64CodeGen
							LLVMAArch64AsmParser
							LLVMAArch64Desc
							LLVMAArch64Disassembler
							LLVMAArch64Info
							LLVMAArch64Utils
							LLVMAMDGPUCodeGen
							LLVMAMDGPUAsmParser
							LLVMAMDGPUDesc
							LLVMAMDGPUDisassembler
							LLVMAMDGPUInfo
							LLVMAMDGPUUtils
							LLVMARMCodeGen
							LLVMARMAsmParser
							LLVMARMDesc
							LLVMARMDisassembler
							LLVMARMInfo
							LLVMARMUtils
							LLVMBPFCodeGen
							LLVMBPFAsmParser
							LLVMBPFDesc
							LLVMBPFDisassembler
							LLVMBPFInfo
							LLVMHexagonCodeGen
							LLVMHexagonAsmParser
							LLVMHexagonDesc
							LLVMHexagonDisassembler
							LLVMHexagonInfo
							LLVMLanaiCodeGen
							LLVMLanaiAsmParser
							LLVMLanaiDesc
							LLVMLanaiDisassembler
							LLVMLanaiInfo
							LLVMMipsCodeGen
							LLVMMipsAsmParser
							LLVMMipsDesc
							LLVMMipsDisassembler
							LLVMMipsInfo
							LLVMMSP430CodeGen
							LLVMMSP430AsmParser
							LLVMMSP430Desc
							LLVMMSP430Disassembler
							LLVMMSP430Info
							LLVMNVPTXCodeGen
							LLVMNVPTXDesc
							LLVMNVPTXInfo
							LLVMPowerPCCodeGen
							LLVMPowerPCAsmParser
							LLVMPowerPCDesc
							LLVMPowerPCDisassembler
							LLVMPowerPCInfo
							LLVMRISCVCodeGen
							LLVMRISCVAsmParser
							LLVMRISCVDesc
							LLVMRISCVDisassembler
							LLVMRISCVInfo
							LLVMRISCVUtils
							LLVMSparcCodeGen
							LLVMSparcAsmParser
							LLVMSparcDesc
							LLVMSparcDisassembler
							LLVMSparcInfo
							LLVMSystemZCodeGen
							LLVMSystemZAsmParser
							LLVMSystemZDesc
							LLVMSystemZDisassembler
							LLVMSystemZInfo
							LLVMWebAssemblyCodeGen
							LLVMWebAssemblyAsmParser
							LLVMWebAssemblyDesc
							LLVMWebAssemblyDisassembler
							LLVMWebAssemblyInfo
							LLVMX86CodeGen
							LLVMX86AsmParser
							LLVMX86Desc
							LLVMX86Disassembler
							LLVMX86Info
							LLVMX86Utils
							LLVMXCoreCodeGen
							LLVMXCoreDesc
							LLVMXCoreDisassembler
							LLVMXCoreInfo
							LLVMCore
							LLVMSupport
							clangFormat
							clangToolingInclusions
							clangToolingCore
							clangFrontend
							clangDriver
							LLVMOption
							clangParse
							clangSerialization
							clangSema
							clangEdit
							clangRewrite
							clangAnalysis
							clangASTMatchers
							clangAST
							clangLex
							clangBasic
							LLVMAArch64Desc
							LLVMAArch64Info
							LLVMAArch64Utils
							LLVMMIRParser
							LLVMAMDGPUDesc
							LLVMAMDGPUInfo
							LLVMAMDGPUUtils
							LLVMARMDesc
							LLVMARMInfo
							LLVMARMUtils
							LLVMHexagonDesc
							LLVMHexagonInfo
							LLVMLanaiDesc
							LLVMLanaiInfo
							LLVMipo
							LLVMVectorize
							LLVMIRReader
							LLVMAsmParser
							LLVMInstrumentation
							LLVMLinker
							LLVMSystemZDesc
							LLVMSystemZInfo
							LLVMWebAssemblyDesc
							LLVMWebAssemblyInfo
							LLVMGlobalISel
							LLVMAsmPrinter
							LLVMDebugInfoDWARF
							LLVMSelectionDAG
							LLVMCodeGen
							LLVMScalarOpts
							LLVMAggressiveInstCombine
							LLVMInstCombine
							LLVMBitWriter
							LLVMTarget
							LLVMTransformUtils
							LLVMAnalysis
							LLVMProfileData
							LLVMObject
							LLVMBitReader
							LLVMCore
							LLVMRemarks
							LLVMBitstreamReader
							LLVMMCParser
							LLVMMCDisassembler
							LLVMMC
							LLVMBinaryFormat
							LLVMDebugInfoCodeView
							LLVMDebugInfoMSF
							LLVMSupport
							z
							$<$<PLATFORM_ID:Linux>:dl>
							Threads::Threads
							LLVMDemangle
)

add_subdirectory(Tests)
add_subdirectory(Examples)