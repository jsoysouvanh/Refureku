cmake_minimum_required(VERSION 3.13.5)

project(LibraryGenerator)

set(LibraryGeneratorTarget LibraryGenerator)
add_executable(${LibraryGeneratorTarget} main.cpp)

target_link_libraries(${LibraryGeneratorTarget} PRIVATE RefurekuGeneratorLib)