cmake_minimum_required(VERSION 3.13.5)

project(RefurekuGenerator)

# Build dependencies
add_subdirectory(Submodules/Kodgen)

# Add Refureku generator executable
set(RefurekuGeneratorTarget RefurekuGenerator_${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}_${CMAKE_BUILD_TYPE})
add_executable(${RefurekuGeneratorTarget}
				Source/FileParser.cpp
				Source/GeneratedEntityCodeTemplate.cpp
				Source/GeneratedClassCodeTemplate.cpp
				Source/GeneratedEnumCodeTemplate.cpp
				Source/FileGenerator.cpp

				Source/main.cpp
				)

# Setup language requirements - I don't understand why it wasn't propagated by the KodgenLibrary target.
target_compile_features(${RefurekuGeneratorTarget} PUBLIC cxx_std_17)

target_include_directories(${RefurekuGeneratorTarget} PRIVATE Include)

# Link to Kodgen library
set(KodgenLibrary Kodgen_${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}_${CMAKE_BUILD_TYPE})

target_link_libraries(${RefurekuGeneratorTarget} PRIVATE ${KodgenLibrary})