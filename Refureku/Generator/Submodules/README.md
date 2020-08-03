
# Kodgen

[![Latest Release](https://badge.fury.io/gh/jsoysouvanh%2FKodgen.svg)](https://github.com/jsoysouvanh/Kodgen/releases/latest)
[![Build Status](https://travis-ci.com/jsoysouvanh/Kodgen.svg?branch=master)](https://travis-ci.com/jsoysouvanh/Kodgen)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/0de06d87df194f568e6f4c0f97c00fa8)](https://www.codacy.com/manual/jsoysouvanh/Kodgen?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=jsoysouvanh/Kodgen&amp;utm_campaign=Badge_Grade)

Kodgen is a C++17 library based on libclang. It provides tools to parse C++ source files, extract data from it, and generate files from the parsed data. The C++ entities parsed in the current implementation are namespaces, structs/classes, member fields, member methods, enums and enum values.

Snippets of this README contain a lot of customizable keywords. All of them will be annotated with a # followed by a number, so that you can find easily which setting to update to change them at the [end of this document](#referenced-settings).

Usage:
```cpp
//Some header file
#pragma once

#include "Generated/EntityMacros.h" //#1/#2

//Attach a macro on the entities to parse
//This macro is customizable, and not even necessary if setting #10 is used

//----------------------------v Mark a namespace for parsing
namespace ExampleNamespace Namespace()	//#3
{
    //------v Mark a class for parsing
    class Class() /* #4 */ ExampleClass
    {
        //----------v Mark an enum for parsing
        enum class Enum() /* #5 */ ExampleEnum
        {
            EnumValue1 = 0,
            EnumValue2 EnumValue() = 1  //#6
        };
        
        // -v Mark a field for parsing
        Field() //#7
        int i = 0;
 
        //--v Mark a method for parsing
        Method() //#8
        void ExampleMethod() {}
    };
}

```

```cpp
#include <Parsing/FileParser.h>
#include <CodeGen/FileGenerator.h>

//...

kodgen::FileParser	fileParser;
kodgen::FileGenerator	fileGenerator;

//Setup parser and generator settings if not done already
fileParser.parsingSettings.projectIncludeDirectories.emplace("Path/To/Include/Directory");

fileGenerator.outputDirectory = "Path/To/The/Output/Directory";
fileGenerator.toParseDirectories.emplace("Path/To/A/Directory/To/Parse");
fileGenerator.ignoredDirectories.emplace("Path/To/A/Directory/To/Ignore");
fileGenerator.ignoredDirectories.emplace("Path/To/The/Output/Directory"); //Don't parse generated files

kodgen::FileGenerationResult genResult = fileGenerator.generateFiles(fileParser, false);

if (genResult.completed)
{
    //Exploit result, check errors
}
else
{
    //Fatal error occured, check logs
}
```

## Index
- [Getting Started](#getting-started)
  - [Requirements](#requirements)
  - [Steps](#steps)
  - [Possible Issues](#possible-issues)
- [Workflow](#workflow)
- [Customization](#customization)
  - [Logger](#logger)
  - [Properties / PropertyRules](#properties--propertyrules)
    - [SimplePropertyRule](#simplepropertyrule)
    - [ComplexPropertyRule](#complexpropertyrule)
    - [Native properties](#native-properties)
  - [GeneratedCodeTemplate](#generatedcodetemplate)
  - [FileParser](#fileparser)
  - [FileGenerator](#filegenerator)
  - [Referenced Settings](#referenced-settings)
- [Cross-platform compatibility](#cross-platform-compatibility)
- [Known issues](#known-issues)
- [License](#license)

## Getting Started
### Requirements:

-   CMake 3.15.0+ (if you build the library from source).
-   A compatible compiler: MSVC Platform Toolset v141+ / GCC8.0.0+ / Clang 7.0.0+.

### Steps
**Pre-built binaries for Windows x64 are available [here](https://github.com/jsoysouvanh/Kodgen/releases). If you want to use those, you can skip to step 3.**

1.  Pull the repository
2.  Compile the library following these steps:
    -   At the root of the Kodgen project, open a terminal
        -   cmake -B Build/Release -DCMAKE_BUILD_TYPE=Release -G "\<Generator\>"
            
            > Most common generators include:
            > 
            > -   Visual Studio 15 2017 -> cmake -B Build/Release -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 15 2017" -A x64
            > -   Unix Makefiles
            > -   Ninja -> cmake -B Build/Release -DCMAKE_BUILD_TYPE=Release -G "Ninja"
            > -   Type cmake -G for more information
            
        -   cmake --build Build/Release --config Release --target Kodgen
    -   If you're compiling your project in debug mode, you will probably also need the debug version of Kodgen:
        -   cmake -B Build/Debug -DCMAKE_BUILD_TYPE=Debug -G "\<Generator\>"
        -   cmake --build Build/Debug --config Debug --target Kodgen
    -   You will find libclang.dll in Build/[Debug|Release]/Bin/ and Kodgen.lib in Build/[Debug|Release]/Lib/
        
        > **Note:** On multiple configuration generators such as Visual Studio or XCode, an additional Debug/Release folder is generated.
        
3.  Add necessary header directories to your project settings:
    - Kodgen header directory, located at /Kodgen/Include, or /Include if you downloaded the binaries.
    - Third party libraries header directory, located at /Kodgen/ThirdParty/Include, or /ThirdParty/Include if you downloaded the binaries.

4.  Add library directories to your projet settings:
    - The directory containing Kodgen.lib, located at /Build/[Debug|Release]/Lib/, or /Lib if you downloaded the binaries.
    - The directory containing third party libraries, located at /Kodgen/ThirdParty/x64/Static, or /ThirdParty/x64/Static if you downloaded the binaries.

5.  Link against:
    - Kodgen.lib. Make sure to use the Debug version of the library if you compile your project in Debug mode to prevent [this issue](#issue-1).
    - clang.lib

7.  Make sure you compile your project in C++17 or later.
8.  Compile!
9.  Before running your program, make sure that the libclang dynamic library is located next to your executable. You should find it at /Kodgen/ThirdParty/Libraries/x64/Shared (or /ThirdParty/Libraries/x64/Shared from binaries). If you encounter errors, see the [Possible issues section](#possible-issues). If it doesn't help, don't hesitate to [open a new issue](https://github.com/jsoysouvanh/Kodgen/issues).

### Possible issues
#### Issue 1
-   If you compile your program in debug mode, your compiler might complain about library / debug level mismatchs. In that case, make sure to compile the Kodgen library both in Debug and Release, and link against the debug version of the library when compiling your program in debug mode.
    
    > With CMake:
    ```cmake
     target_link_libraries(YourExecutable PRIVATE $<IF:$<CONFIG:Debug>,KodgenDebug,KodgenRelease>)
    ```

## Workflow
To begin with, let's talk a bit about how Kodgen works.  Code generation is based on 3 main classes: [FileParser](#fileparser), [GeneratedCodeTemplate](#generatedcodetemplate) and [FileGenerator](#filegenerator). When the code generation process starts (call to FileGenerator::generateFiles), source files are parsed by the FileParser and the retrieved data are passed to the FileGenerator. From that point, the FileGenerator will check for each parsed entity which GeneratedCodeTemplate to use. If a GeneratedCodeTemplate is found, code is generated for this entity, otherwise nothing is generated. To sum up:
 1. The FileParser extracts data from source file;
 2. The FileGenerator choses the right GeneratedCodeTemplate for a given parsed entity;
 3. The GeneratedCodeTemplate generates the code;

Each of those 3 classes contain a bunch of settings and overridable methods, which make the process flexible enough for a wide amount of use cases.

## Customization
### Logger
Kodgen defines a logger interface in Misc/ILogger.h. You can inherit from it, override the ILogger::log method, and provide an instance of your logger to the FileParser and the FileGenerator. If you don't want to bother with implementing your own logger, you can use kodgen::DefaultLogger (Misc/DefaultLogger.h).

```cpp
#pragma once

#include <Misc/ILogger.h>

class CustomLogger : public kodgen::ILogger
{
    public:
        virtual void log(std::string const& message, kodgen::ELogSeverity logSeverity) noexcept
        {
            //Your implementation
        }
};
```

```cpp
#include <Parsing/FileParser.h>
#include <CodeGen/FileGenerator.h>

#include "CustomLogger.h"

//...

kodgen::FileParser fileParser;
kodgen::FileGenerator fileGenerator;

CustomLogger logger; //Can replace CustomLogger by kodgen::DefaultLogger

//Provide your logger instance to the file parser and file generator
fileParser.logger = &logger;
fileGenerator.logger = &logger;

```

Providing a logger instance to the FileParser and the FileGenerator is not mandatory, however it is highly recommended if you want to keep track of what's happening. 

### Properties / PropertyRules
Properties are used to attach some metadata to a parsed entity. There are 2 kinds of properties:
  - Simple properties are properties which don't take any subproperty or argument. It could be a simple keyword.
  - Complex properties are properties which need additional data to make sense. A great example would be a Range property (that you could attach to a float field), to specify a minimum value and a maximum value for that field. Those minimum and maximum values are subproperties for the Range complex property.

For a property to be recognized, the FileParser contains a collection of rules (called PropertyRules) which implement a bunch of methods to check whether a property is valid or not.
1. When a property is parsed, the FileParser will immediately look for a PropertyRule which validates this property syntax by calling PropertyRule::isMainPropSyntaxValid on each registered PropertyRule. If one is found (PropertyRule::isMainPropSyntaxValid returned true), it is linked to this property, otherwise an error is generated.
2. Once all properties of an entity have been checked, each property will be checked again (using their respective linked property rule from step 1) to make sure all properties are compatible with each other. For example, we can check during this step that a property is not specified twice in a single entity. This is done by calling PropertyRule::isPropertyGroupValid. If at least one PropertyRule returned false, an error is generated.
3. After the entity has been completely parsed (properties of an entity are parsed before the entity itself), the FileParser proceeds to a final check by calling PropertyRule::isEntityValid, to make sure each property is compatible with the parsed entity. For example, we might want to make some properties available only for a given type (Range needs a float field for example). If at least one PropertyRule returned false, an error is generated.

To support new properties, we have to implement new property rules and [provide them to the FileParser](#fileparser).

#### SimplePropertyRule
To make a new valid simple property, we need to inherit from kodgen::SimplePropertyRule (Properties/SimplePropertyRule.h). In this new class, we **must** override the isMainPropSyntaxValid method. Both isPropertyGroupValid and isEntityValid return true by default, so it is not necessary to override them if you have no additional checks to perform.

The framework already provides some SimplePropertyRule implementations which do most of the work for you.

- [DefaultSimplePropertyRule](#defaultsimplepropertyrule)

##### DefaultSimplePropertyRule 
The DefaultSimplePropertyRule class does most of the job in most cases. It implements the isMainPropSyntaxValid method by checking that the property has a given name and that the parsed entity is of a given type. 
Let's say we want to make a property called "ExampleSimpleProperty" which is valid only when attached to a namespace, a struct or a class. We would write the following:

```cpp
#pragma once

#include <Properties/DefaultSimplePropertyRule.h>

class ExampleSimplePropertyRule : kodgen::DefaultSimplePropertyRule
{
    public:
        ExampleSimplePropertyRule() noexcept;
};
```

```cpp
#include "ExampleSimplePropertyRule.h"

ExampleSimplePropertyRule::ExampleSimplePropertyRule() noexcept:
    kodgen::DefaultSimplePropertyRule("ExampleSimpleProperty",
                                      {
                                          kodgen::EntityInfo::EType::Namespace,
                                          kodgen::EntityInfo::EType::Struct,
                                          kodgen::EntityInfo::EType::Class
                                      },
                                      "This is a description for this example property rule.")
{
}
```

And that's it! Once an instance of ExampleSimplePropertyRule will have been added to the FileParser, you will be able to write:

```cpp
#include "Generated/EntityMacros.h" //#1/#2

namespace ExampleNamespace Namespace(ExampleSimpleProperty) //#3
{
    class Class(ExampleSimpleProperty) /* #4 */ ExampleClass
    {
    };

    struct Struct(ExampleSimpleProperty) /* #9 */ ExampleStruct
    {
    };
}
```

You can still of course override isPropertyGroupValid and isEntityValid if you want to perform additional checks.

#### ComplexPropertyRule
To make a new valid complex property, we need to inherit from kodgen::ComplexPropertyRule (Properties/ComplexPropertyRule.h). In this new class, we **must** override the isMainPropSyntaxValid method, as well as the isSubPropSyntaxValid method. Both isPropertyGroupValid and isEntityValid return true by default, so it is not necessary to override them if you have no additional checks to perform.

The framework already provides some ComplexPropertyRule implementations which do most of the work for you.

- [DefaultComplexPropertyRule](#defaultcomplexpropertyrule)
- [FixedComplexPropertyRule](#fixedcomplexpropertyrule)

##### DefaultComplexPropertyRule 
Just like [DefaultSimplePropertyRule](#defaultsimplepropertyrule), DefaultComplexPropertyRule implements the isMainPropSyntaxValid method by checking that the property has a given name and that the parsed entity is of a given type. However, the isSubPropSyntaxValid method is not overriden, so you will have to do it yourself or use a higher level class to inherit from, like [FixedComplexPropertyRule](#fixedcomplexpropertyrule).
Let's say we want to make a property called "ExampleComplexProperty" which is valid only when attached to a method, and which has no subproperty constraints. We would write the following:

```cpp
#pragma once

#include <Properties/DefaultComplexPropertyRule.h>

class ExampleComplexPropertyRule : kodgen::DefaultComplexPropertyRule
{
    public:
        ExampleComplexPropertyRule() noexcept;

        virtual bool isSubPropSyntaxValid(std::string const& subProperty,
                                          uint8 subPropIndex,
                                          std::string& out_errorDescription) const noexcept override;
};
```

```cpp
#include "ExampleComplexPropertyRule.h"

ExampleComplexPropertyRule::ExampleComplexPropertyRule() noexcept:
    kodgen::DefaultComplexPropertyRule("ExampleComplexProperty",
                                      { kodgen::EntityInfo::EType::Method },
                                      "This is a description for this example property rule.")
{
}

bool ExampleComplexPropertyRule::isSubPropSyntaxValid(std::string const& subProperty,
                                          uint8 subPropIndex,
                                          std::string& out_errorDescription) const noexcept
{
    return true;
}
```

Once an instance of ExampleComplexPropertyRule will have been added to the FileParser, you will be able to write:

```cpp
#pragma once

#include "Generated/EntityMacros.h" //#1/#2

class Class() /* #4 */ ExampleClass
{
    public:
        Method(ExampleComplexPropertyRule("This is valid", 42, ThisToo)) //#7
        void ExampleMethod() {}
        
};
```

##### FixedComplexPropertyRule
A FixedComplexPropertyRule is a [DefaultComplexPropertyRule](#defaultcomplexpropertyrule) which is designed to accept a fixed number of typed subproperties. Supported types are int32, uint32, float and string. All type checks are already implemented, so it is really easy to create typed complex properties on top of that. Let's say we want to create a Range property which takes 2 floats (min and max) as subproperties, we could write:

```cpp
#pragma once

#include <Properties/FixedComplexPropertyRule.h>

class RangePropertyRule : public kodgen::FixedComplexPropertyRule
{
    public:
        RangePropertyRule() noexcept;
        
        virtual bool isPropertyGroupValid(kodgen::PropertyGroup const& propertyGroup, kodgen::uint8 propertyIndex, std::string& out_errorDescription) const noexcept override;
        virtual bool isEntityValid(kodgen::EntityInfo const& entity, kodgen::uint8 propertyIndex, std::string& out_errorDescription) const noexcept override;
};
```

```cpp
#include "Properties/RangePropertyRule.h"

#include <InfoStructures/FieldInfo.h>

RangePropertyRule::RangePropertyRule() noexcept:
    kodgen::FixedComplexPropertyRule("Range",
                                     {
                                         kodgen::EntityInfo::EType::Field
                                     },
                                     "Defines a float range between min and max.")
{
    subProperties.emplace_back(kodgen::ComplexPropertySubProperty::EType::Float, "min", "Minimum of the range.");
    subProperties.emplace_back(kodgen::ComplexPropertySubProperty::EType::Float, "max", "Maximum of the range.");
}

bool RangePropertyRule::isPropertyGroupValid(kodgen::PropertyGroup const& propertyGroup, kodgen::uint8 propertyIndex, std::string& out_errorDescription) const noexcept
{
    kodgen::ComplexProperty const& prop = propertyGroup.complexProperties[propertyIndex];

    //Parent implementation checks subprop type and count
    if (FixedComplexPropertyRule::isPropertyGroupValid(propertyGroup, propertyIndex, out_errorDescription))
    {
        //Make sure min < max
        if (std::stof(prop.subProperties[0]) > std::stof(prop.subProperties[1]))
        {
            out_errorDescription = "First subproperty (min) should be less or equal than second subproperty (max)";
	
            return false;
        }
    }

    return true;
}

bool RangePropertyRule::isEntityValid(kodgen::EntityInfo const& entity, kodgen::uint8 /* propertyIndex */, std::string& out_errorDescription) const noexcept
{
    //Range can apply only on floats
    if (static_cast<kodgen::FieldInfo const&>(entity).type.getCanonicalName(true) != "float")
    {
        out_errorDescription = "Range property can only apply on float fields.";
        
        return false;
    }

    return true;
}
```

#### Native properties
Kodgen implements some properties that it is possible to use out of the box.

- [ParseAllNested](#parseallnested)
- [GenCodeTemplate](#gencodetemplate)

##### ParseAllNested
ParseAllNested is a simple property which can be used on namespaces, structs and classes. Use it when you want to parse every **directly** nested entity, without having to necessarily specify the parsing macro again.

```cpp
#pragma once

#include "Generated/EntityMacros.h" //#1/#2

namespace ExampleNamespace Namespace(ParseAllNested) //#3
{
    class /* Even if Class() is not specified, this class is parsed */ NestedExampleClass
    {
        public:
            int i; //This field is NOT parsed as it is not **directly** inside a ParseAllNested tagged entity
    };
}

class Class(ParseAllNested) /* #4 */ ExampleClass
{
    public:
        //This field is parsed automatically
        int i;
        
        //This method is parsed automatically
        void someMethod() {}

        //This nested struct is parsed automatically
	struct NestedExampleStruct
	{
	};

        //This enum is reflected automatically
        enum class NestedExampleEnum
        {
            Value1 //Enum values are ALWAYS parsed automatically
        };
};
```

##### GenCodeTemplate
GenCodeTemplate is a complex property used to specify which [GeneratedCodeTemplate](#generatedcodetemplate) to use for a specific entity. Just pass the name of the GeneratedCodeTemplate as a subproperty (between ""), and the FileGenerator will use it to generate the code of the tagged entity.

```cpp
#pragma once

#include "Generated/EntityMacros.h" //#1/#2

class Class(GenCodeTemplate("ExampleGeneratedCodeTemplate")) /* #4 */
{
};
``` 

### GeneratedCodeTemplate
GeneratedCodeTemplate is the class which actually generates the code (or text or whatever) into a file.  It has a single overridable method called GeneratedCodeTemplate::generateCode, which takes a file and a parsed entity data as parameter.
To create your own code generation, inherit from GeneratedCodeTemplate and override the generateCode method.

```cpp
#pragma once

#include <CodeGen/GeneratedCodeTemplate.h>

class ExampleGeneratedCodeTemplate : public kodgen::GeneratedCodeTemplate
{
    public:
        virtual void generateCode(kodgen::GeneratedFile& generatedFile, kodgen::EntityInfo const& entityInfo) noexcept override;
};
```

```cpp
#include "ExampleGeneratedCodeTemplate.h"

using namespace kodgen;

void ExampleGeneratedCodeTemplate::generateCode(GeneratedFile& generatedFile, EntityInfo const& entityInfo) noexcept
{
    if (entityInfo.entityType == EntityInfo::EType::Namespace)
    {
        NamespaceInfo const& ni = static_cast<NamespaceInfo const&>(entityInfo);
        //Do whatever with the namespace data...
        //ex: generatedFile.writeLine("Namespace : " + ni.name);
    }
    else if (entityInfo.entityType == EntityInfo::EType::Class ||
             entityInfo.entityType == EntityInfo::EType::Struct)
    {
        StructClassInfo const& sci = static_cast<NamespaceInfo const&>(entityInfo);
        //Do whatever with struct/class data...
        //ex: generatedFile.writeLine("Class : " + sci.name);
    }
    //else if ...
}
```

### FileParser
Most of the settings available in the file parser are public variables, but it is cleaner to make a new class which inherits from kodgen::FileParser to have default settings for you own parser and to be able to override some methods if necessary.

```cpp
#pragma once

#include <Parsing/FileParser.h>

class ExampleFileParser : public kodgen::FileParser
{
    private:
        //Read the Properties section to understand those 2 fields
        ExampleSimplePropertyRule _simplePropertyRule;
        ExampleComplexPropertyRule _complexPropertyRule;

    protected:
        virtual void preParse(fs::path const& parseFile) noexcept override;
        virtual void postParse(fs::path const& parseFile, kodgen::FileParsingResult const& result) noexcept override;
};

    public:
        ExampleFileParser() noexcept;
```

The preParse method is called before a file is actually parsed by the FileParser, and the postParse method right after (whether the parsing successed or not). You can override them if you want to add a special behaviour at these key points of the program (like logs or whatever).

```cpp
#include "ExampleFileParser.h"

ExampleFileParser::ExampleFileParser() noexcept:
    kodgen::FileParser()
{
    //Here we can setup the file parser settings by accessing the parsingSettings variable
    
    //Should the FileParser immediately abort a file parsing when it encounters an error?
    parsingSettings.shouldAbortParsingOnFirstError = true;

    //Should the FileParser parse all entities whether they are tagged or not?
    parsingSettings.shouldParseAllEntities = false; //#10

    //Define the property macros for each entity
    parsingSettings.propertyParsingSettings.namespaceMacroName = "Namespace"; //#3
    //You can mark a namespace for parsing by writing
    //namespace some_namespace Namespace() {}

    parsingSettings.propertyParsingSettings.classMacroName = "Class";  //#4
    //You can mark a class for parsing by writing
    //class Class() SomeClass {};
    
    //Equivalent setting exists for structs, fields, methods, enums and enum values...

    //Ignore and remove any character before collecting properties
    parsingSettings.propertyParsingSettings.ignoredCharacters = {' '};
    //Ignoring ' ' will make ExampleClassMacro(a,    b, c) equivalent to ExampleClassMacro(a,b,c)

    //What character should be used to separate entity properties?
    parsingSettings.propertyParsingSettings.propertySeparator = ',';
    //class ExampleClassMacro(a, b, c) SomeClass {};
    //-------------------------^--^---------

    //Which delimiter to use to enclose subproperties?
    parsingSettings.propertyParsingSettings.subPropertyEnclosers[0] = '(';
    parsingSettings.propertyParsingSettings.subPropertyEnclosers[1] = ')';
    //class ExampleClassMacro( ExampleProperty(1, 2) ) SomeClass {};
    //----------------------------------------^----^-----

    //What character should be used to separate a property subproperties?
    parsingSettings.propertyParsingSettings.subPropertySeparator = ',';
    //class ExampleClassMacro( ExampleProperty(1, 2) ) SomeClass {};
    //------------------------------------------^------

    //Add property rules
    parsingSettings.propertyParsingSettings.simplePropertyRules.emplace_back(&_simplePropertyRule);
    parsingSettings.propertyParsingSettings.complexPropertyRules.emplace_back(&_complexPropertyRule);

    //Add path to project include directories. You might want to setup that somewhere else
    //parsingSettings.projectIncludeDirectories.emplace("Path/To/Include/Directory");
}

void ExampleFileParser::preParse() noexcept
{
    //Your implementation
}

void ExampleFileParser::postParse() noexcept
{
    //Your implementation
}
```

>**Note:** Adding the project include directories is mandatory. Indeed, the parser needs to know where it can find the files you include or it won't be able to resolve all symbols in a translation unit.

FileParser settings can also be loaded at runtime from a .toml file. A template of this toml file with all editable settings will be available in the repository, but it looks like this:

```ini
[FileParserSettings]
shouldAbortParsingOnFirstError = true
shouldParseAllEntities = false

projectIncludeDirectories = [ '''Path/To/Include/Directory''' ]

[FileParserSettings.Properties]
propertySeparator = ","
subPropertySeparator = ","
subPropertyStartEncloser = "("
subPropertyEndEncloser = ")"
ignoredCharacters = [ " " ]

namespaceMacroName = "Namespace"
classmacroName = "Class"
structMacroName = "Struct"
fieldMacroName = "Field"
methodMacroName = "Method"
enumMacroName = "Enum"
enumValueMacroName = "EnumVal"
``` 

> Note that paths are written between ''' '''.  This is the syntax to make raw strings in toml.
> On Windows, you can use both / or \ as path separator.

To load the settings, you just have to write:

```cpp
ExampleFileParser fileParser;

//The path must be either absolute or relative to the working directory
if (fileParser.loadSettings("Path/To/The/Toml"))
{
    //Settings loaded successfully
}
else
{
    //Failed to load settings
    //Failed to find the file or there is a syntax error
    //Make sure the file parser logger is setup for more info
}
```

### FileGenerator
Just like the FileParser class, FileGenerator settings are public, but to be able to override methods and to keep things clean, it is recommended that you create a new class.

```cpp
#pragma once

#include <CodeGen/FileGenerator.h>

class ExampleFileGenerator : public kodgen::FileGenerator
{
    private:
        ExampleGeneratedCodeTemplate _exampleGeneratedCodeTemplate;

    public:
        ExampleFileGenerator() noexcept;

        virtual void preGenerateFile() noexcept override;
        virtual void postGenerateFile() noexcept override;
        virtual void writeHeader(kodgen::GeneratedFile& file, FileParsingResult const& parsingResult) const noexcept override;
        virtual void writeFooter(kodgen::GeneratedFile& file, FileParsingResult const& parsingResult) const noexcept override;
};
```

```cpp
#include "ExampleFileGenerator.h"

ExampleFileGenerator::ExampleFileGenerator() noexcept:
    kodgen::FileGenerator()
{
    //Extension used by generated files
    generatedFilesExtension = ".extension.h";

    //Setup extensions to parse
    supportedExtensions.emplace(".h");
    supportedExtensions.emplace(".hpp");

    //Name of the file containing all macros
    entityMacrosFilename = "EntityMacros.h"; //#2

    //Add generated code templates to this generator
    addGeneratedCodeTemplate("ExampleTemplate", &_exampleGeneratedCodeTemplate);
    //Can now write namespace ExampleNamespace Namespace(GenCodeTemplate("ExampleTemplate")) {}

    //Use a given GeneratedCodeTemplate by default
    //when GenCodeTemplate complex property is not specified
    setDefaultGeneratedCodeTemplate(kodgen::EntityInfo::EType::Namespace, "ExampleTemplate");
    //Now if we write namespace ExampleNamespace Namespace() {}, ExampleTemplate will be used by default

    //The following settings are contained in the FileGenerator but it is likely that you will want to setup them from the outside
    //outputDirectory = "Path/To/The/Output/Directory" //#1
    //toParseFiles.emplace("Path/To/A/File/To/Parse");
    //toParseDirectories.emplace("Path/To/A/Directory/To/Parse");
    //ignoredFiles.emplace("Path/To/A/File/To/Ignore");
    //ignoredDirectories.emplace("Path/To/A/Directory/To/Ignore");
}

void ExampleFileGenerator::preGenerateFile() const noexcept
{
}

void ExampleFileGenerator::postGenerateFile() const noexcept
{
}

void ExampleFileGenerator::writeHeader(kodgen::GeneratedFile& file, FileParsingResult const& parsingResult) const noexcept
{
}

void ExampleFileGenerator::writeFooter(kodgen::GeneratedFile& file, FileParsingResult const& parsingResult) const noexcept
{
}
```

FileGenerator settings can also be loaded at runtime from a .toml file. A template of this toml file with all editable settings will be available in the repository, but it looks like this:

```ini
generatedFilesExtension = ".extension.h"
supportedExtensions	= [".h", ".hpp"]
entityMacrosFilename 	= "EntityMacros.h"

outputDirectory		= '''Path/To/Output/Dir'''
toParseDirectories	= [ '''Path/To/Directory/To/Parse''' ]
toParseFiles		= []
ignoredDirectories	= [ '''Path/To/Output/Dir''', '''Path/To/Directory/To/Ignore''' ]
ignoredFiles		= []
``` 

To load the settings, you just have to write:

```cpp
ExampleFileGenerator fileGenerator;

//The path must be either absolute or relative to the working directory
if (fileGenerator.loadSettings("Path/To/The/Toml"))
{
    //Settings loaded successfully
}
else
{
    //Failed to load settings
    //Failed to find the file or there is a syntax error
    //Make sure the file generator logger is setup for more info
}
```

All paths specified in the settings should be either absolute (best option), or relative to the working directory.

### Referenced Settings
#1: FileGenerator::outputDirectory
#2: FileGenerator::entityMacrosFilename
#3: FileParser::parsingSettings.propertyParsingSettings.namespaceMacroName 
#4: FileParser::parsingSettings.propertyParsingSettings.classMacroName 
#5: FileParser::parsingSettings.propertyParsingSettings.enumMacroName 
#6: FileParser::parsingSettings.propertyParsingSettings.enumValueMacroName
#7: FileParser::parsingSettings.propertyParsingSettings.fieldMacroName 
#8: FileParser::parsingSettings.propertyParsingSettings.methodMacroName 
#9: FileParser::parsingSettings.propertyParsingSettings.structMacroName 
#10: FileParser::parsingSettings.shouldParseAllEntities

## Cross-platform compatibility
This library has been tested and is stable on the following configurations:
- Windows Server version 1809 | MSVC 19.16.27035.0
- Linux 18.04 | Clang 7.0.0, Clang 8.0.0, Clang 9.0.0
- Linux 18.04 | GCC 8.4.0, GCC 9.2.1

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
