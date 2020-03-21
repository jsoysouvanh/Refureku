cmake_minimum_required(VERSION 3.13.5)

# Build dependencies
add_subdirectory(Submodules/Kodgen)

# Setup output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY Lib/${CMAKE_BUILD_TYPE}/${CMAKE_CXX_COMPILER_ARCHITECTURE_ID})	# .dll / .so
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY Lib/${CMAKE_BUILD_TYPE}/${CMAKE_CXX_COMPILER_ARCHITECTURE_ID})	# .lib / .a
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY Bin/${CMAKE_BUILD_TYPE}/${CMAKE_CXX_COMPILER_ARCHITECTURE_ID})	# .exe

# Add Refureku executable
set(RefurekuTarget Refureku_${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}_${CMAKE_BUILD_TYPE})
add_executable(${RefurekuTarget}
				Source/FileParser.cpp
				Source/GeneratedCodeTemplate.cpp

				Source/main.cpp
				)

# Setup language requirements - I don't understand why it wasn't propagated by the KodgenLibrary target.
target_compile_features(${RefurekuTarget} PUBLIC cxx_std_17)

target_include_directories(${RefurekuTarget} PRIVATE Include)

# Link to Kodgen library
set(KodgenLibrary Kodgen_${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}_${CMAKE_BUILD_TYPE})

target_link_libraries(${RefurekuTarget} PRIVATE ${KodgenLibrary})