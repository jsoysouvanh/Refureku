cmake_minimum_required(VERSION 3.13.5)

set(PropertyRulesTestsTarget Kodgen_PropertyRulesTests)
set(ParsingTestsTarget Kodgen_ParsingTests)
set(FileGeneratorTestsTarget Kodgen_FileGeneratorTests)

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