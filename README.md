# Refureku
[![Build Status](https://travis-ci.com/Angelysse/Refureku.svg?branch=master)](https://travis-ci.com/Angelysse/Refureku)

## Presentation
Refureku is a powerful customizable C++ reflection library based on libclang.
It allows you to retrieve information on classes/structs, fields, methods and enums at runtime.

It is basically made of two parts:
- The metadata parser and generator, which will parse C++ source code and generate metadata, which will be injected back into source code using macros. This tool can either be built as a standalone executable or embed into a program (for example a game engine) depending on your needs. Last but not least, it is highly customizable (see the Customization section).
- The actual library which contain the framwork classes to access and manipulate reflected data at runtime.

## Features
TODO

## Classes overview
### Archetype
An archetype is a class wich contains information about a model type, like its name for example.
Each reflected class, struct and enum owns a unique archetype in the program. All C++ fundamental types also have their archetype.
The Class and Struct classes inherit from Archetype and contain additional data such as fields and methods. Class and Struct are not different from each other in the current library implementation, but are still separated to allow further development.

Consider the following header file, let's say Example.h:
```cpp
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
```

### Field / StaticField
Field and StaticField classes handle information about a class or struct reflected field.
Usage example:
```cpp
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

field->getData<int>(&instance);	//Get 0
field->setData(&instance, 42);	//Set 42 in instance
field->getData<int>(&instance);	//Get 42

//Find a static field by name - You can filter static fields with other arguments
rfk::StaticField const* staticField = classArchetype.getStaticField("exampleFloat");

staticField->getData<float>();	//Get 3.14
staticField->setData(42.42f);	//Set 42.42
staticField->getData<float>();	//Get 42.42
```

### Method / StaticMethod
Method and StaticMethod classes work just the same way as fields:
```cpp
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
f1->invoke(&instance);	//Note that we can call non const method on const instance

rfk::Method const* f2 = classArchetype.getMethod("returnNoParam");
f2->invoke<int>(&instance);	//Return 42

rfk::Method const* f3 = classArchetype.getMethod("returnWithParams");
f3->invoke<int>(&instance, 21.0f, 21.0f);	//Return 42

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
## Customization

## Setup

## License