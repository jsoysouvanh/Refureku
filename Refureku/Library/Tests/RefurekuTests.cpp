#include <iostream>
#include <cfloat> //FLT_EPSILON
#include <cmath>  //std::fabs

#include <Refureku/Refureku.h>

#include "AB.h"
#include "ExampleClass.h"
#include "TestPropertyUsage.h"
#include "ThirdPartyEnumReflectionCode.h"
#include "CustomString.h"

#define TEST(...) if (!(__VA_ARGS__)) { std::cerr << "Test failed (" << __LINE__ << "): " << #__VA_ARGS__ << std::endl; exit(EXIT_FAILURE); }

bool approximatelyEqual(float value1, float value2, float epsilon = FLT_EPSILON)
{
	return std::fabs(value1 - value2) <= epsilon;
}

void outerEntities()
{
	TEST(rfk::Database::getNamespace("namespace3")->outerEntity == nullptr);
	TEST(rfk::Database::getNamespace("namespace4")->getNamespace("namespace4_nested")->outerEntity == rfk::Database::getNamespace("namespace4"));
	TEST(rfk::Database::getNamespace("namespace3")->getClass("AnotherClassInNamespace3")->outerEntity == rfk::Database::getNamespace("namespace3"));
	TEST(namespace3::ExampleClass::staticGetArchetype().getNestedStruct("NestedExampleStruct")->outerEntity == rfk::Database::getNamespace("namespace3")->getClass("ExampleClass"));
	TEST(rfk::Database::getNamespace("test1")->getNamespace("test2")->getEnum("NestedEnumInNestedNamespace")->outerEntity == rfk::Database::getNamespace("test1")->getNamespace("test2"));
	TEST(rfk::Database::getNamespace("test1")->getNamespace("test2")->getEnum("NestedEnumInNestedNamespace")->getEnumValue("SomeValue")->outerEntity == rfk::Database::getNamespace("test1")->getNamespace("test2")->getEnum("NestedEnumInNestedNamespace"));
	TEST(ExampleStruct::staticGetArchetype().getStaticField("staticInt")->outerEntity == &ExampleStruct::staticGetArchetype());
	TEST(ExampleStruct::staticGetArchetype().getField("i")->outerEntity == &ExampleStruct::staticGetArchetype());
	TEST(ExampleStruct::staticGetArchetype().getStaticMethod("staticMethod")->outerEntity == &ExampleStruct::staticGetArchetype());
	TEST(rfk::Database::getFunction("function1")->outerEntity == nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getFunction("function1")->outerEntity == rfk::Database::getNamespace("namespace3"));
	TEST(rfk::Database::getVariable("variableInsideGlobalScope")->outerEntity == nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getVariable("variableInsideNamespace")->outerEntity == rfk::Database::getNamespace("namespace3"));
}

void namespaces()
{
	TEST(rfk::Database::getNamespace("namespace3") != nullptr);
	TEST(rfk::Database::getNamespace(rfk::Database::getNamespace("namespace3")->id) != nullptr);
	TEST(rfk::Database::getNamespace("namespace4") != nullptr);
	TEST(rfk::Database::getNamespace("namespace4_nested") == nullptr);
	TEST(rfk::Database::getNamespace("namespace4")->getNamespace("namespace4_nested") != nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getClass("AnotherClassInNamespace3") != nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getClass("OtherClass") != nullptr);
	TEST(rfk::Database::getNamespace("test1")->getNamespace("test2")->getEnum("NestedEnumInNestedNamespace")->getEnumValue("SomeValue")->value == 42u);
	
	TEST(rfk::Database::getNamespace("namespace3")->getVariable("variableInsideNamespace")->getData<int>() == 42);
	TEST(rfk::Database::getNamespace("namespace3")->getVariable("variableInsideNamespace", rfk::EVarFlags::Static) == nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getVariable("variableInsideGlobalScope") == nullptr);

	rfk::Database::getNamespace("namespace3")->getFunction("functionInsideNamespace", rfk::EFunctionFlags::Inline)->invoke(1);
	rfk::Database::getNamespace("namespace3")->getFunction("functionInsideNamespace", rfk::EFunctionFlags::Default)->invoke(2);
	TEST(rfk::Database::getNamespace("namespace3")->getFunction("functionInsideNamespace", rfk::EFunctionFlags::Static) == nullptr);

	TEST(rfk::Database::getNamespace("namespace3")->getFunction<int(int)>("function1")->rInvoke<int>(1) == 1);
	TEST(rfk::Database::getNamespace("namespace3")->getFunction<int(int, int)>("function1")->rInvoke<int>(1, 2) == 3);
	TEST(rfk::Database::getNamespace("namespace3")->getFunction<void(int, int)>("function1") == nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getFunction<int()>("function1") == nullptr);

	//By predicate
	TEST(rfk::Database::getNamespace("namespace3")->getNamespace([](rfk::Namespace const*) { return true; }) == nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getArchetype([](rfk::Archetype const* a) { return a->memorySize == sizeof(namespace3::ParentClass); }) != nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getStruct([](rfk::Struct const*) { return true; }) == nullptr );
	TEST(rfk::Database::getNamespace("namespace3")->getClass([](rfk::Class const* c) { return c->name == "AnotherClassInNamespace3"; }) != nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getEnum([](rfk::Enum const* e) { return e->values.size() == 5; }) != nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getVariable([](rfk::Variable const* v) { return v->getData<int>() == 42; }) != nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getFunction([](rfk::Function const* f) { return f->returnType == rfk::Type::getType<int>() && f->parameters.size() == 2; }) != nullptr);
}

void classes()
{
	TEST(rfk::Database::getClass("ParentParentParentClass") == nullptr);
	TEST(rfk::Database::getClass(namespace3::ExampleClass::staticGetArchetype().id) != nullptr);
	TEST(rfk::Database::getNamespace("namespace2")->getClass("ParentParentClass") != nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getClass("OtherClass") != nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getClass("ParentClass") != nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getClass("ParentClass2") != nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getClass("ExampleClass") != nullptr);
	TEST(rfk::Database::getEnum("ExampleClass") == nullptr);
	TEST(rfk::Database::getStruct("ExampleClass") == nullptr);

	//Nested classes
	TEST(rfk::Database::getNamespace("namespace3")->getClass("ExampleClass")->getNestedClass("NestedExampleClass") != nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getClass("ExampleClass")->getNestedClass("NestedExampleClass", rfk::EAccessSpecifier::Private) != nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getClass("ExampleClass")->getNestedClass("NestedExampleClass", rfk::EAccessSpecifier::Public) == nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getClass("ExampleClass")->getNestedClass("NestedExampleClass")->getField("i") != nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getClass("ExampleClass")->getNestedStruct("NestedExampleClass") == nullptr);
}

void structs()
{
	TEST(rfk::Database::getStruct("ExampleStruct") != nullptr);
	TEST(rfk::Database::getStruct(ExampleStruct::staticGetArchetype().id) != nullptr);
	TEST(rfk::Database::getEnum("ExampleStruct") == nullptr);
	TEST(rfk::Database::getClass("ExampleStruct") == nullptr);

	ExampleStruct es;

	TEST(ExampleStruct::staticGetArchetype().getStaticField("staticInt")->getData<int>() == 123);
	TEST(ExampleStruct::staticGetArchetype().getField("i")->getData<int>(&es) == 2);
	
	ExampleStruct::staticGetArchetype().getStaticMethod("staticMethod")->invoke();
	ExampleStruct::staticGetArchetype().getMethod("method")->invoke(&es, 1, 42.0f);

	try
	{
		ExampleStruct::staticGetArchetype().getMethod<void(int, float)>("method")->checkedInvoke(&es, 1, 2.0f);		//This passes
		ExampleStruct::staticGetArchetype().getMethod<void(int, float)>("method")->checkedInvoke(&es, "a", "aa");	//This throws
		TEST(false);	//Never reach this line
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
	}

	TEST(ExampleStruct::staticGetArchetype().getMethod<void(int, int)>("method") == nullptr);	//Bad parameter type
	TEST(ExampleStruct::staticGetArchetype().getMethod<int(int, float)>("method") == nullptr);	//Bad return type
	TEST(ExampleStruct::staticGetArchetype().getMethod<void(int, float)>("method") != nullptr);
	TEST(ExampleStruct::staticGetArchetype().getStaticMethod<void(int, float)>("method") == nullptr);

	//Nested structs
	TEST(rfk::Database::getNamespace("namespace3")->getClass("ExampleClass")->getNestedStruct("NestedExampleStruct") != nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getClass("ExampleClass")->getNestedStruct("NestedExampleStruct", rfk::EAccessSpecifier::Protected) != nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getClass("ExampleClass")->getNestedStruct("NestedExampleStruct", rfk::EAccessSpecifier::Public) == nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getClass("ExampleClass")->getNestedStruct("NestedExampleStruct")->getMethod<void()>("foo") != nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getClass("ExampleClass")->getNestedClass("NestedExampleStruct") == nullptr);

	//Get struct content by predicate
	TEST(ExampleStruct::staticGetArchetype().getNestedArchetype([](rfk::Archetype const*) { return true; }) == nullptr);
	TEST(ExampleStruct::staticGetArchetype().getNestedStruct([](rfk::Struct const*) { return true; }) == nullptr);
	TEST(ExampleStruct::staticGetArchetype().getNestedClass([](rfk::Class const*) { return true; }) == nullptr);
	TEST(ExampleStruct::staticGetArchetype().getNestedEnum([](rfk::Enum const*) { return true; }) == nullptr);
	TEST(ExampleStruct::staticGetArchetype().getField([](rfk::Field const* f) { return f->type == rfk::Type::getType<int>(); }) != nullptr);
	TEST(ExampleStruct::staticGetArchetype().getFields([](rfk::Field const*) { return true; }, true).size() == 1u);
	TEST(ExampleStruct::staticGetArchetype().getStaticField([](rfk::StaticField const* sf) { return sf->type == rfk::Type::getType<int>(); }) != nullptr);
	TEST(ExampleStruct::staticGetArchetype().getStaticFields([](rfk::StaticField const*) { return true; }, true).size() == 1u);
	TEST(ExampleStruct::staticGetArchetype().getMethod([](rfk::Method const* m) { return m->parameters.size() == 2u; }, true) != nullptr);
	TEST(ExampleStruct::staticGetArchetype().getMethods([](rfk::Method const*) { return true; }).size() == 1u);
	TEST(ExampleStruct::staticGetArchetype().getStaticMethod([](rfk::StaticMethod const* sm) { return sm->parameters.size() == 0u; }) != nullptr);
	TEST(ExampleStruct::staticGetArchetype().getStaticMethods([](rfk::StaticMethod const* sm) { return sm->returnType == rfk::Type::getType<void>(); }).size() == 1u);
}

void enums()
{
	TEST(rfk::Database::getEnum("UnexistantEnum") == nullptr);

	TEST(rfk::Database::getEnum(rfk::getEnum<namespace3::ExampleEnum>()->id) != nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getEnum("ExampleEnum") != nullptr);
	TEST(rfk::Database::getClass("ExampleEnum") == nullptr);
	TEST(rfk::Database::getStruct("ExampleEnum") == nullptr);

	rfk::Enum const* e = rfk::Database::getNamespace("namespace3")->getEnum("ExampleEnum");
	TEST(e != nullptr);

	TEST(e->memorySize == sizeof(uint8_t));
	TEST(e->name == "ExampleEnum");
	TEST(e->getEnumValue("ExampleValue1")->value == 1 << 0);
	TEST(e->getEnumValue("ExampleValue2")->value == 1 << 1);
	TEST(e->getEnumValue("ExampleValue3")->value == 1 << 2);
	TEST(e->getEnumValue("ExampleValue4")->value == 1 << 3);
	TEST(e->getEnumValue("ExampleValue5")->value == 1 << 3);
	TEST(e->getEnumValue(1 << 0)->name == "ExampleValue1");
	TEST(e->getEnumValue(1 << 1)->name == "ExampleValue2");
	TEST(e->getEnumValue(1 << 2)->name == "ExampleValue3");
	TEST(e->getEnumValues(1 << 3).size() == 2);
	TEST(e->getEnumValue("ExampleValue1") == rfk::Database::getEnumValue(e->getEnumValue("ExampleValue1")->id));

	//By predicate
	TEST(e->getEnumValue([](rfk::EnumValue const* v){ return v->value == 1 << 3 && v->name == "ExampleValue4"; }) != nullptr);
	TEST(e->getEnumValues([](rfk::EnumValue const* v){ return v->value == 10; }).empty());

	//Nested enums
	TEST(rfk::Database::getNamespace("namespace3")->getClass("ExampleClass")->getNestedEnum("NestedExampleEnum")->getEnumValue("Value1")->value == 0);

	TEST(rfk::getEnum<C::PublicNestedEnum>() != nullptr);
	TEST(C::staticGetArchetype().getNestedEnum("PrivateNestedEnum") != nullptr);
	TEST(C::staticGetArchetype().getNestedClass("PrivateNestedClass")->getNestedEnum("PrivateNestedEnum") != nullptr);

	rfk::Enum const* nestedEnum = C::staticGetArchetype().getNestedEnum("PrivateNestedEnum");
	TEST(rfk::Database::getEnum(nestedEnum->id) == nestedEnum);

	//Normal enum (no enum class)
	TEST(rfk::Database::getEnum("EThisIsANormalEnum") != nullptr);

	//Underlying type
	TEST(rfk::Database::getEnum("EThisIsANormalEnum")->underlyingType.archetype->name == "int");
}

void methods()
{
	//ParentParentClass
	rfk::Class const& ppc = namespace2::ParentParentClass::staticGetArchetype();

	TEST(ppc.getMethod("SomeMethod") == nullptr);

	//ParentClass
	namespace3::ParentClass	p;
	rfk::Class const&		pc = namespace3::ParentClass::staticGetArchetype();

	pc.getMethod("parentClassMethod1")->invoke(&p);

	rfk::Method const* pc_method1 = pc.getMethod("method1", rfk::EMethodFlags::Public | rfk::EMethodFlags::Virtual | rfk::EMethodFlags::Const);
	TEST(pc_method1->checkedRInvoke<int>(&p) == 1);
	TEST(pc.getMethod("method1", rfk::EMethodFlags::Protected | rfk::EMethodFlags::Virtual | rfk::EMethodFlags::Const) == nullptr);
	TEST(pc_method1 == rfk::Database::getMethod(pc_method1->id));

	//ExampleClass
	namespace3::ExampleClass	e;
	rfk::Class const&			ec = namespace3::ExampleClass::staticGetArchetype();

	rfk::Method const*			ec_method1 = ec.getMethod("method1", rfk::EMethodFlags::Public | rfk::EMethodFlags::Override | rfk::EMethodFlags::Final | rfk::EMethodFlags::Virtual);
	TEST(ec_method1->rInvoke<int>(&e) != 1);
	TEST(ec_method1->rInvoke<int>(&e) == 2);

	rfk::Method const* ec_method2 = ec.getMethod("method2", rfk::EMethodFlags::Protected | rfk::EMethodFlags::Const);
	ec_method2->invoke(&e);

	rfk::Method const* ec_method3int = ec.getMethod("method3", rfk::EMethodFlags::Protected);
	TEST(ec_method3int->rInvoke<int>(&e) == 42);

	rfk::Method const* ec_method3float	= ec.getMethod("method3", rfk::EMethodFlags::Private);
	
	//Handle functions when they use an incomplete type (forward declared type)
	rfk::Method const* ec_methodWithForwardDeclaredParam = ec.getMethod<void(D*)>("methodWithForwardDeclaredParam");
	ec_methodWithForwardDeclaredParam->invoke(&e, nullptr);

	rfk::Method const* ec_methodWithClassParam = ec.getMethod("methodWithClassParam");
	ec_methodWithClassParam->invoke(&e, nullptr);

	#if REFUREKU_DEBUG

	try
	{
		ec_method3float->invoke(&e);	// <- Bad number of arguments
		TEST(false);	//Should not reach this line, throw here ^ in DEBUG only
	}
	catch (std::exception const&)
	{
		ec_method3float->invoke(&e, 7);	// <- Call with correct arguments count
	}

	#else

	ec_method3float->invoke(&e);	// <- This should not throw in release eventhough bad arguments count
	ec_method3float->invoke(&e, 7);

	#endif

	rfk::Method const*	ec_method4	= ec.getMethod("method4", rfk::EMethodFlags::Public);
	TEST(ec_method4->rInvoke<unsigned long long>(&e, nullptr) == 0u);

	try
	{
		ec_method4->checkedRInvoke<unsigned long long>(&e, nullptr, 1);		// <- Bad number of arguments
		TEST(false);	//Should not reach this line, throw here ^
	}
	catch (std::exception const&)
	{}

	try
	{
		ec_method4->checkedInvoke<unsigned long long>(&e, 1);		// <- Bad argument type
		TEST(false);	//Should not reach this line, throw here ^
	}
	catch (std::exception const&)
	{}

	//No lookup in parent classes
	TEST(ec.getMethod("parentClassMethod1", rfk::EMethodFlags::Private, false) == nullptr);

	//Lookup in parent classes
	rfk::Method const*	ec_parentClassMethod1 = ec.getMethod("parentClassMethod1", rfk::EMethodFlags::Private, true);
	TEST(ec_parentClassMethod1 != nullptr);

	ec_parentClassMethod1->invoke(&e);

	//Check const / non-const
	TEST(ec.getMethod("constMethod", rfk::EMethodFlags::Const) != nullptr);
	TEST(ec.getMethod<void(int)>("constMethod") == nullptr);
	TEST(ec.getMethod<void(int) const>("constMethod") != nullptr);
	TEST(ec.getMethod<void(int) const>("constMethod", rfk::EMethodFlags::Const) != nullptr);

	TEST(ec.getMethod("method3") != nullptr);			//We don't know if it's the const or non-const overload
	TEST(ec.getMethod<int(int)>("method3")->rInvoke<int>(&e, 1) == 1);	//non-const
	TEST(ec.getMethod<int(int) const>("method3")->rInvoke<int>(&e, 1) == 2);	//const
	TEST(ec.getMethod("method3", rfk::EMethodFlags::Const)->rInvoke<int>(&e, 1) == 2);	//const
	TEST(ec.getMethod<int(int) const>("method3", rfk::EMethodFlags::Const)->rInvoke<int>(&e, 1) == 2);	//const
	TEST(ec.getMethod<int(int)>("method3", rfk::EMethodFlags::Const) == nullptr);	//Method signature is non const and flag is const -> contradiction

	//Check methods non-const method call throw when instance is const
	namespace3::ParentClass	const constP;

	try
	{
		pc.getMethod("parentClassMethod1")->invoke(&constP);
		TEST(false);
	}
	catch (rfk::ConstViolation const&)
	{
	}
}

void staticMethods()
{
	//ParentClass
	rfk::Class const& pc = namespace3::ParentClass::staticGetArchetype();

	TEST(pc.getStaticMethod("method1") == nullptr);	//Not static

	//ExampleClass
	rfk::Class const& ec = namespace3::ExampleClass::staticGetArchetype();

	ec.getStaticMethod("staticMethod1", rfk::EMethodFlags::Private)->invoke();

	TEST(ec.getStaticMethod("staticMethod1") == rfk::Database::getStaticMethod(ec.getStaticMethod("staticMethod1")->id));
	TEST(ec.getStaticMethod("staticMethod2", rfk::EMethodFlags::Private)->rInvoke<int>() == 2);

	TEST(ec.getStaticMethod("staticMethod3", rfk::EMethodFlags::Public) == nullptr);

	TEST(ec.getStaticMethods("staticMethod3").size() == 2u);

	ec.getStaticMethod("staticMethod3", rfk::EMethodFlags::Protected)->invoke("This is a test, and let's try to make sure it works even when it's long");
	TEST(ec.getStaticMethod("staticMethod3", rfk::EMethodFlags::Private)->rInvoke<int>(1, 2) == 3);
}

void fields()
{
	//ParentParentClass
	namespace2::ParentParentClass	pp;
	rfk::Class const&				ppc = namespace2::ParentParentClass::staticGetArchetype();

	TEST(ppc.getField("pFloat") == nullptr);
	TEST(ppc.getField("ppFloat", rfk::EFieldFlags::Public) == nullptr);
	TEST(static_cast<int>(ppc.getField("ppFloat", rfk::EFieldFlags::Private)->getData<float>(&pp)) == 123456);
	TEST(ppc.getField("ppFloat", rfk::EFieldFlags::Private) == rfk::Database::getField(ppc.getField("ppFloat", rfk::EFieldFlags::Private)->id));

	ppc.getField("ppFloat", rfk::EFieldFlags::Private)->setData(&pp, 3.14f);

	TEST(static_cast<int>(ppc.getField("ppFloat", rfk::EFieldFlags::Private)->getData<float>(&pp)) == 3);

	//ParentClass
	namespace3::ParentClass	p;
	rfk::Class const&		pc = namespace3::ParentClass::staticGetArchetype();

	TEST(pc.getField("ppFloat", rfk::EFieldFlags::Private, false) == nullptr);
	TEST(static_cast<int>(pc.getField("ppFloat", rfk::EFieldFlags::Private, true)->getData<float>(&p)) == 123456);

	TEST(pc.getField("pInt64")->getData<unsigned long long>(&p) == 666u);
	pc.getField("pInt64")->getData<unsigned long long&>(&p) = 642u;
	TEST(pc.getField("pInt64")->getData<unsigned long long>(&p) == 642u);

	//ExampleClass
	namespace3::ExampleClass	exampleClassInstance;
	rfk::Class const&			exampleClass = namespace3::ExampleClass::staticGetArchetype();

	TEST(exampleClass.getField("ppFloat", rfk::EFieldFlags::Private, false) == nullptr);
	TEST(static_cast<int>(exampleClass.getField("ppFloat", rfk::EFieldFlags::Private, true)->getData<float>(&exampleClassInstance)) == 123456);

	TEST(exampleClass.getField("pInt64", rfk::EFieldFlags::Default, true)->getData<unsigned long long>(&exampleClassInstance) == 666u);
	exampleClass.getField("pInt64", rfk::EFieldFlags::Default, true)->getData<unsigned long long&>(&exampleClassInstance) = 642u;
	TEST(exampleClass.getField("pInt64", rfk::EFieldFlags::Default, true)->getData<unsigned long long>(&exampleClassInstance) == 642u);

	TEST(exampleClass.getField("someInt", rfk::EFieldFlags::Public | rfk::EFieldFlags::Mutable)->getData<int>(&exampleClassInstance) == 42);
	TEST(exampleClass.getField("someParentClass")->getData<namespace3::ParentClass&>(&exampleClassInstance).pInt64 == 666u);

	//Make sure const fields can't be set
	rfk::Class const& eClass = E::staticGetArchetype();
	E eInstance;

	try
	{
		eClass.getField("constFloat")->setData(&eInstance, 0);
		TEST(false); //Should never pass here
	}
	catch (rfk::ConstViolation const&)
	{
	}

	try
	{
		eClass.getField("constFloat")->setData(&eInstance, 42.0f);
		TEST(false); //Should never pass here
	}
	catch (rfk::ConstViolation const&)
	{
	}

	//Make sure that const field can only be get as const
	try
	{
		eClass.getField("constFloat")->getData<float&&>(&eInstance);
		TEST(false);
	}
	catch (rfk::ConstViolation const&)
	{
	}

	try
	{
		eClass.getField("constFloat")->getData<float&>(&eInstance);
		TEST(false);
	}
	catch (rfk::ConstViolation const&)
	{

	}

	try
	{
		eClass.getField("constFloat")->getData<float const&>(&eInstance);
	}
	catch (rfk::ConstViolation const&)
	{
		TEST(false);
	}

	try
	{
		eClass.getField("constFloat")->getData<float>(&eInstance); //copy is ok
	}
	catch (rfk::ConstViolation const&)
	{
		TEST(false);
	}
}

void staticFields()
{
	//ExampleClass
	rfk::Class const& ec = namespace3::ExampleClass::staticGetArchetype();

	TEST(ec.getField("someStaticInt") == nullptr);
	TEST(ec.getStaticField("someStaticInt") != nullptr);
	TEST(ec.getStaticField("someStaticInt", rfk::EFieldFlags::Public) != nullptr);
	TEST(ec.getStaticField("someStaticInt", rfk::EFieldFlags::Public) == rfk::Database::getStaticField(ec.getStaticField("someStaticInt", rfk::EFieldFlags::Public)->id));
	TEST(ec.getStaticField("someStaticInt", rfk::EFieldFlags::Public)->getData<int>() == namespace3::ExampleClass::someStaticInt);
	
	ec.getStaticField("someStaticInt", rfk::EFieldFlags::Public)->setData(2);
	TEST(namespace3::ExampleClass::someStaticInt == 2);

	//Make sure const static fields can't be set
	rfk::Class const& eClass = E::staticGetArchetype();

	try
	{
		eClass.getStaticField("staticConstFloat")->setData(nullptr, 0);
		TEST(false); //Should never pass here
	}
	catch (rfk::ConstViolation const&)
	{
	}

	try
	{
		eClass.getStaticField("staticConstFloat")->setData(42.0f);
		TEST(false); //Should never pass here
	}
	catch (rfk::ConstViolation const&)
	{
	}

	//Make sure that const static field can only be get as const
	try
	{
		eClass.getStaticField("staticConstFloat")->getData<float&&>();
		TEST(false);
	}
	catch (rfk::ConstViolation const&)
	{
	}

	try
	{
		eClass.getStaticField("staticConstFloat")->getData<float&>();
		TEST(false);
	}
	catch (rfk::ConstViolation const&)
	{

	}

	try
	{
		eClass.getStaticField("staticConstFloat")->getData<float const&>();
	}
	catch (rfk::ConstViolation const&)
	{
		TEST(false);
	}

	try
	{
		eClass.getStaticField("staticConstFloat")->getData<float>(); //copy is ok
	}
	catch (rfk::ConstViolation const&)
	{
		TEST(false);
	}
}

void variables()
{
	TEST(approximatelyEqual(rfk::Database::getVariable("variableInsideGlobalScope", rfk::EVarFlags::Default)->getData<float>(), 10.0f));
	TEST(approximatelyEqual(rfk::Database::getVariable("variableInsideGlobalScope", rfk::EVarFlags::Static)->getData<float>(), 10.0f));
	TEST(rfk::Database::getVariable("variableInsideGlobalScope") == rfk::Database::getVariable(rfk::Database::getVariable("variableInsideGlobalScope")->id));

	TEST(rfk::Database::getVariable("variableInsideNamespace") == nullptr);

	//Make sure const variables can't be set
	try
	{
		rfk::Database::getVariable("constGlobalInt")->setData(nullptr, 0);
		TEST(false); //Should never pass here
	}
	catch (rfk::ConstViolation const&)
	{
	}

	try
	{
		rfk::Database::getVariable("constGlobalInt")->setData(32);
		TEST(false); //Should never pass here
	}
	catch (rfk::ConstViolation const&)
	{
	}

	//Make sure that const variables can only be get as const
	try
	{
		rfk::Database::getVariable("constGlobalInt")->getData<float&&>();
		TEST(false);
	}
	catch (rfk::ConstViolation const&)
	{
	}

	try
	{
		rfk::Database::getVariable("constGlobalInt")->getData<float&>();
		TEST(false);
	}
	catch (rfk::ConstViolation const&)
	{

	}

	try
	{
		rfk::Database::getVariable("constGlobalInt")->getData<float const&>();
	}
	catch (rfk::ConstViolation const&)
	{
		TEST(false);
	}

	try
	{
		rfk::Database::getVariable("constGlobalInt")->getData<float>(); //copy is ok
	}
	catch (rfk::ConstViolation const&)
	{
		TEST(false);
	}
}

void functions()
{
	rfk::Database::getFunction("functionInsideGlobalScope", rfk::EFunctionFlags::Default)->invoke(12.f);
	rfk::Database::getFunction("functionInsideGlobalScope", rfk::EFunctionFlags::Static)->invoke(12.f);

	TEST(rfk::Database::getFunction("functionInsideGlobalScope") == rfk::Database::getFunction(rfk::Database::getFunction("functionInsideGlobalScope")->id));
	TEST(rfk::Database::getFunction("functionInsideGlobalScope", rfk::EFunctionFlags::Inline) == nullptr);
}

void inheritance()
{
	//rfk::Class const& pppClass = ParentParentParentClass::staticGetArchetype(); //Not reflected type, so can't call staticGetArchetype();
	rfk::Class const& ppc	= namespace2::ParentParentClass::staticGetArchetype();
	rfk::Class const& pc	= namespace3::ParentClass::staticGetArchetype();
	rfk::Class const& pc2	= namespace3::ParentClass2::staticGetArchetype();
	rfk::Class const& ec	= namespace3::ExampleClass::staticGetArchetype();
	rfk::Class const& oc	= namespace3::OtherClass::staticGetArchetype();

	//IsBaseOf
	TEST(ppc.isBaseOf(ppc));
	TEST(ppc.isBaseOf(pc));
	TEST(!ppc.isBaseOf(pc2));
	TEST(ppc.isBaseOf(ec));
	TEST(!ppc.isBaseOf(oc));

	TEST(!pc.isBaseOf(ppc));
	TEST(pc.isBaseOf(pc));
	TEST(!pc.isBaseOf(pc2));
	TEST(pc.isBaseOf(ec));
	TEST(!pc.isBaseOf(oc));

	TEST(!ec.isBaseOf(ppc));
	TEST(!ec.isBaseOf(pc));
	TEST(!ec.isBaseOf(pc2));
	TEST(ec.isBaseOf(ec));
	TEST(!ec.isBaseOf(oc));

	TEST(!oc.isBaseOf(ppc));
	TEST(!oc.isBaseOf(pc));
	TEST(!oc.isBaseOf(pc2));
	TEST(!oc.isBaseOf(ec));
	TEST(oc.isBaseOf(oc));

	TEST(!pc2.isBaseOf(ppc));
	TEST(!pc2.isBaseOf(pc));
	TEST(pc2.isBaseOf(pc2));
	TEST(pc2.isBaseOf(ec));
	TEST(!pc2.isBaseOf(oc));

	//isSubclassOf
	TEST(!ppc.isSubclassOf(ppc));
	TEST(!ppc.isSubclassOf(pc));
	TEST(!ppc.isSubclassOf(pc2));
	TEST(!ppc.isSubclassOf(ec));
	TEST(!ppc.isSubclassOf(oc));

	TEST(pc.isSubclassOf(ppc));
	TEST(!pc.isSubclassOf(pc));
	TEST(!pc.isSubclassOf(pc2));
	TEST(!pc.isSubclassOf(ec));
	TEST(!pc.isSubclassOf(oc));

	TEST(ec.isSubclassOf(ppc));
	TEST(ec.isSubclassOf(pc));
	TEST(ec.isSubclassOf(pc2));
	TEST(!ec.isSubclassOf(ec));
	TEST(!ec.isSubclassOf(oc));

	TEST(!oc.isSubclassOf(ppc));
	TEST(!oc.isSubclassOf(pc));
	TEST(!oc.isSubclassOf(pc2));
	TEST(!oc.isSubclassOf(ec));
	TEST(!oc.isSubclassOf(oc));

	TEST(!pc2.isSubclassOf(ppc));
	TEST(!pc2.isSubclassOf(pc));
	TEST(!pc2.isSubclassOf(pc2));
	TEST(!pc2.isSubclassOf(ec));
	TEST(!pc2.isSubclassOf(oc));
}

void instantiation()
{
	rfk::Class const& pc	= namespace3::ParentClass::staticGetArchetype();
	rfk::Class const& pc2	= namespace3::ParentClass2::staticGetArchetype();
	rfk::Class const& ec	= namespace3::ExampleClass::staticGetArchetype();

	namespace3::ParentClass*	pcI		= pc.makeInstance<namespace3::ParentClass>();
	namespace3::ParentClass2*	pc2I	= pc2.makeInstance<namespace3::ParentClass2>();
	namespace3::ExampleClass*	ecI		= ec.makeInstance<namespace3::ExampleClass>();

	TEST(&pcI->getArchetype() == &pc);
	//TEST(&pc2I->getArchetype() == &pc2);	//Can't do that test because ParentClass2 is not a ReflectedObject
	TEST(&ecI->getArchetype() == &ec);

	TEST(pcI->pInt64 == 666u);
	TEST(ecI->someInt == 1);	//ExampleClass has a custom instantiator without parameters, which sets someInt to 1

	//This leaks :) Should clean pcI, pc2I & ecI
	delete pcI;
	delete pc2I;
	delete ecI;
}

void parseAllNested()
{
	TEST(rfk::Database::getNamespace("parse_all_nested_namespace")->getClass("NestedClass1") != nullptr);
	TEST(rfk::Database::getNamespace("parse_all_nested_namespace")->getStruct("NestedStruct1") != nullptr);
	TEST(rfk::Database::getNamespace("parse_all_nested_namespace")->getEnum("NestedEnum1") != nullptr);
	TEST(rfk::Database::getNamespace("parse_all_nested_namespace")->getNamespace("parse_all_nested_namespace") != nullptr);
}

void properties()
{
	rfk::Class const& ec = namespace3::ExampleClass::staticGetArchetype();

	TEST(ec.getStaticMethod("customInstantiator")->getProperty<CustomInstantiator>() != nullptr);

	rfk::Class const& a = A::staticGetArchetype();

	TEST(a.getProperty<CustomProperty2>() != nullptr);
	TEST(a.getProperty(CustomProperty::staticGetArchetype()) != nullptr);
	TEST(a.getProperties(CustomProperty::staticGetArchetype(), false).size() == 1u);
	TEST(a.getProperties(CustomProperty::staticGetArchetype(), true).size() == 3u);
	TEST(a.getProperties<CustomProperty2>().size() == 2u);
	
	//with predicate
	TEST(a.getProperty([](rfk::Property const* prop) { return CustomProperty::staticGetArchetype().isBaseOf(prop->getArchetype()); }) != nullptr);

	//Get all properties inheriting from CustomProperty (including CustomProperty)
	TEST(a.getProperties([](rfk::Property const* prop) { return CustomProperty::staticGetArchetype().isBaseOf(prop->getArchetype()); }).size() == 3u);

	rfk::Field const* f = a.getField("field");

	TEST(f->getProperty([](rfk::Property const* prop){ return	prop->getArchetype() == CustomProperty::staticGetArchetype() && 
																reinterpret_cast<CustomProperty const*>(prop)->i == 1 &&
																reinterpret_cast<CustomProperty const*>(prop)->j == 456; }) != nullptr);
	TEST(f->getProperties<CustomProperty2>().empty());

	TEST(a.getMethod([](rfk::Method const* method) { return method->name == "testMethod" && method->parameters.empty(); })->getProperty<Tooltip>()->message == "This is a test");

	//Properties inheritance
	rfk::Class const& b = B::staticGetArchetype();
	rfk::Class const& c = C::staticGetArchetype();

	TEST(b.getProperty<CustomProperty2>() == nullptr);											//CustomProperty2 is not a inherited property
	TEST(b.getProperty<CustomProperty>()->i == 3 && b.getProperty<CustomProperty>()->j == 4);	//Overriden inherited property
	TEST(c.getProperty<CustomProperty>()->j == 2);												//Inherited property
	TEST(c.getMethod("testMethod")->getProperty<Tooltip>()->message == "This is a test");		//Overriden method inherit from base method

	parseAllNested();
}

void dynamicTypes()
{
	std::vector<rfk::Object*>	objects;

	objects.push_back(new namespace3::ExampleClass());
	objects.push_back(new namespace3::ParentClass());
	objects.push_back(new namespace2::ParentParentClass());

	TEST(objects[0]->getArchetype().name == "ExampleClass");
	TEST(objects[1]->getArchetype().name == "ParentClass");
	TEST(objects[2]->getArchetype().name == "ParentParentClass");

	//Yummy leak
	for (rfk::Object* o : objects)
	{
		delete o;
	}
}

void makeInstance()
{
	//ExampleClass has a default constructor, can call makeInstance()
	namespace3::ExampleClass* instance1 = namespace3::ExampleClass::staticGetArchetype().makeInstance<namespace3::ExampleClass>();
	TEST(instance1 != nullptr && instance1->someInt == 1);
	delete instance1;

	//Use customInstantiator method
	rfk::Object* instance2 = namespace3::ExampleClass::staticGetArchetype().makeInstance<rfk::Object>(1, 3.14f);
	TEST(instance2 != nullptr);
	delete instance2;

	TEST(namespace3::ExampleClass::staticGetArchetype().makeInstance(10.0f, 3.14f) == nullptr);

	//ExampleClass2 has a deleted default constructor, makeInstance should return nullptr
	TEST(namespace3::ExampleClass2::staticGetArchetype().makeInstance() == nullptr);

	//Use customInstantiator method
	namespace3::ExampleClass2* instance3 = namespace3::ExampleClass2::staticGetArchetype().makeInstance<namespace3::ExampleClass2>(42);
	TEST(instance3->i == 42);
	delete instance3;
}

void database()
{
	TEST(rfk::Database::getNamespace("namespace4") != nullptr);
	TEST(rfk::Database::getNamespace("namespace4::namespace4_nested") != nullptr);
	TEST(rfk::Database::getNamespace("namespace4_nested") == nullptr);
	TEST(rfk::Database::getNamespace("namespace4::namespace4_nested::namespace4_nested_nested") != nullptr);
	
	try
	{
		TEST(rfk::Database::getNamespace("namespace4::") != nullptr);
		TEST(false);	//Should never reach this line
	}
	catch (...)
	{}

	try
	{
		TEST(rfk::Database::getNamespace("names:pace4") != nullptr);
		TEST(false);	//Should never reach this line
	}
	catch (...)
	{}

	try
	{
		TEST(rfk::Database::getNamespace("namespace4:") != nullptr);
		TEST(false);	//Should never reach this line
	}
	catch (...)
	{}

	TEST(rfk::Database::getFunction<int(int)>("function1")->rInvoke<int>(1) == 1);
	TEST(rfk::Database::getFunction<int(int, int)>("function1")->rInvoke<int>(1, 2) == 3);
	TEST(rfk::Database::getFunction<void(int, int)>("function1") == nullptr);
	TEST(rfk::Database::getFunction<int()>("function1") == nullptr);
	TEST(rfk::Database::getFunction<void(namespace3::ExampleClass)>("function1") != nullptr);

	//By predicate
	TEST(rfk::Database::getEntity([](rfk::Entity const* e) { return e->id == namespace3::ExampleClass::staticGetArchetype().id; }) != nullptr);
	TEST(rfk::Database::getArchetype([](rfk::Archetype const* a) { return a->getProperty<PropertySettings>() != nullptr; }) != nullptr);
	TEST(rfk::Database::getStruct([](rfk::Struct const* s) { return s->getMethod("method") != nullptr; })->name == "ExampleStruct");
	TEST(rfk::Database::getClass([](rfk::Class const* c){ CustomProperty const* prop = c->getProperty<CustomProperty>(); return prop != nullptr && prop->i == 3 && prop->j == 4; })->name == "B");
	TEST(rfk::Database::getEnum([](rfk::Enum const* e) { rfk::EnumValue const* ev = e->getEnumValue("Value2"); return ev != nullptr && ev->value == 1; })->name == "EThisIsANormalEnum");
	TEST(rfk::Database::getFundamentalArchetype([](rfk::FundamentalArchetype const* ft) { return ft->memorySize == 4; }) != nullptr);
	TEST(rfk::Database::getVariable([](rfk::Variable const* v) { return v->type == rfk::Type::getType<float>() && v->getData<float>() == 10.0f; })->name == "variableInsideGlobalScope");
	TEST(rfk::Database::getFunction([](rfk::Function const* f) { return f->returnType == rfk::Type::getType<void>() && f->parameters.size() == 1 && f->parameters[0].type == rfk::Type::getType<namespace3::ExampleClass>(); })->name == "function1");
}

void templateEnums()
{
	TEST(rfk::getEnum<namespace3::ExampleEnum>() == rfk::Database::getNamespace("namespace3")->getEnum("ExampleEnum"));
}

void getArchetypes()
{
	//From database
	TEST(rfk::Database::getArchetype("ExampleStruct") != nullptr);

	//Using templated version
	TEST(rfk::getArchetype<namespace3::ExampleClass>() == rfk::Database::getNamespace("namespace3")->getClass("ExampleClass"));
	TEST(rfk::getArchetype<namespace3::ExampleClass2>() == rfk::Database::getNamespace("namespace3")->getClass("ExampleClass2"));
	TEST(rfk::Database::getArchetype(rfk::getArchetype<Vector3f>()->id) == rfk::getArchetype<Vector3f>());

	TEST(rfk::getArchetype<void>() == rfk::getArchetype<void*>());
	TEST(rfk::getArchetype<namespace3::ExampleClass>() == rfk::getArchetype<volatile const namespace3::ExampleClass&>());
	TEST(rfk::getArchetype<namespace3::ExampleClass>() == rfk::getArchetype<volatile const namespace3::ExampleClass* const>());
	TEST(rfk::getArchetype<namespace3::ExampleClass>() == rfk::getArchetype<namespace3::ExampleClass****>());
	TEST(rfk::getArchetype<int>() == rfk::getArchetype<int*&>());
	TEST(rfk::getArchetype<int>() == rfk::getArchetype<int[2]>());
	TEST(rfk::getArchetype<int>() == rfk::getArchetype<int[2][3]>());

	TEST(rfk::getArchetype<void(int)>() == nullptr);			//Func prototype
	TEST(rfk::getArchetype<void(*)(int)>() == nullptr);			//Func ptr
	TEST(rfk::getArchetype<int(rfk::Class::*)>() == nullptr);	//Ptr to field
	TEST(rfk::getArchetype<int(rfk::Class::*)()>() == nullptr);	//Ptr to method

	auto l = [](){};
	TEST(rfk::getArchetype<decltype(l)>() == nullptr);			//Lambda
}

void entityCast()
{
	//FundamentalArchetype
	TEST(rfk::entityCast<rfk::Archetype>(rfk::Database::getEntity(rfk::getArchetype<int>()->id)) != nullptr);
	TEST(rfk::entityCast<rfk::FundamentalArchetype>(rfk::Database::getEntity(rfk::getArchetype<float>()->id)) != nullptr);

	//Enum
	rfk::Enum const* e = rfk::getEnum<namespace3::ExampleEnum>();

	TEST(rfk::entityCast<rfk::Archetype>(rfk::Database::getEntity(e->id)) != nullptr);
	TEST(rfk::entityCast<rfk::Enum>(rfk::Database::getEntity(e->id)) != nullptr);

	//EnumValue
	TEST(rfk::entityCast<rfk::EnumValue>(rfk::Database::getEntity(e->getEnumValue(1)->id)) != nullptr);

	//Struct
	rfk::Struct const& s = ExampleStruct::staticGetArchetype();

	TEST(rfk::entityCast<rfk::Archetype>(rfk::Database::getEntity(s.id)) != nullptr);
	TEST(rfk::entityCast<rfk::Struct>(rfk::Database::getEntity(s.id)) != nullptr);

	//Class
	rfk::Class const& c = namespace3::ExampleClass::staticGetArchetype();

	TEST(rfk::entityCast<rfk::Archetype>(rfk::Database::getEntity(c.id)) != nullptr);
	TEST(rfk::entityCast<rfk::Struct>(rfk::Database::getEntity(c.id)) != nullptr);
	TEST(rfk::entityCast<rfk::Class>(rfk::Database::getEntity(c.id)) != nullptr);

	//Fields
	rfk::Field const* field = s.getField("i");
	rfk::StaticField const* sField = s.getStaticField("staticInt");

	TEST(rfk::entityCast<rfk::FieldBase>(rfk::Database::getEntity(field->id)) != nullptr);
	TEST(rfk::entityCast<rfk::Field>(rfk::Database::getEntity(field->id)) != nullptr);
	TEST(rfk::entityCast<rfk::FieldBase>(rfk::Database::getEntity(sField->id)) != nullptr);
	TEST(rfk::entityCast<rfk::StaticField>(rfk::Database::getEntity(sField->id)) != nullptr);

	//Methods
	rfk::Method const* method = s.getMethod("method");
	rfk::StaticMethod const* sMethod = s.getStaticMethod("staticMethod");

	TEST(rfk::entityCast<rfk::MethodBase>(rfk::Database::getEntity(method->id)) != nullptr);
	TEST(rfk::entityCast<rfk::Method>(rfk::Database::getEntity(method->id)) != nullptr);
	TEST(rfk::entityCast<rfk::MethodBase>(rfk::Database::getEntity(sMethod->id)) != nullptr);
	TEST(rfk::entityCast<rfk::StaticMethod>(rfk::Database::getEntity(sMethod->id)) != nullptr);

	//Namespaces
	TEST(rfk::entityCast<rfk::Namespace>(rfk::Database::getEntity(rfk::Database::getNamespace("namespace3")->id)) != nullptr);

	//Variables
	TEST(rfk::entityCast<rfk::Variable>(rfk::Database::getEntity(rfk::Database::getVariable("variableInsideGlobalScope")->id)) != nullptr);

	//Functions
	TEST(rfk::entityCast<rfk::Function>(rfk::Database::getEntity(rfk::Database::getFunction("function1")->id)) != nullptr);
}

void fundamentalArchetypes()
{
	TEST(rfk::Database::getFundamentalArchetype("int") != nullptr);
	TEST(rfk::Database::getFundamentalArchetype("void") != nullptr);
	TEST(rfk::Database::getFundamentalArchetype("nullptr_t") != nullptr);
}

void enumManualReflection()
{
	rfk::Enum const* e = rfk::Database::getEnum("ThirdPartyEnum");

	TEST(e != nullptr);
	TEST(rfk::getEnum<ThirdPartyEnum>() != nullptr);
	TEST(e == rfk::getEnum<ThirdPartyEnum>());
	TEST(e->getEnumValue("Value1")->value == 0);
	TEST(e->getEnumValue(2)->name == "Value2");
}

void classManualReflection()
{
	rfk::Class const* vec3archetype = rfk::Database::getClass("Vector3f");

	TEST(vec3archetype != nullptr);
	TEST(vec3archetype->getField("x") != nullptr);
	TEST(vec3archetype->getField("y") != nullptr);
	TEST(vec3archetype->getField("z") != nullptr);
	TEST(vec3archetype->getMethod("sqrSize", rfk::EMethodFlags::Public | rfk::EMethodFlags::Inline | rfk::EMethodFlags::Const) != nullptr);
	TEST(vec3archetype->getStaticMethod<float(Vector3f const&, Vector3f const&)>("dot", rfk::EMethodFlags::Public | rfk::EMethodFlags::Inline) != nullptr);

	Vector3f vec{3.14f, 42.0f, 0.0f};

	TEST(approximatelyEqual(vec3archetype->getField("x")->getData<float>(&vec), 3.14f));
	TEST(approximatelyEqual(vec3archetype->getField("y")->getData<float>(&vec), 42.0f));
	TEST(approximatelyEqual(vec3archetype->getField("z")->getData<float>(&vec), 0.0f));

	rfk::Class const& exampleClassArchetype = namespace3::ExampleClass::staticGetArchetype();
	TEST(exampleClassArchetype.getField("vec3")->type.archetype == vec3archetype);
	TEST(exampleClassArchetype.getField("vec3ptr")->type.archetype == vec3archetype);
}

void structDirectChildren()
{
	rfk::Class const& ppClass = namespace2::ParentParentClass::staticGetArchetype();

	TEST(ppClass.getDirectSubclasses().size() == 1u);
	TEST(ppClass.subclasses.size() == 2u);
}

#include "TemplateClass.h"
void typeTemplateClass()
{
	rfk::Class const* c = rfk::Database::getClass("TestSimpleClassTemplate");

	//Template
	TEST(c->isTemplate());
	TEST(c->asTemplate()->getProperty<ParseAllNested>() != nullptr);

	std::cout << c->asTemplate()->getInstance<int>() << std::endl;
	std::cout << c->asTemplate()->getInstance<TestClassA>() << std::endl;
	std::cout << c->asTemplate()->getInstance<TestClassB>() << std::endl;

	//Template instance

	//rfk::ClassTemplate const* classTemplate = rfk

	//std::cout << c->getField("vector")->type.archetype << std::endl;
}

int main()
{
	/*inheritance();
	classes();
	structs();
	database();
	outerEntities();
	namespaces();
	templateEnums();
	getArchetypes();
	entityCast();
	enums();
	methods();
	staticMethods();
	fields();
	staticFields();
	variables();
	functions();
	instantiation();
	properties();
	dynamicTypes();
	makeInstance();
	fundamentalArchetypes();
	enumManualReflection();
	classManualReflection();
	structDirectChildren();*/

	typeTemplateClass();

	return EXIT_SUCCESS;
}