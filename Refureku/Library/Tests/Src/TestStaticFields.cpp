#include "ForwardDeclaredClass.h"

#include "Generated/TestStaticFields.rfks.h"

int TestStaticFieldsClass::intField = 42;

int const TestStaticFieldsClass::constIntField = 314;

TestClass TestStaticFieldsClass::testClassField;

ForwardDeclaredClass* TestStaticFieldsClass::forwardDeclaredClassField = nullptr;

NonReflectedClass TestStaticFieldsClass::nonReflectedClassField;

ConstructionTrackedClass TestStaticFieldsClass::ctorTrackedClassField;

ConstructionTrackedClass const TestStaticFieldsClass::constCtorTrackedClassField;