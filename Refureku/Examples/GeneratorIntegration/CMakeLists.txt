cmake_minimum_required(VERSION 3.13.5)

project(RefurekuGeneratorIntegrationWithCMake)

set(Target RefurekuGeneratorIntegrationWithCMake)
add_executable(${Target} Source/main.cpp)

# Compile in c++17
target_compile_features(${Target} PUBLIC cxx_std_17)

# Add Include directories
target_include_directories(${Target}
							PRIVATE
								../../Generator/Submodules/Kodgen/Libraries/Include	# Kodgen dependencies
								../../Generator/Submodules/Kodgen/Include			# Kodgen headers
								../../Generator/Include)							# Refureku generator headers

# Link against dependant libraries
target_link_directories(${Target}
							PRIVATE
								../ThirdParty/Lib										# Kodgen, RefurekuGeneratorLib
								../../Generator/Submodules/Kodgen/Libraries/x64/Static)	# clang.lib

target_link_libraries(${Target}
						PRIVATE
							$<IF:$<CONFIG:Debug>,KodgenDebug,KodgenRelease>								# Kodgen
							$<IF:$<CONFIG:Debug>,RefurekuGeneratorLibDebug,RefurekuGeneratorLibRelease>	# RefurekuGenerator
							clang)
