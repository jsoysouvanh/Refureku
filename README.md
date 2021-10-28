<div align="center">

<img src="placeholder" width=400>

[![License: MIT](https://img.shields.io/github/license/jsoysouvanh/Refureku)](https://github.com/jsoysouvanh/Refureku/blob/master/LICENSE.md)
[![Latest Release](https://img.shields.io/github/v/tag/jsoysouvanh/refureku?label=release)](https://github.com/jsoysouvanh/Refureku/releases/latest)
[![Build & Tests](https://github.com/jsoysouvanh/Refureku/actions/workflows/build_and_tests.yml/badge.svg?branch=master)](https://github.com/jsoysouvanh/Refureku/actions/workflows/build_and_tests.yml)
[![codecov](https://codecov.io/gh/jsoysouvanh/Refureku/branch/master/graph/badge.svg?token=IG2AFIJI0M)](https://codecov.io/gh/jsoysouvanh/Refureku)
[![documentation](https://img.shields.io/badge/API-documentation-ff69b4)](https://jsoysouvanh.github.io/Refureku/)

</div>

# Overview
Refureku is a powerful C++17 runtime reflection dynamic library.  
It is split in 2 parts:
- The code generator is an executable, based on [Kodgen](https://github.com/jsoysouvanh/Kodgen). It handles the reflection code generation.
- The actual dynamic library that is linked to the target program using reflection.

**Check [the Wiki](https://github.com/jsoysouvanh/Refureku/wiki) to get started!**

## Features
- Reflect namespaces, classes, (static) methods, (static) fields, variables, functions, enums and enum values
- Support runtime loaded/unloaded dynamic library reflection
- Support class template reflection, as well as multiple inheritance
- Entities do not need to be included to be manipulated
- Reflected entities can be retrieved by name, id or predicate
- Read/write reflected fields/variables value
- Call reflected functions/methods
- Instantiate reflected classes without access to their static type
- Access dynamic type of an object instance through a base pointer/reference
- Powerful property system allowing to attach custom metadata to any entity
- Reflection metadata is regenerated only when a file has changed
- Customizable code generation

## Design goals
There are different approaches to add reflection to a C++ program:  
1. Write the reflected entities inside a macro that will parse the entity declaration and expand to the reflection metadata. This option completely alter the way to write entities (classes for example), and quickly becomes unreadble.
2. Declare entities first, and reflect each of them manually afterwards using macros. The code stays readable, however the user has to write everything twice, which is both time-consuming and error-prone.

Refureku uses a third approach that solves most of the above problems: code generation. The user annotates the entities they want to reflect, and when the project is compiled, reflected entities are parsed and c++ code is generated in separate files. The user just has to include the generated files in their own files, write a few macros, and done.  
This solution is not a pure win though. There is no simple and transparent way (yet) to add reflection to C++ and each approach comes with its own pros and cons.  

Refureku was initially developed with game engine development in mind, which greatly influenced the global design and architecture. The ability to generate and inject custom generated code without changing the project source files might be a reason to choose Refureku over another library.

# Examples
## Reflect a class

```cpp
//TestClass.h
#pragma once

#include "Generated/TestClass.rfkh.h"

class CLASS() TestClass
{
    FIELD()
    int _intField;

    METHOD()
    void testMethod();

    TestClass_GENERATED
};

File_TestClass_GENERATED
```

```cpp
//TestClass.cpp, or any source file being part of your project
#include "Generated/TestClass.rfks.h"
```

## Get a class metadata

```cpp
//From name
rfk::Class const* c = rfk::getDatabase().getFileLevelClassByName("TestClass");

//From static type
rfk::Class const& c2 = TestClass::staticGetArchetype();

//From reflected/unreflected type
rfk::Class const* c3 = rfk::getArchetype<TestClass>(); //nullptr if not reflected
```

## Get class metadata from base pointer

This feature is only available to classes that publicly derive from rfk::Object (#include <Refureku/Object.h>).
```cpp
TestClass instance;
rfk::Object const* instancePtr = &instance;

rfk::Struct const& archetype = instancePtr->getArchetype();
```

## Manipulate fields

```cpp
//Get field
rfk::Field const* field = TestClass::staticGetArchetype().getFieldByName("_intField");

TestClass instance;

//Read field value
int value = field->get<int>(instance);

//Write field value
field->set(instance, 3);
```

## Manipulate methods

```cpp
//Get method
rfk::Method const* method = TestClass::staticGetArchetype().getMethodByName("testMethod");

TestClass instance;

//Call method
//Without arguments
method->invoke(instance);

//With arguments and returned value
int returnedValue = method->invoke<int>(instance, 1, 2, 3);
```

## Instantiate a class

```cpp
rfk::Class const* c = rfk::getDatabase().getFileLevelClassByName("TestClass");

rfk::SharedPtr<TestClass> instance = c->makeSharedInstance<TestClass>(); //Instantiate from default ctor

//If TestClass has a base class, we can do
rfk::SharedPtr<BaseClass> instance2 = c->makeSharedInstance<BaseClass>();
```

It is also possible to instantiate a class with parameters, by providing a custom instantiator when declaring the class:
```cpp
//TestClass2.h
#pragma once

#include <Refureku/Properties/Instantiator.h>

#include "Generated/TestClass2.rfkh.h"

class CLASS() TestClass2 : public BaseClass
{
    METHOD(rfk::Instantiator)
    static rfk::SharedPtr<TestClass2> customInstantiator(int i)
    {
        //Use this if there is no custom deleter
        //return rfk::makeShared<TestClass2>();

        //Use this if you want to provide a custom deleter
        return rfk::SharedPtr<TestClass2>(new TestClass2(), [](TestClass2* ptr)
                {
                    delete ptr; //Simple delete for example simplicity
                });
    }

    TestClass2_GENERATED
};

File_TestClass2_GENERATED
```

```cpp
//TestClass2.cpp
#include "Generated/TestClass2.rfks.h"
```

```cpp
rfk::Class const* c2 = rfk::getDatabase().getFileLevelClassByName("TestClass2");

rfk::SharedPtr<BaseClass> instance3 = c2->makeSharedInstance<BaseClass>(42); //Call customInstantiator
```

## Create custom properties

```cpp
//ExampleProperty.h
#pragma once

#include <Refureku/Properties/PropertySettings.h>

#include "Generated/ExampleProperty.rfkh.h"

class CLASS(rfk::PropertySettings(rfk::EEntityKind::Struct | rfk::EEntityKind::Class))
    ExampleProperty : public rfk::Property
{
    public:
        int someData;

        ExampleProperty(int data):
            someData{data}
        {}

    ExampleProperty_GENERATED
};

File_ExampleProperty_GENERATED
```

```cpp
//ExampleProperty.cpp, or any source file being part of your project
#include "Generated/ExampleProperty.rfks.h"
```

Then, we can attach ExampleProperty to any reflected struct or class, as specified with the first argument of PropertySettings. Attaching the property to any other entity will trigger a compilation error with an explicit error message.
```cpp
//TestClass3.h
#pragma once

#include "ExampleProperty.h" //Include the custom property first
#include "Generated/TestClass3.rfkh.h"

class CLASS(ExampleProperty(42)) TestClass3
{
    TestClass3_GENERATED
};

File_TestClass3_GENERATED
```

```cpp
//TestClass3.cpp
#include "Generated/TestClass3.rfks.h"
```

## Read entity properties

```cpp
rfk::Class const* c = rfk::getDatabase().getFileLevelClassByName("TestClass3");

//From name
rfk::Property const* prop = c->getPropertyByName("ExampleProperty");

//From static type
ExampleProperty const* prop2 = c->getProperty<ExampleProperty>();
```

# Cross-platform compatibility
This library has been tested and is stable on the following configurations:
- Microsoft Windows Server | MSVC 19.29.30133.0
- Linux 20.04 | Clang 7.0.1, Clang 8.0.1, Clang 9.0.1, Clang 10.0.0, Clang 11.0.0
- Linux 20.04 | GNU 8.4.0, GNU 9.3.0, GNU 10.3.0, GNU 11.1.0
- Mac OS X 10.15.7 | AppleClang 12.0.0

# Known issues
- _(MSVC only)_ Issues when reflecting class templates with only template template parameters, see [this issue](https://developercommunity.visualstudio.com/t/Type-template-parameter-can-erroneously/1548997).
- Compilation error when reflect protected/private nested class template
- If a reflected namespace is shared among different modules, this namespace properties are not removed when one of the modules is unloaded.