cmake_minimum_required(VERSION 3.13.5)

set(PropertyRulesTestsTarget Kodgen_${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}_${CMAKE_BUILD_TYPE}_PropertyRulesTests)
set(ParsingTestsTarget Kodgen_${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}_${CMAKE_BUILD_TYPE}_ParsingTests)
set(FileGeneratorTestsTarget Kodgen_${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}_${CMAKE_BUILD_TYPE}_FileGeneratorTests)

add_executable(${PropertyRulesTestsTarget} PropertyRulesTests.cpp)
add_executable(${ParsingTestsTarget} ParsingTests.cpp)
add_executable(${FileGeneratorTestsTarget} FileGeneratorTests.cpp)

# Setup language requirements
set_target_properties(${PropertyRulesTestsTarget} ${ParsingTestsTarget} ${FileGeneratorTestsTarget}
						PROPERTIES
						CXX_STANDARD 17
						CXX_STANDARD_REQUIRED ON
						CXX_EXTENSIONS OFF)

# Link to Kodgen library to test it
target_link_libraries(${PropertyRulesTestsTarget} PRIVATE ${KodgenTargetLibrary})
target_link_libraries(${ParsingTestsTarget} PRIVATE ${KodgenTargetLibrary})
target_link_libraries(${FileGeneratorTestsTarget} PRIVATE ${KodgenTargetLibrary})

add_dependencies(${PropertyRulesTestsTarget} ${KodgenTargetLibrary})
add_dependencies(${ParsingTestsTarget} ${KodgenTargetLibrary})
add_dependencies(${FileGeneratorTestsTarget} ${KodgenTargetLibrary})

add_test(NAME ${PropertyRulesTestsTarget} COMMAND ${PropertyRulesTestsTarget})
add_test(NAME ${ParsingTestsTarget} COMMAND ${ParsingTestsTarget})
add_test(NAME ${FileGeneratorTestsTarget} COMMAND ${FileGeneratorTestsTarget})