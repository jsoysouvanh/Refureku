cmake_minimum_required(VERSION 3.13.5)

project(KodgenTests)

set(ThreadingTestsTarget ThreadingTests)
add_executable(${ThreadingTestsTarget} Threading/main.cpp)

# Link to kodgen
target_link_libraries(${ThreadingTestsTarget} PRIVATE ${KodgenTargetLibrary})

add_test(NAME ${ThreadingTestsTarget} COMMAND ${ThreadingTestsTarget})