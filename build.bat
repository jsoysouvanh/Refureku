@echo off

set "flag="

:: Clang (Debug + Release)
if "%1%" == "clang" set flag=1
if "%1%" == "all" set flag=1

if defined flag rmdir /S /Q "Build\ClangDebug" & rmdir /S /Q "Build/ClangRelease" & cmake -B Build/ClangDebug -DCMAKE_BUILD_TYPE=Debug -G "Ninja" & cmake --build Build/ClangDebug --config Debug --target RefurekuGenerator Refureku & cmake -B Build/ClangRelease -DCMAKE_BUILD_TYPE=Release -G "Ninja" & cmake --build Build/ClangRelease --config Release --target RefurekuGenerator Refureku

:: Reset flag
set "flag="

:: MSVC 2017 (Debug + Release)
if "%1%" == "msvc2017" set flag=1
if "%1%" == "msvc" set flag=1
if "%1%" == "all" set flag=1

if defined flag rmdir /S /Q "Build\MSVC2017Debug" & rmdir /S /Q "Build/MSVC2017Release" & cmake -B Build/MSVC2017Debug -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 15 2017" -A x64 & cmake --build Build/MSVC2017Debug --config Debug --target RefurekuGenerator Refureku & cmake -B Build/MSVC2017Release -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 15 2017" -A x64 & cmake --build Build/MSVC2017Release --config Release --target RefurekuGenerator Refureku

:: Reset flag
set "flag="

:: MSVC 2019 (Debug + Release)
if "%1%" == "msvc2019" set flag=1
if "%1%" == "msvc" set flag=1
if "%1%" == "all" set flag=1

if defined flag rmdir /S /Q "Build\MSVC2019Debug" & rmdir /S /Q "Build/MSVC2019Release" cmake -B Build/MSVC2019Debug -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 16 2019" -A x64 & cmake --build Build/MSVC2019Debug --config Debug --target RefurekuGenerator Refureku & cmake -B Build/MSVC2019Release -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 16 2019" -A x64 & cmake --build Build/MSVC2019Release --config Release --target RefurekuGenerator Refureku