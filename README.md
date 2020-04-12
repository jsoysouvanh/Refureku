




# Refureku
[![Build Status](https://travis-ci.com/jsoysouvanh/Refureku.svg?branch=master)](https://travis-ci.com/jsoysouvanh/Refureku)

## Presentation
Refureku is a powerful customizable C++17 reflection library based on libclang.
It allows you to retrieve information on classes/structs, fields, methods and enums at runtime.

It is basically made of two parts:
- The metadata parser and generator, which will parse C++ source code and generate metadata, which will be injected back into source code using macros. This tool can either be built as a standalone executable or embeded in a program (for example a game engine) depending on your needs. Last but not least, it is highly customizable (see the Customization section).
- The actual library which contain the framework classes to access and manipulate reflected data at runtime.

## Features
- Reflect classes, structs, enums, member methods (static or not) and member fields (static or not)
- Support structs/classes with or without inheritance (multiple inheritance supported)
- Can look for a struct/class, enum, field or method by name, with additional filtering
- Method call with any arguments and any return type (public, protected, private, virtual, overriden, const methods callable on non const instances)
- Field get/set any data of any type (public, protected, private)
- Know at runtime if a reflected class inherits or is the base of another reflected class
- Arbitrary properties (like tags) on any entity (struct, class, field, method, enum, enum value)
- Reflection metadata is regenerated only when a file has changed
- Can instantiate any objects just from an archetype (which is obtainable by name or id)
- Know at compile-time if a struct/class is reflected or not (can be combined with if constexpr expression)

## Classes overview
### Archetype
An archetype is a class wich contains information about a model type, like its name for example.
Each reflected class, struct and enum owns a unique archetype in the program. All C++ fundamental types also have their archetype.
The Class and Struct classes inherit from Archetype and contain additional data such as fields and methods. Class and Struct are not different from each other in the current library implementation, but are still separated to allow further development.

Consider the following header file, let's say Example.h:
```cpp
#pragma once

#include "Generated/Example.rfk.h"

class RFKStruct() ExampleStruct
{
    RFKExampleStruct_GENERATED
};
class RFKClass() ExampleClass
{
    RFKExampleClass_GENERATED
};
enum class RFKEnum() ExampleEnum
{
};

RFKExampleEnum_GENERATED

```
To retrieve those archetypes, we can write the following:
```cpp
#include "Example.h"

//...

rfk::Struct const& exampleStructArchetype = ExampleStruct::staticGetArchetype();
rfk::Class const& exampleClassArchetype = ExampleClass::staticGetArchetype();
rfk::Enum const* exampleEnumArchetype = rfk::getEnum<ExampleEnum>();

//Iterate over fields
for (rfk::Field const& field : exampleClassArchetype.fields)
    //Do something

//Iterate over methods
for (rfk::Method const& method : exampleClassArchetype.method)
    //Do something

//Iterate over enum values
for (rfk::EnumValue const& enumValue : exampleEnumArchetype->values)
    //Do something
```

### Field / StaticField
Field and StaticField classes handle information about a class or struct reflected field.
Usage example:
```cpp
#pragma once

#include "Generated/ExampleClass.rfk.h"

class RFKClass() ExampleClass
{
    protected:
        RFKField()
        static float exampleFloat = 3.14f;

    public:
        RFKField()
        int exampleInt = 0;

    RFKExampleClass_GENERATED
}
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

### Method / StaticMethod
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

    RFKExampleClass_GENERATED
}
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
f2->invoke(&instance);  //If you don't care about the return value, you can omit template
f2->invoke<int>(&instance); //Return 42

rfk::Method const* f3 = classArchetype.getMethod("returnWithParams");
f3->invoke<int>(&instance, 21.0f, 21.0f);   //Return 42

//It works exactly the same for static methods, but we don't need an instance
rfk::StaticMethod const* sf1 = classArchetype.getStaticMethod("staticNoReturnNoParam");
sf1->invoke();
```

### Database
The Database class regroups all reflection data in a single place. It can provide us Archetype from a string or an id.

```cpp
#include <TypeInfo/Database.h>

//...

rfk::Class const* classArchetype = rfk::Database::getClass("ExampleClass");
void* classInstance = classArchetype->makeInstance();

//Do whatever you want with your class
classArchetype->getField("exampleInt")->getData<int>(classInstance);
classArchetype->getMethod("noReturnNoParam")->invoke(classInstance);

//Don't forget to delete your instance at the end, there is no memory auto managing
delete classInstance;

```

## Properties
Properties are just like tags (strings) that can be attached to any entity (Struct, Class, Enum, Field, Method, EnumValue), through the reflection macro. These properties are following a syntax which is handled by the parser using regex (see the Customization section), so that we know what is permitted to write and what's not. These rules also prevent unintentional syntax errors. Each property can also accept subproperties (or arguments).

It could look like this:
```cpp
#pragma once

#include "Generated/Example.rfk.h"

class RFKClass(CustomSimpleProperty, CustomComplexProperty[SubProp1, SubProp2])
    ExampleClass
{
    RFKExampleClass_GENERATED
};

enum class RFKEnum(EnumProp) ExampleEnum
{
    EnumValue1 = 0,
    EnumValue2 RFKEnumVal(EnumValueProp) = 1
};

RFKExampleEnum_GENERATED
```

And we can retrieve properties like so:
```cpp
#include "Example.h"

//...

rfk::Class const& classArchetype = ExampleClass::staticGetArchetype();

//Iterate over all simple properties
for (std::string const& simpleProp : classArchetype.properties.simpleProperty)
    //Do something

//Iterate over all complex properties
for (auto& [complexProp, subProp] : classArchetype.properties.complexProperties)
    //Do something

//Iterate over all subproperties of a chosen complex property
auto range = classArchetype.properties.complexProperties.equal_range("CustomComplexProperty");
for (auto it = range.first; it != range.second; it++)
    //Do something

//Check if an entity has a specific simple or complex property
classArchetype.properties.hasProperty("CustomSimpleProperty");  //true
classArchetype.properties.hasProperty("CustomComplexProperty", "SubProp1"); //true
classArchetype.properties.hasProperty("CustomComplexProperty", "SubProp2"); //true

```

It can be really useful when you want to adapt behaviors depending on specific properties (for example, a game engine editor).

## Customization
Before talking about how to customize the code generation, let's talk a bit about how it works.   
There are 3 main classes which make the code generation possible: the FileParser, the GeneratedCodeTemplate and the FileGenerator. When the code generation process starts, a source file is parsed by the FileParser and the retrieved data are passed to the FileGenerator. From that point, the FileGenerator will check for each parsed archetype (i.e each struct, class or enum) which GeneratedCodeTemplate to use. File are then generated by the relevant GeneratedCodeTemplate. To sum up:
 1. The FileParser extracts data from source file;
 2. The FileGenerator choses the right GeneratedCodeTemplate for a given parsed archetype;
 3. The GeneratedCodeTemplate generates the file & code;

Each of those 3 classes contain overridable methods and modifiable fields, and this is where user customization starts.
### FileParser
The parser is probably the class which you will want to change at first to modify the global syntax for reflection. If the default Refureku syntax is fine, you can reuse the rfk::FileParser as it is, but let's make a new one to see what we can tweak:
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

    //First of all, macro appearance !
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

### FileGenerator
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

### GeneratedCodeTemplate
GeneratedCodeTemplate class is defining the code to generate for a given set of data. An implementation is already provided in Refureku and it should be used as it is.

### Putting all 3 together
Once you've setup the above 3 classes (actually 2, you should definitely use Refureku GeneratedCodeTemplate implementation), making everything work is pretty straight forward.
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
        //Probably bad input directory
    }

    return EXIT_SUCCESS;
}
```

All this process can be setup in a standalone executable which will be called before you code base is compiled (you can use CMake add_custom_target(...) and add_dependencies(...), or MSVC Build events), but as you could see, it could easily be integrated in an application as well.

## Getting started
Requirements:
- CMake 3.15.0+
- C++17+
- A compatible compiler (see Cross-platform compatibility section).

1. Pull the repository
2. Update the RefurekuGenerator (Refureku/Generator/Source/main.cpp) according to your needs. You will probably want to at least change the "includeDirectory" variable in the parseAndGenerate() method.
3. Compile the library and the generator following these steps:

- At the root of the Refureku project, open a terminal
- Type:

> \> mkdir Build   
> \> cd Build   
> \> cmake -G \<Generator\> -A x64 .\.
>> Most common generators include:
>> - Visual Studio 2017	-> cmake -G "Visual Studio 15 2017" -A x64 .\.
>> - Makefile -> cmake -G "Unix Makefiles" -A x64 .\.
>> - Ninja
>> - Type cmake -G for more information

> \> cmake --build . --target RefurekuGenerator Refureku --config Release --parallel 8

4. Link against Refureku.lib, and don't forget to add the Refureku headers directory to your project included header directories (Refureku/Library/Include)
5. Make a pre-build custom event (VS) or a custom target + dependency (CMake) to run the Generator before building your project, with your working directory as the first argument.
6. Compile your project: the generator should run before your project is built.

## Cross-platform compatibility
This library has been tested and is stable with the following configurations:
- Windows | MSVC 2019 16.5.2
- Linux | Clang 7.0.0, Clang 8.0.0, Clang 9.0.0
- Linux | GCC 8.4.0, GCC 9.2.1

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
