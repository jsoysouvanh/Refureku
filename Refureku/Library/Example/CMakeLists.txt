cmake_minimum_required(VERSION 3.13.5)

project(RefurekuUsageExample)

###########################################
#		Configure the demo project
###########################################

set(RefurekuDemoTarget RefurekuDemo)
add_executable(${RefurekuDemoTarget}
					Source/ExampleClass.cpp

					Source/main.cpp
				)

# Link to RefurekuLibrary
target_link_libraries(${RefurekuDemoTarget} PRIVATE ${RefurekuLibraryTarget})

# Create the command to run RefurekuGenerator
set(RefurekuGeneratorPath ${CMAKE_BINARY_DIR}/Refureku/Generator/Bin/${CMAKE_BUILD_TYPE}/${CMAKE_CXX_COMPILER_ARCHITECTURE_ID})
set(RefurekuGeneratorExeName RefurekuGenerator)
set(RunGeneratorTarget RunRefurekuGenerator)

# Two ways to proceed here (choose either one):

# 1st way: we run the generator from our project source directory (so we specify the absolute path to the generator executable)
# In that case, we need to specify the full path to the generator executable,
# but we don't need to pass it any arguments as it processes the working directory by default
add_custom_target(${RunGeneratorTarget}
                    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                    COMMAND ${RefurekuGeneratorPath}/${RefurekuGeneratorExeName})

#2nd way: we run the generator from its own parent directory (so we can execute it without specifying any path)
# In that case, we need to pass our project source directory path to the generator (first argument)
#add_custom_target(${RunGeneratorTarget}
#                    WORKING_DIRECTORY ${RefurekuGeneratorPath}
#                    COMMAND ${RefurekuGeneratorExeName} ${PROJECT_SOURCE_DIR})

# Run the RefurekuGenerator BEFORE building the project to refresh generated files
add_dependencies(${RefurekuDemoTarget} ${RunGeneratorTarget})

# Add include directories
target_include_directories(${RefurekuDemoTarget} PRIVATE Include)