# Refureku

[![Latest Release](https://badge.fury.io/gh/jsoysouvanh%2FRefureku.svg)](https://github.com/jsoysouvanh/Refureku/releases/latest)
[![Linux](https://github.com/jsoysouvanh/Refureku/actions/workflows/run_tests_linux.yml/badge.svg?branch=master)](https://github.com/jsoysouvanh/Refureku/actions/workflows/run_tests_linux.yml)
[![Windows](https://github.com/jsoysouvanh/Refureku/actions/workflows/run_tests_windows.yml/badge.svg?branch=master)](https://github.com/jsoysouvanh/Refureku/actions/workflows/run_tests_windows.yml)
[![MacOS](https://github.com/jsoysouvanh/Refureku/actions/workflows/run_tests_macos.yml/badge.svg?branch=master)](https://github.com/jsoysouvanh/Refureku/actions/workflows/run_tests_macos.yml)


**Check [the Wiki](https://github.com/jsoysouvanh/Refureku/wiki) for more documentation and use examples!**

Refureku is a powerful C++17 RTTI free runtime reflection dynamic library based on [Kodgen](https://github.com/jsoysouvanh/Kodgen).
It allows to retrieve information on namespaces, structs/classes, fields, methods, non-member variables, non-member functions, enums and enum values at runtime.

## Index
- [Features](#features)
- [Getting started](#getting-started)
  - [Requirements](#requirements)
  - [Library integration](#library-integration)
  - [Parser/Generator integration](#parsergenerator-integration)
  - [Possible issues](#possible-issues)
- [Cross-platform compatibility](#cross-platform-compatibility)
- [Planned features](#planned-features)
- [Known issues](#known-issues)
- [License](#license)

## Features
- Easy to integrate in a software like a game engine
- Reflect namespaces, structs, classes, methods, fields, variables, functions, enums and enum values
- Support structs/classes with or without inheritance (multiple inheritance supported)
- Support template structs/classes
- Can get an entity by name, predicate, ID, with additional filtering parameters
- Function/Method call with any arguments and any return type (public, protected, private, virtual, override)
- Variable/Field get/set any data of any type (public, protected, private)
- Know at runtime if an instance of a reflected struct/class is the base or a subclass of another reflected struct/class
- Powerful property system allowing to attach metadata on any entity and generate custom code
- Reflection metadata is regenerated only when a file has changed
- Can instantiate any objects just from an archetype (which is obtainable by name or id), with arbitrary parameters

## Getting started
**Pre-built binaries for Windows x64 are available [here](https://github.com/jsoysouvanh/Refureku/releases). If you want to use those, you can skip to step 3 (this is true for the [Library Integration part](#library-integration) as well as the [Parser/Generator Integration part](#parsergenerator-integration).**

**Refureku integration examples are available [here](https://github.com/jsoysouvanh/RefurekuIntegration).**

### Requirements:
- CMake 3.15.0+ (if you build the library from source).
- A compatible compiler: MSVC Platform Toolset v141+ / GCC8.0.0+ / Clang 7.0.0+.

### Library integration
1. Pull the repository
2. Compile the library and the generator following these steps:
	- At the root of the Refureku folder, open a terminal
		- cmake -B Build/Release -DCMAKE_BUILD_TYPE=Release -G "\<Generator\>"
			> Most common generators include:
			> - Visual Studio 15 2017 -> cmake -B Build/Release -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 15 2017" -A x64
			>**Note:** If you use Visual Studio generator, you must explicitely specify the target architecture using -A x64
			> - Unix Makefiles
			> - Ninja -> cmake -B Build/Release -DCMAKE_BUILD_TYPE=Release -G "Ninja"
			> - Type cmake -G for more information
		- cmake --build Build/Release --config Release --target **RefurekuGenerator Refureku**
	- You will find the generator binaries in Build/Release/Bin/ and the library in Build/[Debug|Release]/Lib/
		> **Note:** On multiple configuration generators such as Visual Studio or XCode, an additional Debug/Release folder is generated.

3.  Add necessary header directories to your project settings:
    - From binaries: /Include/
    - From source: /Refureku/Library/Include/Public/

4.  Add library directories to your projet settings:
    - From binaries: /Lib/
    - From source: /Build/[Debug|Release]/Lib/

5.  Link against:
    - From binaries: Refureku.lib

6. Update RefurekuSettings.toml located in /Build/Release/Bin/, or /Bin/ if you downloaded the binaries. You must at least specify:
	- [FileParsingSettings] **projectIncludeDirectories** and **compilerExeName** as documented [here](https://github.com/jsoysouvanh/Kodgen/wiki/FileParser-settings#load-settings-from-a-toml-file).
		> Paths to your project's additional include directories are **absolutely necessary** to make sure the parser can find all included files. As you added Refureku include directory at step 3, you must add it to the list as well.
	- [CodeGenUnitSettings] **outputDirectory** as documented [here](https://github.com/jsoysouvanh/Kodgen/wiki/CodeGenUnit-settings#load-settings-from-a-toml-file).
	- [CodeGenManagerSettings] **toProcessDirectories** as documented [here](https://github.com/jsoysouvanh/Kodgen/wiki/CodeGenManager-settings#load-settings-from-a-toml-file).
	- **If the specified outputDirectory is in a parsed directory**, you should ignore it too by adding it to ignoredDirectories.
	
7. Make the RefurekuGenerator run just before your project's compilation:
	- With CMake:
	```cmake
	# Run generator before compiling our own program
	add_custom_target(RunGenerator
				WORKING_DIRECTORY "Your/Working/Directory"
				COMMAND "Path/To/The/RefurekuGenerator" "Path/To/RefurekuSettings.toml")
	add_dependencies(YourExecutable RunGenerator)
	```
	- With Visual Studio:
		> In Project properties > Build Events > Pre-Build Event, add the command Path\To\Executable\RefurekuGenerator.exe Path\To\RefurekuSettings.toml

8. Make sure you compile your project in C++17 or later.
9. Compile your project: you should see build logs from the RefurekuGenerator with a list of parsed files, or error logs if something went wrong. If you encounter errors, see the [Possible issues section](#possible-issues). If it doesn't help, don't hesitate to [open a new issue](https://github.com/jsoysouvanh/Refureku/issues).

### Parser/Generator integration
1. Pull the repository
2. Compile the generator library following these steps:
	- At the root of the Refureku folder, open a terminal
		- cmake -B Build/Release -DCMAKE_BUILD_TYPE=Release -G "\<Generator\>"
			> Most common generators include:
			> - Visual Studio 15 2017 -> cmake -B Build/Release -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 15 2017" -A x64
				>**Note:** If you use Visual Studio generator, you must explicitely specify the target architecture using -A x64
			> - Unix Makefiles
			> - Ninja -> cmake -B Build/Release -DCMAKE_BUILD_TYPE=Release -G "Ninja"
			> - Type cmake -G for more information
		- cmake --build Build/Release --config Release --target **RefurekuGeneratorLib**
	- If you're compiling your project in debug mode, you will also probably need the debug version too:
		- cmake -B Build/Debug -DCMAKE_BUILD_TYPE=Debug -G "\<Generator\>"
		- cmake --build Build/Debug --config Debug --target **RefurekuGeneratorLib**
	- You will find the built libraries in Build/[Debug|Release]/Lib/
		> **Note:** On multiple configuration generators such as Visual Studio or XCode, an additional Debug/Release folder is generated.

3.  Add necessary header directories to your project settings:
    - From binaries: /Include/
    - From source:
	    - /Refureku/Generator/Submodules/Kodgen/Kodgen/Include/
	    - /Refureku/Generator/Submodules/Kodgen/Kodgen/ThirdParty/Include/
	    - /Refureku/Generator/Include/

4.  Add library directories to your projet settings:
    - From binaries:
	    - /Lib/
    - From source:
	    - /Refureku/Generator/Submodules/Kodgen/Kodgen/ThirdParty/x64/Static/
	    - /Build/[Debug|Release]/Lib/
    > Make sure /Build/Debug/Lib/ is only set in debug mode, and /Build/Release/Lib/ only in release mode

5.  Link against:
    - From binaries:
	    - clang.lib
	    - KodgenDebug.lib in debug only, KodgenRelease.lib in release only
	    - RefurekuGeneratorLibDebug.lib in debug only, RefurekuGeneratorLibRelease.lib in release only
    - From source:
	    - clang.lib
	    - Kodgen.lib
	    - RefurekuGeneratorLib.lib

6.  Setup your project C++ compilation version to C++17 or later.
7.  Compile!
8.  Before running your program, make sure that the libclang dynamic library is located next to your executable. You should find it at /Refureku/Generator/Submodules/Kodgen/Kodgen/ThirdParty/x64/Shared/, or /Bin/ from the binaries.

You should be able to run the following snippet:

```cpp
#include <Kodgen/Misc/DefaultLogger.h>
#include <Kodgen/CodeGen/Macro/MacroCodeGenUnit.h>

#include <RefurekuGenerator/Parsing/FileParser.h>
#include <RefurekuGenerator/CodeGen/CodeGenManager.h>
#include <RefurekuGenerator/CodeGen/MacroCodeGenUnitSettings.h>
#include <RefurekuGenerator/CodeGen/ReflectionCodeGenModule.h>

int main()
{
    kodgen::DefaultLogger logger;

	rfk::FileParser fileParser;
	fileParser.logger = &logger;

	rfk::CodeGenManager codeGenMgr;
	codeGenMgr.logger = &logger;

	rfk::MacroCodeGenUnitSettings codeGenUnitSettings;
	kodgen::MacroCodeGenUnit codeGenUnit;
	codeGenUnit.logger = &logger;
	codeGenUnit.setSettings(codeGenUnitSettings);
	
	rfk::ReflectionCodeGenModule reflectionCodeGenModule;	
	codeGenUnit.addModule(reflectionCodeGenModule);

	//TODO: Load all settings here.
	//Either load settings from a settings file, or set them by calling the appropriate methods.
	//Refer to Kodgen documentation for more information.
    
	//Parse & generate code
	codeGenMgr.run(fileParser, codeGenUnit);

    return 0;
}
```

### Possible issues
#### Issue 1
- If you compile your program in debug mode, your compiler might complain about library / debug level mismatchs. In that case, make sure to compile the Refureku generator library both in Debug and Release, and link against the debug version of the library when compiling your program in debug mode.

## Cross-platform compatibility
This library has been tested and is stable on the following configurations:
- Microsoft Windows Server | MSVC 19.29.30133.0
- Linux 20.04 | Clang 7.0.1, Clang 8.0.1, Clang 9.0.1, Clang 10.0.0, Clang 11.0.0
- Linux 20.04 | GNU 8.4.0, GNU 9.3.0, GNU 10.3.0, GNU 11.1.0
- Mac OS X 10.15.7 | AppleClang 12.0.0

## Planned features
- Reflect class constructors to use them as instantiators

## Known issues
- Issues when reflecting template template classes with MSVC because of [this issue](https://developercommunity.visualstudio.com/t/Type-template-parameter-can-erroneously/1548997).

## License
MIT License

Copyright (c) 2020-2021 Julien SOYSOUVANH

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
