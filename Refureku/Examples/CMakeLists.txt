cmake_minimum_required(VERSION 3.13.5)

project(RefurekuIntegrationWithCMake)

set(Target IntegrationWithCMake)
add_executable(${Target} Source/main.cpp)

# Compile in c++17
target_compile_features(${Target} PUBLIC cxx_std_17)

# Add Include directories
target_include_directories(${Target}
							PRIVATE
								../Library/Include	# Refureku Include dir
								Include)			# Our project Include dir

# Link against Refureku library
target_link_directories(${Target} PRIVATE ThirdParty/Libs)
target_link_libraries(${Target} PRIVATE $<IF:$<CONFIG:Debug>,RefurekuDebug,RefurekuRelease>)

# Create the command to run RefurekuGenerator
set(RunRefurekuGenerator RunRefurekuGenerator)

add_custom_target(${RunRefurekuGenerator}
					WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}		# This is CMakeLists.txt location, which is Refureku/Examples
					COMMAND ThirdParty/Exe/RefurekuGenerator)	# Might need to add .exe

# Run the RefurekuGenerator BEFORE building the project to refresh generated files
add_dependencies(${Target} ${RunRefurekuGenerator})