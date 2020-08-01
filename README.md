# Refureku

[![Latest Release](https://badge.fury.io/gh/jsoysouvanh%2FRefureku.svg)](https://github.com/jsoysouvanh/Refureku/releases/latest)
[![Build Status](https://travis-ci.com/jsoysouvanh/Refureku.svg?branch=master)](https://travis-ci.com/jsoysouvanh/Refureku)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/ba0bf8ff67cf47c498409aef31b88700)](https://www.codacy.com/manual/jsoysouvanh/Refureku?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=jsoysouvanh/Refureku&amp;utm_campaign=Badge_Grade)

Refureku is a powerful customizable C++17 runtime reflection library based on [Kodgen](https://github.com/jsoysouvanh/Kodgen).
It allows you to retrieve information on namespaces, structs/classes, fields, methods, enums and enum values at runtime.

It is separated into 2 distinct parts:
- The metadata parser and generator, which parses C++ source code and generates metadata that will be injected back into source code using macros. This tool can either be built as a standalone executable or embeded in a program (for example a game engine) depending on your needs. Last but not least, it is highly customizable (see the [Customization section](#customization)).
- The actual library which contains the framework classes to access and manipulate reflected data at runtime.

To get started now, see the [Getting Started](#getting-started) section.

## Index
- [Features](#features)
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
  - [From a TOML file](#from-a-toml-file)
  - [From C++ code](#from-c-code)
    - [FileParser](#fileparser)
    - [FileGenerator](#filegenerator)
    - [Usage](#usage)
- [Getting started](#getting-started)
  - [Requirements](#requirements)
  - [Steps](#steps)
  - [Possible issues](#possible-issues)
- [Cross-platform compatibility](#cross-platform-compatibility)
- [Planned features](#planned-features)
- [Known issues](#known-issues)
- [License](#license)

## Features
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
#include <TypeInfo/Database.h>

rfk::Struct const* exampleStructArchetype = rfk::Database::getStruct("ExampleStruct");
rfk::Class const* exampleClassArchetype = rfk::Database::getClass("ExampleClass");
```
Or even use the getArchetype method on an instance of a reflected archetype having the [DynamicGetArchetype property](#dynamicgetarchetype-struct--class).

#### Enums / Enum values
Just like structs and classes, we can reflect enums. If an enum is reflected, nested enum values will automatically be reflected too, but it is still possible to add [properties](#properties) to them.

```cpp
#include "Generated/ExampleEnum.rfk.h"

enum class RFKEnum() ExampleEnum : int
{
	ExampleValue1 = 0u,
	ExampleValue2 RFKEnumVal(SomeProperty) = 42u,
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
#include <TypeInfo/Database.h>

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
#include "Generated/ExampleNamespace.rfk.h"

namespace ExampleNamespace::ExampleNamespaceNested RFKNamespace()
{
}

File_GENERATED
```

Note that declaring the same namespace multiple times in a single file will produce an error. Declaring the same namespaces in different files is however valid.
```cpp
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
#include <TypeInfo/Database.h>

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
Properties are just like tags that can be attached to any entity through the reflection macro. These properties are following a syntax which is handled by the parser using rules defined by the user (see the [Customization section](#customization)). If the syntax is violated, the generator will generate errors. Each property can accept subproperties (or arguments).

```cpp
#pragma once

#include "Generated/Example.rfk.h"

class RFKClass(CustomSimpleProperty, CustomComplexProperty[SubProp1, SubProp2]) ExampleClass
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

    //Helpers to retrieve a property as int, uint, float or string
    complexProp->getInt32(0u);	//0 means the first subproperty
    //this call actually throws an exception because can't convert SubProp1 to an int.
}
```

It can be really useful when you want to adapt behaviors depending on specific properties (for a game engine editor for example).

### Builtin Properties
- [DynamicGetArchetype](#dynamicgetarchetype-struct--class)
- [CustomInstantiator](#custominstantiator-method)
- [ParseAllNested](#parseallnested-namespace--struct--class)

#### DynamicGetArchetype (Struct / Class)
DynamicGetArchetype is a simple property which should be specified when a class or struct should override the getArchetype() method declared by rfk::ReflectedObject. It allows to retrieve the archetype of a class on its instances through a virtual call to classInstance->getArchetype().

```cpp
#include <ReflectedObject.h>

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
#include <TypeInfo/Database.h>

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

>A CustomInstantiator tagged method **MUST** be static and return void*. If the method doesn't fulfill those requirements, an error will be thrown by the parser/generator.

#### ParseAllNested (Namespace / Struct / Class)
Use ParseAllNested when you want to parse every entity **directly** nested in a namespace, struct or class, without having to necessarly specify the reflection macro again.

```cpp
#include "Generated/ExampleClass.rfk.h"

namespace ExampleNamespace RFKNamespace(ParseAllNested)
{
    class /* Even if RFKClass() is not specified, this class is reflected */ NestedExampleClass
    {
        public:
            int i; //This field is NOT reflected as it is not **directly** inside a ParseAllNested tagged entity
        
        NestedExampleClass_GENERATED
    };
}

class RFKClass(ParseAllNested) ExampleClass
{
    public:
        //This field is reflected automatically
        int i;
        
        //This method is reflected automatically
        void someMethod() {}

        //This nested struct is reflected automatically
	struct NestedExampleStruct
	{
	    NestedExampleStruct_GENERATED
	};

        //This enum is reflected automatically
        enum class NestedExampleEnum
        {
            Value1 //Enum values are ALWAYS reflected automatically
        };
    
    ExampleClass_GENERATED
};

File_GENERATED

```

Alternatively, if you just want to reflect all entities contained in each parsed file, you might consider setup FileParser::parsingSettings.shouldParseAllEntities boolean to true.

## Customization
Before talking about how to customize the code generation, let's talk a bit about how it works.   
There are 3 main classes which make the code generation possible: the FileParser, the GeneratedCodeTemplate and the FileGenerator. When the code generation process starts, a source file is parsed by the FileParser and the retrieved data are passed to the FileGenerator. From that point, the FileGenerator will check for each parsed archetype (i.e each struct, class or enum) which GeneratedCodeTemplate to use. File are then generated by the relevant GeneratedCodeTemplate. To sum up:
 1. The FileParser extracts data from source file;
 2. The FileGenerator choses the right GeneratedCodeTemplate for a given parsed archetype;
 3. The GeneratedCodeTemplate generates the file & code;

Each of those 3 classes contain overridable methods and modifiable fields, and this is where user customization starts. However, it might be tedious to modify and recompile the code each time you want to update something, that's why Refureku offers 2 possibilities:
- Customize parsing and generation properties from a TOML file. It is enough in most use cases and is really fast and easy to setup.
- Handle everything from C++ to allow a full control, from data modification to method overrides. This option is more likely to be used if you want to embed the generation system into another software like a game engine.

You can decide to chose either one or to combine both at the same time.

### From a TOML file
A template TOML file named RefurekuSettings.toml with all editable properties is provided in the repository, and will be copied next to the executable after it is built. You can specify whichever property you want and simply remove or comment the ones you don't use. Make sure this settings file is always located next to the RefurekuGenerator executable.

Paths must be written between ''' '''. They may be absolute or relative, but note that relative paths will be relative to the working directory.
- In Cmake, the working directory is specified in the add_custom_target call
	```cmake
	add_custom_target(RunGenerator
			  WORKING_DIRECTORY Your/Working/Directory
			  COMMAND Path/To/The/RefurekuGenerator)
	```
- In Visual Studio, the working directory is specified in **Project > Properties > Configuration Properties > Debugging > Working Directory**

On Windows, you can use either / or \ as a path separator.

As an example is always easier to understand than a long explanation, please look at the [RefurekuSettings.toml located in the Examples folder](https://github.com/jsoysouvanh/Refureku/tree/master/Refureku/Examples/ThirdParty/Exe) for an example setup with both CMake and Visual Studio.

### From C++ code
Editable properties from C++ code are the same than the ones accessible from the TOML file.

#### FileParser
The parser is probably the class which you will want to change at first to modify the global syntax for reflection. If the default Refureku syntax is fine, you can reuse the rfk::FileParser as it is, but let's make a new one to see what we can change:
```cpp
//Header file, let's say CustomFileParser.h
#pragma once

#include <FileParser.h> //Refureku/Generator/Include/FileParser.h

class CustomFileParser : public rfk::FileParser
{
    protected:
        void preParse(fs::path const& parseFile) override;
        void postParse(fs::path const& parseFile, kodgen::ParsingResult const& result) override;
    
    public:
        CustomFileParser();
};
```
```cpp
#include "CustomFileParser.h"

CustomFileParser::CustomFileParser():
    rfk::FileParser()
{
    //Let's get the settings
    kodgen::ParsingSettings& parsingSettings = getParsingSettings();

    //Whether to cancel the parsing process when an error is detected or parse until the end anyway.
    parsingSettings.shouldAbortParsingOnFirstError = true;

    //Let's play with the property settings
    kodgen::PropertyParsingSettings& pps = parsingSettings.propertyParsingSettings;

    //First of all, macro syntax!
    pps.classPropertyRules.macroName = "CLASS"; //Source code will look like class CLASS() CustomClass {};
    //Works the same for each propertyRule: pps.classPropertyRules, pps.fieldPropertyRules, pps.enumPropertyRules etc...

    //Define how properties should be parsed
    pps.ignoredCharacters = {' '};  //CLASS( Prop ) is the same as CLASS(Prop)
    pps.propertySeparator = ',';    //CLASS(Prop1, Prop2)
    pps.subPropertyEnclosers[0] = '[';  //CLASS(ComplexProp[SubProp])
    pps.subPropertyEnclosers[1] = ']'; 
    pps.subPropertySeparator = ','; //CLASS(ComplexProp[SubProp1, SubProp2])
    
    //Define valid properties for each entity type
    //Simple property
    pps.classPropertyRules.addSimplePropertyRule("CustomSimpleProp");   //CLASS(CustomSimpleProp)

    //Complex property using regex for subprops
    pps.classPropertyRules.addComplexPropertyRule("CustomComplexProp", "CustomSubProp");    //CLASS(CustomComplexProp[CustomSubProp])
    pps.classPropertyRules.addComplexPropertyRule("CCP2", "CSP[1-9]");  //CLASS(CCP2[CSP1, CSP6, CSP9])
    pps.classPropertyRules.addComplexPropertyRule("CCP3", "Option1|Option2|Option3");   //CLASS(CCP3[Option1])   CLASS(CCP3[Option2, Option3])
}

void CustomFileParser::preParse(fs::path const& parseFile)
{
    //Optionally call parent implementation
    //rfk::preParse(parseFile);

    //Do whatever you want to do before a file is parsed (can be logs or whatever)
}

void CustomFileParser::postParse(fs::path const& parseFile, kodgen::ParsingResult const& result)
{
    //Optionally call parent implementation
    //rfk::postParse(parseFile, result);

    //Do whatever you want to do after a file has been parsed (can be logs, checks or whatever)
}
```

#### FileGenerator
The file generator handles collections of paths to files and directories to determine what should be parsed and what should not. Let's make a simple one:
```cpp
//Header file, CustomFileGenerator.h
#pragma once

#include <FileGenerator.h>  //Refureku/Generator/Include/FileGenerator.h

class CustomFileGenerator : public rfk::FileGenerator
{
    protected:
        void writeHeader(kodgen::GeneratedFile& file, kodgen::ParsingResult const& parsingResult) const noexcept override;
        void writeFooter(kodgen::GeneratedFile& file, kodgen::ParsingResult const& parsingResult) const noexcept override;
};

    public:
        CustomFileGenerator();
```
```cpp
#include "CustomFileGenerator.h"

CustomFileGenerator::CustomFileGenerator():
    rfk::FileGenerator()
{
    //Generated files will use .customextension extension
    generatedFilesExtension = ".customextension";
}

void CustomFileGenerator::writeHeader(kodgen::GeneratedFile& file, kodgen::ParsingResult const& parsingResult) const noexcept
{
    //MUST CALL PARENT IMPLEMENTATION
    rfk::FileGenerator::writeHeader(file, parsingResult);

    //Write something else in the generated file header?
    file.writeLine("/* Write some custom code here */");
    file.writeLines("/* Write some custom code here", "on ", "as", "many", "lines as you want */");
}

void CustomFileGenerator::writeFooter(kodgen::GeneratedFile& file, kodgen::ParsingResult const& parsingResult) const noexcept
{
    //Optionally call parent implementation
    //rfk::FileGenerator::writeFooter(file, parsingResult);
}
```
#### Usage
Once you've setup the FileParser and the FileGenerator, making everything work is pretty straight forward.
However, there is one more piece of information we **MUST** provide to the FileParser to make it work properly: the include directories you added to your project. Indeed, the parser needs to know where it can find the files you include or it won't be able to resolve all symbols in a translation unit. The first one you can add is the **Refureku library include directory** (Refureku/Library/Include)
```cpp
#include <iostream>
#include <filesystem>

#include <GeneratedClassCodeTemplate.h>
#include <GeneratedEnumCodeTemplate.h>

#include "CustomFileParser.h"
#include "CustomFileGenerator.h"

int main()
{
    CustomFileParser    fileParser;
    CustomFileGenerator fileGenerator;

    //Can explicitely load settings from a toml file
    if (fileGenerator.loadSettings("RefurekuSettings.toml"))
    {
        //Load success
    }

    if (fileParser.loadSettings("RefurekuSettings.toml"))
    {
        //Load success
    }

    //-------------------------------------------------
    //THIS PART IS MANDATORY TO MAKE THE GENERATOR WORK (or it must be loaded from the TOML settings file)

    fileParser.getParsingSettings().projectIncludeDirectories.emplace("Path/To/Refureku/Include/Directory");	//Refureku/Library/Include
    fileParser.getParsingSettings().projectIncludeDirectories.emplace("Path/To/Your/Include/Directory");
    //... Add all the include directories you added to your project

    //-------------------------------------------------

    //Setup the files / directories you want to parse and/or ignore
    fileGenerator.includedDirectories.emplace("Path/To/A/Directory/To/Parse");
    fileGenerator.includedFiles.emplace("Path/To/A/File/To/Parse.h");
    fileGenerator.ignoredDirectories.emplace("Path/To/A/Directory/To/Ignore");
    fileGenerator.ignoredFiles.emplace("Path/To/A/File/To/Ignore.h");
    fileGenerator.outputDirectory = "Path/To/A/Directory";  //Generated files will be placed here

    //Parse and generate files. false means only new/modified files will be regenerated
    kodgen::FileGenerationResult genResult = fileGenerator.generateFiles(fileParser, false);

    if (genResult.completed)
    {
        //Can check generation result
        //genResult.parsingErrors contains parsing errors
        //genResult.fileGenerationErrors contains generation errors
    }
    else  //Generation was aborted
    {
        //Probably forgot or provided a bad output directory
    }

    return EXIT_SUCCESS;
}
```

All this process can be setup in a standalone executable which will be called before you code base is compiled (you can use CMake add_custom_target(...) and add_dependencies(...), or MSVC Build events), but as you could see, it could easily be integrated in an application as well.

## Getting started
### Requirements:
- CMake 3.15.0+ (if you build the library from source).
- A compatible compiler: MSVC Platform Toolset v141+ / GCC8.0.0+ / Clang 7.0.0+.

### Steps
If you get lost when reading the following steps, you're greatly encouraged to have a look at the [Examples folder](https://github.com/jsoysouvanh/Refureku/tree/master/Refureku/Examples) where there is a sample project integrating Refureku.

**Pre-built binaries for Windows x64 are available [here](https://github.com/jsoysouvanh/Refureku/releases). If you want to use those, you can skip to step 3.**

1. Pull the repository
2. Compile the library and the generator following these steps:
	- At the root of the Refureku project, open a terminal
		- cmake -B Build/Release -DCMAKE_BUILD_TYPE=Release -G "\<Generator\>" -A x64
			> Most common generators include:
			> - Visual Studio 15 2017 -> cmake -B Build/Release -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 15 2017" -A x64
			> - Unix Makefiles
			> - Ninja -> cmake -B Build/Release -DCMAKE_BUILD_TYPE=Release -G "Ninja"
			> - Type cmake -G for more information
		- cmake --build Build/Release --config Release --target RefurekuGenerator Refureku
	- If you're compiling your project in debug mode, you will also probably need the debug version of Refureku:
		- cmake -B Build/Debug -DCMAKE_BUILD_TYPE=Debug -G "\<Generator\>" -A x64
		- cmake --build Build/Debug --config Debug --target Refureku
	- You will find the generator binaries in Build/Release/Bin/ and the library in Build/[Debug|Release]/Lib/
		> **Note:** On multiple configuration generators such as Visual Studio or XCode, an additional Debug/Release folder is generated. Make sure to move libclang.dll and RefurekuSettings.toml next to the generator executable.
3. In your project settings, add the Refureku headers directory to the include directories. If you compiled the library yourself, the headers directory is located at Refureku/Library/Include. If you downloaded the binaries, the headers directory is the Include directory. 
4. Link against Refureku.lib. Make sure to use the Debug version of the library if you compile your project in Debug mode to prevent [this issue](#issue-1).
	-  With CMake, it would look like this:
	```cmake
	# Add Refureku Include directory
	target_include_directories(YourExecutable PRIVATE Path/To/Refureku/Library/Include)
	
	# Link against Refureku library
	target_link_directories(YourExecutable PRIVATE Path/To/Refureku/Library)
	target_link_libraries(YourExecutable PRIVATE $<IF:$<CONFIG:Debug>,RefurekuDebug,RefurekuRelease>)
	```
5. Update RefurekuSettings.toml located in Build/Release/Bin/ as [described here](#from-a-toml-file). You must at least specify:
	- [FileGeneratorSettings] outputDirectory = '''Path/To/An/Output/Directory'''
	- [FileGeneratorSettings] toParseDirectories = [ '''Path/To/Dir/To/Parse1''', ... ]
	- [FileParserSettings] projectIncludeDirectories = [ '''Path/To/Refureku/Library/Include''', '''Path/To/Your/Project/Include/Dir1''', ... ]
	- **If the specified outputDirectory is in a parsed directory**, you should ignore it too     
	[FileGeneratorSettings] ignoredDirectories = [ '''Path/To/An/Output/Directory''' ]
6. Make the RefurekuGenerator run before compiling your project:
	- With CMake:
	```cmake
	# Run generator before compiling our own program
	add_custom_target(RunGenerator WORKING_DIRECTORY Your/Working/Directory COMMAND Path/To/The/RefurekuGenerator)
	add_dependencies(YourExecutable RunGenerator)
	```
	- With Visual Studio:
		> In Project properties > Build Events > Pre-Build Event, add the command Path\To\Executable\RefurekuGenerator.exe
7. Make sure you compile your project in C++17 or later.
8. Compile your project: you should see build logs from the RefurekuGenerator with a list of parsed files, or error logs if something went wrong. If you encounter errors, see the [Possible issues section](#possible-issues). If it doesn't help, don't hesitate to [open a new issue](https://github.com/jsoysouvanh/Refureku/issues).

### Possible issues
#### Issue 1
- If you compile your program in debug mode, your compiler might complain about library / debug level mismatchs. In that case, make sure to compile the Refureku library both in Debug and Release, and link against the debug version of the library when compiling your program in debug mode.
	> With CMake:
	```cmake
	target_link_libraries(YourExecutable PRIVATE $<IF:$<CONFIG:Debug>,RefurekuDebug,RefurekuRelease>)
	```

## Cross-platform compatibility
This library has been tested and is stable on the following configurations:
- Windows Server version 1809 | MSVC 19.16.27035.0
- Linux 18.04 | Clang 7.0.0, Clang 8.0.0, Clang 9.0.0
- Linux 18.04 | GCC 8.4.0, GCC 9.2.1

## Planned features
- Add new valid properties via TOML file
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
