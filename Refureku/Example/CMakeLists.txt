cmake_minimum_required(VERSION 3.13.5)

project(RefurekuUsageExample)

###########################################
# Configure the demo project
###########################################

set(RefurekuDemoTarget RefurekuDemo)
add_executable(${RefurekuDemoTarget}
					Source/main.cpp
				)

set(RunGeneratorTarget RunRefurekuGenerator)
add_custom_target(${RunGeneratorTarget}
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Refureku/Bin/${CMAKE_BUILD_TYPE}/${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}
                    COMMAND ./${RefurekuTarget} ${PROJECT_SOURCE_DIR})

# Run the Refureku BEFORE building the project to refresh generated files
add_dependencies(${RefurekuDemoTarget} ${RunGeneratorTarget})

# Build Refureku BEFORE running it...
add_dependencies(${RunGeneratorTarget} ${RefurekuTarget})

# Add include directories
target_include_directories(${RefurekuDemoTarget} PRIVATE Include)