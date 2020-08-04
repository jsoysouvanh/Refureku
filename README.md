# Refureku

[![Latest Release](https://badge.fury.io/gh/jsoysouvanh%2FRefureku.svg)](https://github.com/jsoysouvanh/Refureku/releases/latest)
[![Build Status](https://travis-ci.com/jsoysouvanh/Refureku.svg?branch=master)](https://travis-ci.com/jsoysouvanh/Refureku)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/ba0bf8ff67cf47c498409aef31b88700)](https://www.codacy.com/manual/jsoysouvanh/Refureku?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=jsoysouvanh/Refureku&amp;utm_campaign=Badge_Grade)

Refureku is a powerful C++17 runtime reflection library based on [Kodgen](https://github.com/jsoysouvanh/Kodgen).
It allows you to retrieve information on namespaces, structs/classes, fields, methods, enums and enum values at runtime.

It is separated into 2 distinct parts:
- The metadata parser and generator, which parses C++ source code and generates metadata that will be injected back into source code using macros. This tool can either be built as a standalone executable or embeded in a program (for example a game engine) depending on your needs. Last but not least, it is highly customizable (see [Customization](#customization)).
- The actual library which contains the framework classes to access and manipulate reflected data at runtime.

Here is a non-exhaustive list of Refureku library features:
- Easy to integrate in a software like a game engine
- Reflect namespaces, structs, classes, enums, member methods (static or not) and member fields (static or not)
- Support structs/classes with or without inheritance (multiple inheritance supported)
- Can look for a struct/class, enum, field or method by name, with additional filtering parameters
- Method call with any arguments and any return type (public, protected, private, virtual, override)
- Field get/set any data of any type (public, protected, private)
- Know at runtime if an instance of a reflected struct/class inherits or is the base of another reflected struct/class
- Arbitrary properties (like tags) on any entity (namespace, struct, class, field, method, enum, enum value)
- Reflection metadata is regenerated only when a file changes
- Can instantiate any objects just from an archetype (which is obtainable by name or id), with arbitrary parameters
- Know at compile-time if a struct/class is reflected or not (can be combined with if constexpr expression)

## Index
- [Getting started](#getting-started)
  - [Requirements](#requirements)
  - [Library Integration](#library-integration)
  - [Parser/Generator Integration](#parsergenerator-integration)
  - [Possible issues](#possible-issues)
- [Framework Overview](#framework-overview)
  - [Archetype](#archetype)
    - [Structs / Classes](#structs--classes)
    - [Enums / Enum values](#enums--enum-values)
  - [Fields](#fields)
  - [Methods](#methods)
  - [Namespaces](#namespaces)
- [Properties](#properties)
  - [Overview](#overview)
  - [Builtin Properties](#builtin-properties)
- [Customization](#customization)
- [Cross-platform compatibility](#cross-platform-compatibility)
- [Planned features](#planned-features)
- [Known issues](#known-issues)
- [License](#license)

## Getting started
**Pre-built binaries for Windows x64 are available [here](https://github.com/jsoysouvanh/Refureku/releases). If you want to use those, you can skip to step 3 (this is true for the [Library Integration part](#library-integration) as well as the [Parser/Generator Integration part](#parsergenerator-integration).**

>**Note:** Refureku integration examples are available [here](https://github.com/jsoysouvanh/Refureku/tree/master/Refureku/Examples).

### Requirements:
- CMake 3.15.0+ (if you build the library from source).
- A compatible compiler: MSVC Platform Toolset v141+ / GCC8.0.0+ / Clang 7.0.0+.

### Library Integration
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
	- If you're compiling your project in debug mode, you will also probably need the debug version too:
		- cmake -B Build/Debug -DCMAKE_BUILD_TYPE=Debug -G "\<Generator\>"
		- cmake --build Build/Debug --config Debug --target **Refureku**
	- You will find the generator binaries in Build/Release/Bin/ and the library in Build/[Debug|Release]/Lib/
		> **Note:** On multiple configuration generators such as Visual Studio or XCode, an additional Debug/Release folder is generated.

3.  Add necessary header directories to your project settings:
    - Refureku header directory, located at /Refureku/Library/Include, or /Include from the binaries.

4.  Add library directories to your projet settings:
    - The directory containing Refureku.lib, located at /Build/[Debug|Release]/Lib/, or /Lib from the binaries.

5.  Link against:
    - Refureku.lib. Make sure you link against the Debug version of the library if you compile your project in Debug mode to prevent [this issue](#issue-1).

6. Update RefurekuSettings.toml located in /Build/Release/Bin/, or /Bin if you downloaded the binaries. You must at least specify:
	- [FileGeneratorSettings] outputDirectory = '''Path/To/An/Output/Directory'''
	- [FileGeneratorSettings] toParseDirectories = [ '''Path/To/Dir/To/Parse1''', ... ]
	- [FileParserSettings] projectIncludeDirectories = [ '''Path/To/Refureku/Library/Include''', '''Path/To/Your/Project/Include/Dir1''', ... ]
	- **If the specified outputDirectory is in a parsed directory**, you should ignore it too (you don't want to parse generated metadata do you?)
	[FileGeneratorSettings] ignoredDirectories = [ '''Path/To/An/Output/Directory''' ]
	> **Note:** All paths must be written between ''' ''', and be either absolute or relative to your workspace directory. Check out the [SimpleIntegration project](https://github.com/jsoysouvanh/Refureku/tree/master/Refureku/Examples/SimpleIntegration)'s [RefurekuSettings.toml](https://github.com/jsoysouvanh/Refureku/blob/master/Refureku/Examples/ThirdParty/Bin/RefurekuSettings.toml) for a concrete example.
	
7. Make the RefurekuGenerator run just before your project's compilation:
	- With CMake:
	```cmake
	# Run generator before compiling our own program
	add_custom_target(RunGenerator
				WORKING_DIRECTORY Your/Working/Directory
				COMMAND Path/To/The/RefurekuGenerator)
	add_dependencies(YourExecutable RunGenerator)
	```
	- With Visual Studio:
		> In Project properties > Build Events > Pre-Build Event, add the command Path\To\Executable\RefurekuGenerator.exe

8. Make sure you compile your project in C++17 or later.
9. Compile your project: you should see build logs from the RefurekuGenerator with a list of parsed files, or error logs if something went wrong. If you encounter errors, see the [Possible issues section](#possible-issues). If it doesn't help, don't hesitate to [open a new issue](https://github.com/jsoysouvanh/Refureku/issues).

### Parser/Generator Integration
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
    - Kodgen header directory, located at /Refureku/Generator/Submodules/Kodgen/Include, or /ThirdParty/Include from the binaries.
    - Kodgen dependencies header directory, located at /Refureku/Generator/Submodules/Kodgen/ThirdParty/Include. If you downloaded the binaries, it is the same directory as above so you don't need to redo it.
    - RefurekuGenerator header directory, located at /Refureku/Generator/Include, or /Include/RefurekuGenerator from the binaries.

4.  Add library directories to your projet settings:
    - Kodgen.lib directory, located at /Build/[Debug|Release]/Lib/, or /ThirdParty/Lib from the binaries.
    - Kodgen dependencies library directory, located at /Refureku/Generator/Submodules/Kodgen/ThirdParty/x64/Static. If you downloaded the binaries, it is the same directory as above so you don't need to redo it.
    - RefurekuGeneratorLib.lib directory, located at /Build/[Debug|Release]/Lib/, or /Lib from the binaries.

5.  Link against:
    - clang.lib
    - Kodgen.lib: Make sure to use the Debug version if you compile your project in Debug mode
    - RefurekuGeneratorLib.lib: Make sure to use the Debug version if you compile your project in Debug mode

7.  Setup your project C++ compilation version to C++17 or later.
8.  Compile!
9.  Before running your program, make sure that the libclang dynamic library is located next to your executable. You should find it at /Refureku/Generator/Submodules/Kodgen/ThirdParty/x64/Shared, or /Bin from the binaries.

You should be able to run the following snippet:

```cpp
#include <Refureku/FileParser.h>
#include <Refureku/FileGenerator.h>
#include <Kodgen/Misc/DefaultLogger.h>

int main()
{
    rfk::FileParser	fileParser;
    rfk::FileGenerator	fileGenerator;

    //Set logger
    kodgen::DefaultLogger logger;

    fileParser.logger = &logger;
    fileGenerator.logger = &logger;

    //Parse
    kodgen::FileGenerationResult genResult = fileGenerator.generateFiles(fileParser, false);

    return 0;
}
```

### Possible issues
#### Issue 1
- If you compile your program in debug mode, your compiler might complain about library / debug level mismatchs. In that case, make sure to compile the Refureku library both in Debug and Release, and link against the debug version of the library when compiling your program in debug mode.

## Framework overview
### Archetype
The archetype class contains information about a model type, like its name for example.
Each reflected class, struct and enum owns a unique archetype in the program. All C++ fundamental types also have their archetype.

#### Structs / Classes
The Class and Struct classes inherit from Archetype and contain additional data such as fields and methods. Class and Struct are not different from each other in the current library implementation, but are still separated to allow further development.

Consider the following header file, let's say ExampleClass.h:

```cpp
#pragma once

#include "Generated/ExampleClass.rfk.h"

struct RFKStruct() ExampleStruct
{
    ExampleStruct_GENERATED
};
class RFKClass() ExampleClass
{
    ExampleClass_GENERATED
};

File_GENERATED

```

To retrieve those classes, we can write the following:

```cpp
#include "ExampleClass.h"

//...

rfk::Struct const& exampleStructArchetype = ExampleStruct::staticGetArchetype();
rfk::Class const& exampleClassArchetype = ExampleClass::staticGetArchetype();

//Iterate over fields
for (rfk::Field const& field : exampleClassArchetype.fields)
    //Do something

//Iterate over methods
for (rfk::Method const& method : exampleClassArchetype.methods)
    //Do something
```

You could also retrieve archetypes from the database using the archetype name like so:

```cpp
#include <Refureku/TypeInfo/Database.h>

rfk::Struct const* exampleStructArchetype = rfk::Database::getStruct("ExampleStruct");
rfk::Class const* exampleClassArchetype = rfk::Database::getClass("ExampleClass");
```
Or even use the getArchetype method on an instance of a reflected archetype having the [DynamicGetArchetype property](#dynamicgetarchetype-struct--class).

#### Enums / Enum values
Just like structs and classes, we can reflect enums. If an enum is reflected, nested enum values will automatically be reflected too, but it is still possible to add [properties](#properties) to them.

```cpp
#pragma once

#include "Generated/ExampleEnum.rfk.h"

enum class RFKEnum() ExampleEnum : int
{
	ExampleValue1 = 0u,
	ExampleValue2 RFKEnumVal() = 42u,
	ExampleValue3
};

File_GENERATED
```

```cpp
#include "ExampleEnum.h"

rfk::Enum const* exampleEnumArchetype = rfk::getEnum<ExampleEnum>();

//Iterate over enum values
for (rfk::EnumValue const& enumValue : exampleEnumArchetype->values)
{
    //Do something
    std::cout << enumValue.name << " = " << enumValue.value << std::endl;
}

//Retrieve an EnumValue from name
exampleEnumArchetype->getEnumValue("ExampleValue1");

//Retrieve an EnumValue from int value
exampleEnumArchetype->getEnumValue(0u);
```

From the database:

```cpp
#include <Refureku/TypeInfo/Database.h>

//...

rfk::Enum const* exampleEnumArchetype = rfk::Database::getEnum("ExampleEnum");
```

### Fields
Field and StaticField classes handle information about a class or struct reflected field.
Usage example:

```cpp
#pragma once

#include "Generated/ExampleClass.rfk.h"

class RFKClass() ExampleClass
{
    protected:
        RFKField()
        inline static float exampleFloat = 3.14f;

    public:
        RFKField()
        int exampleInt = 0;

    ExampleClass_GENERATED
};

File_GENERATED
```

```cpp
#include "ExampleClass.h"

//...

ExampleClass instance;
rfk::Class const& classArchetype = ExampleClass::staticGetArchetype();

//Find a field by name - You can filter fields with other arguments
rfk::Field const* field = classArchetype.getField("exampleInt");

field->getData<int>(&instance); //Get 0
field->setData(&instance, 42);  //Set 42 in instance
field->getData<int>(&instance); //Get 42

//Find a static field by name - You can filter static fields with other arguments
rfk::StaticField const* staticField = classArchetype.getStaticField("exampleFloat");

staticField->getData<float>();  //Get 3.14
staticField->setData(42.42f);   //Set 42.42
staticField->getData<float>();  //Get 42.42
```

### Methods
Method and StaticMethod classes work just the same way as fields:

```cpp
#pragma once

#include "Generated/ExampleClass.rfk.h"

class RFKClass() ExampleClass
{
    private:
        RFKMethod()
        static void staticNoReturnNoParam() {}
        
        RFKMethod()
        void noReturnNoParam() {}
        
    protected:
        RFKMethod()
        int returnNoParam() const { return 42; }

    public:
        RFKMethod()
        int returnWithParams(float a, float b) { return a + b; }

    ExampleClass_GENERATED
};

File_GENERATED
```

```cpp
#include "ExampleClass.h"

//...

ExampleClass const instance;
rfk::Class const& classArchetype = ExampleClass::staticGetArchetype();

//Get methods and call them
rfk::Method const* f1 = classArchetype.getMethod("noReturnNoParam");
f1->invoke(&instance);  //Note that we can call non const method on const instance

rfk::Method const* f2 = classArchetype.getMethod("returnNoParam");
f2->invoke(&instance);  //If you don't care about the return value, you can omit the template argument
f2->invoke<int>(&instance); //Return 42

rfk::Method const* f3 = classArchetype.getMethod("returnWithParams");
f3->invoke<int>(&instance, 21.0f, 21.0f);   //Return 42

//It works exactly the same for static methods, but we don't need to provide an instance
rfk::StaticMethod const* sf1 = classArchetype.getStaticMethod("staticNoReturnNoParam");
sf1->invoke();
```

### Namespaces
Namespaces can be reflected like this:

```cpp
#pragma once

#include "Generated/ExampleNamespace.rfk.h"

namespace ExampleNamespace RFKNamespace()
{
    namespace ExampleNamespaceNested RFKNamespace()
    {
    }
}

File_GENERATED
```

C++17 nested namespace declaration is also supported, but note that all namespaces will be assigned the same properties:

```cpp
#pragma once

#include "Generated/ExampleNamespace.rfk.h"

namespace ExampleNamespace::ExampleNamespaceNested RFKNamespace()
{
}

File_GENERATED
```

Note that declaring the same namespace multiple times in a single file will produce an error. Declaring the same namespaces in different files is however valid.

```cpp
#pragma once

#include "Generated/ExampleNamespace.rfk.h"

namespace ExampleNamespace RFKNamespace()
{
    //Do something
}

// ---------v This produces an error 
namespace ExampleNamespace RFKNamespace()
{
    //Do something else
}

// ---------v This also produces an error because ExampleNamespace is already defined above
namespace ExampleNamespace::ExampleNamespaceNested RFKNamespace()
{
    //Do something
}

File_GENERATED
```

Use namespace reflected data:

```cpp
#include <Refureku/TypeInfo/Database.h>

//...

rfk::Namespace const* en = rfk::Database::getNamespace("ExampleNamespace");
rfk::Namespace const* enn = rfk::Database::getNamespace("ExampleNamespace::ExampleNamespaceNested");

rfk::Struct const* s = en->getStruct("SomeReflectedStruct");
rfk::Class const* c = en->getClass("SomeReflectedClass");
rfk::Enum const* e = en->getEnum("SomeReflectedEnum");
rfk::Namespace const* nn = en->getNestedNamespace("ExampleNamespaceNested");
```

## Properties
### Overview
Properties are additional data that can be attached to any entity through the reflection macro. You can read more about  [how to add new properties here](https://github.com/jsoysouvanh/Kodgen#properties--propertyrules).

```cpp
#pragma once

#include "Generated/Example.rfk.h"

class RFKClass(CustomSimpleProperty, CustomComplexProperty(SubProp1, SubProp2)) ExampleClass
{
    ExampleClass_GENERATED
};

enum class RFKEnum(EnumProp) ExampleEnum
{
    EnumValue1 = 0,
    EnumValue2 RFKEnumVal(EnumValueProp) = 1
};

File_GENERATED
```

And we can retrieve properties like so:

```cpp
#include "Example.h"

//...

rfk::Class const& classArchetype = ExampleClass::staticGetArchetype();

//Iterate over all simple properties
for (rfk::SimpleProperty const& simpleProp : classArchetype.properties.simpleProperties)
    std::cout << simpleProp.mainProperty << std::endl;

//Iterate over all complex properties
for (rfk::ComplexProperty const& complexProp : classArchetype.properties.complexProperties)
    std::cout << complexProp.mainProperty << std::endl;

//Check if an entity has a specific simple or complex property
if (rfk::SimpleProperty const* simpleProp = classArchetype.properties.getSimpleProperty("CustomSimpleProperty"))
{
    //Do something
}

if (rfk::ComplexProperty const* complexProp = classArchetype.properties.getComplexProperty("CustomComplexProperty"))
{
    //Iterate over all subproperties of a chosen complex property
    for (std::string const& subprop : complexProp->subProperties)
    {
        //Do something with subprops
    }

    //Helpers to retrieve a subproperty as int, uint, float or string
    complexProp->getInt32(0u);	//0 means the first subproperty
    //This call actually throws an exception because can't convert SubProp1 to an int.
}
```

It can be really useful when you want to adapt behaviors depending on specific properties (for a game engine editor for example).

### Builtin Properties
- [Kodgen Properties](https://github.com/jsoysouvanh/Kodgen#builtin-properties)
- [DynamicGetArchetype](#dynamicgetarchetype-struct--class)
- [CustomInstantiator](#custominstantiator-method)

#### DynamicGetArchetype (Struct / Class)
DynamicGetArchetype is a simple property which should be specified when a class or struct should override the getArchetype() method declared by rfk::ReflectedObject. It allows to retrieve the archetype of a reflected class instance through a virtual call to classInstance->getArchetype().

```cpp
#pragma once

#include <Refureku/ReflectedObject.h>

#include "Generated/ExampleClass.rfk.h"

class RFKClass(DynamicGetArchetype) ExampleClassBase : public rfk::ReflectedObject
{
    ExampleClassBase_GENERATED
};

//DynamicGetArchetype MUST be specified even if it doesn't inherit directly from rfk::ReflectedObject
class RFKClass(DynamicGetArchetype) ExampleClass : public ExampleClassBase
{
    ExampleClass_GENERATED
};

File_GENERATED
```

```cpp
#include <Refureku/TypeInfo/Database.h>

//...

rfk::ReflectedObject* ecb = rfk::Database::getClass("ExampleClassBase")->makeInstance<rfk::ReflectedObject>();
rfk::ReflectedObject* ec = rfk::Database::getClass("ExampleClass")->makeInstance<rfk::ReflectedObject>();

std::cout << ecb->getArchetype().name << std::endl;    //Prints ExampleClassBase
std::cout << ec->getArchetype().name << std::endl;    //Prints ExampleClass

delete ecb;
delete ec;
```

> DynamicGetArchetype must be specified eventhough ExampleStruct doesn't directly inherit from rfk::ReflectedObject. If not specified, calling getArchetype on an instance of ExampleClass will call the parent implementation, which will return ExampleClassBase archetype.

#### CustomInstantiator (Method)
CustomInstantiator is used to provide custom ways of instantiating a struct or class through the rfk::Struct::makeInstance method. By default, we can only call this method without parameters (it will call the default constructor if it is not deleted, otherwise the method will return nullptr). Using the CustomInstantiator property, we can write the following:

```cpp
#pragma once

#include <iostream>

#include "Generated/ExampleClass.rfk.h"

class RFKClass() ExampleClass
{
    protected:
        RFKMethod(CustomInstantiator)
        static void* customInstantiateMethod(int i, float f)
        {
            std::cout << "Use customInstantiateMethod(int i, float f)" << std::endl;

            return new ExampleClass(i, f);
        }

    public:
        ExampleClass() = delete;
        ExampleClass(int i, float f) {  }
        
    ExampleClass_GENERATED
};

File_GENERATED
```

```cpp
#include "ExampleClass.h"

//...

rfk::Class const& c = ExampleClass::staticGetArchetype();

/**
*    Return nullptr because ExampleClass is not default constructible.
*    However, if we define a CustomInstantiator tagged method which takes no argument,
*    it will be used.
*/
ExampleClass* instance1 = c.makeInstance<ExampleClass>();

//ExampleClass will be instantiated through customInstantiateMethod
ExampleClass* instance2 = c.makeInstance<ExampleClass>(42, 3.14f);

delete instance1;
delete instance2;
```

>**Note:** A CustomInstantiator tagged method **MUST** be static and return void*. If the method doesn't fulfill those requirements, an error will be thrown by the parser/generator.

## Customization
You can customize a wide range of settings by modifying the FileParser and the FileGenerator classes. However, for a simple use of the library, you will probably not have extra energy to spend in modifying/recompiling the generator source code. For that reason, most of the settings are editable in the RefurekuSettings.toml file. You can have a look at the different settings by reading [this section](https://github.com/jsoysouvanh/Kodgen#fileparser) and [this section](https://github.com/jsoysouvanh/Kodgen#filegenerator).

If you are integrating Refureku generator to your program, you will find all the information you need in [Kodgen's README](https://github.com/jsoysouvanh/Kodgen#kodgen). Just keep in mind that you will need to extend rfk::FileParser and rfk::FileGenerator **instead of** kodgen::FileParser and kodgen::FileGenerator. 

## Cross-platform compatibility
This library has been tested and is stable on the following configurations:
- Windows Server version 1809 | MSVC 19.16.27035.0
- Linux 18.04 | Clang 7.0.0, Clang 8.0.0, Clang 9.0.0
- Linux 18.04 | GCC 8.4.0, GCC 9.2.1

## Planned features
- Update database to allow entity unregistering, hence making hot reload possible
- Support global scope (or namespace) fields and functions reflection
- Support template methods reflection 

## Known issues

## License
MIT License

Copyright (c) 2020 Julien SOYSOUVANH

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
