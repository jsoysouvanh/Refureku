cmake_minimum_required(VERSION 3.13.5)

# Build dependencies
add_subdirectory(Submodules/Kodgen Ici)

set(RefurekuTarget Refureku_${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}_${CMAKE_BUILD_TYPE})

add_executable(${RefurekuTarget} 
				Source/main.cpp
				)

# Link to Kodgen library
target_link_libraries(${RefurekuTarget} PUBLIC Kodgen_${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}_${CMAKE_BUILD_TYPE})