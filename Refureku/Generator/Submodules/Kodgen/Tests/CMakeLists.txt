cmake_minimum_required(VERSION 3.13.5)

set(PropertyRulesTestsTarget Kodgen_PropertyRulesTests)

add_executable(${PropertyRulesTestsTarget} PropertyRulesTests.cpp)

# Setup language requirements
set_target_properties(${PropertyRulesTestsTarget} ${ParsingTestsTarget} ${FileGeneratorTestsTarget}
						PROPERTIES
						CXX_STANDARD 17
						CXX_STANDARD_REQUIRED ON
						CXX_EXTENSIONS OFF)

# Link to Kodgen library to test it
target_link_libraries(${PropertyRulesTestsTarget} PRIVATE ${KodgenTargetLibrary})

add_dependencies(${PropertyRulesTestsTarget} ${KodgenTargetLibrary})

add_test(NAME ${PropertyRulesTestsTarget} COMMAND ${PropertyRulesTestsTarget})