#include <iostream>
#include <cassert>

#include "ExampleClass.h"

#include "TypeInfo/Database.h"

void classes()
{
	assert(rfk::Database::getClass("ParentParentParentClass") == nullptr);
	assert(rfk::Database::getClass("ParentParentClass") != nullptr);
	assert(rfk::Database::getClass("OtherClass") != nullptr);
	assert(rfk::Database::getClass("ParentClass") != nullptr);
	assert(rfk::Database::getClass("ParentClass2") != nullptr);
	assert(rfk::Database::getClass("ExampleClass") != nullptr);
	assert(rfk::Database::getEnum("ExampleClass") == nullptr);
	assert(rfk::Database::getStruct("ExampleClass") == nullptr);
}

void enums()
{
	assert(rfk::Database::getEnum("UnexistantEnum") == nullptr);

	assert(rfk::Database::getArchetype("ExampleEnum") != nullptr);
	assert(rfk::Database::getClass("ExampleEnum") == nullptr);
	assert(rfk::Database::getStruct("ExampleEnum") == nullptr);

	rfk::Enum const* e = rfk::Database::getEnum("ExampleEnum");
	assert(e != nullptr);

	assert(e->memorySize == sizeof(char));
	assert(e->name == "ExampleEnum");
	assert(e->getEnumValue("ExampleValue1")->value == 1 << 0);
	assert(e->getEnumValue("ExampleValue2")->value == 1 << 1);
	assert(e->getEnumValue("ExampleValue3")->value == 1 << 2);
	assert(e->getEnumValue("ExampleValue4")->value == 1 << 3);
	assert(e->getEnumValue("ExampleValue5")->value == 1 << 3);
	assert(e->getEnumValue(1 << 0)->name == "ExampleValue1");
	assert(e->getEnumValue(1 << 1)->name == "ExampleValue2");
	assert(e->getEnumValue(1 << 2)->name == "ExampleValue3");
	assert(e->getEnumValues(1 << 3).size() == 2);
}

void methods()
{
	//ParentParentClass
	rfk::Class const& ppc = namespace2::ParentParentClass::staticGetArchetype();

	assert(ppc.getMethod("SomeMethod") == nullptr);

	//ParentClass
	namespace3::ParentClass const	p;
	rfk::Class const&				pc = namespace3::ParentClass::staticGetArchetype();

	pc.getMethod("parentClassMethod1")->invoke(&p);

	rfk::Method const* pc_method1 = pc.getMethod("method1", rfk::EMethodFlags::Public | rfk::EMethodFlags::Virtual | rfk::EMethodFlags::Const);
	assert(pc_method1->safeInvoke<int>(&p) == 1);
	assert(pc.getMethod("method1", rfk::EMethodFlags::Protected | rfk::EMethodFlags::Virtual | rfk::EMethodFlags::Const) == nullptr);

	//ExampleClass
	namespace3::ExampleClass	e;
	rfk::Class const&			ec = namespace3::ExampleClass::staticGetArchetype();

	rfk::Method const*			ec_method1 = ec.getMethod("method1", rfk::EMethodFlags::Public | rfk::EMethodFlags::Override | rfk::EMethodFlags::Final | rfk::EMethodFlags::Virtual);
	assert(ec_method1->invoke<int>(&e) != 1);
	assert(ec_method1->invoke<int>(&e) == 2);

	rfk::Method const*			ec_method2 = ec.getMethod("method2", rfk::EMethodFlags::Protected | rfk::EMethodFlags::Const);
	ec_method2->invoke(&e);

	rfk::Method const*			ec_method3int = ec.getMethod("method3", rfk::EMethodFlags::Protected);
	assert(ec_method3int->invoke<int>(&e) == 42);

	rfk::Method const*			ec_method3float	= ec.getMethod("method3", rfk::EMethodFlags::Private);
	assert(ec_method3float->invoke<float>(&e));

	rfk::Method const*			ec_method4	= ec.getMethod("method4", rfk::EMethodFlags::Public);
	assert(ec_method4->invoke<unsigned long long>(&e, nullptr) == 0u);

	try
	{
		ec_method4->safeInvoke<unsigned long long>(&e, nullptr, 1);		// <- Bad number of arguments
		assert(false);	//Should not reach this line, throw here ^
	}
	catch (rfk::MethodError const& e)
	{}

	try
	{
		ec_method4->safeInvoke<unsigned long long>(&e, 1);		// <- Bad argument type
		assert(false);	//Should not reach this line, throw here ^
	}
	catch (rfk::MethodError const& e)
	{}
}

void staticMethods()
{

}

void fields()
{

}

void staticFields()
{

}

void inheritance()
{

}

void instantiation()
{

}

void properties()
{

}

void dynamicTypes()
{

}

int main()
{
	classes();
	enums();
	methods();
	staticMethods();
	fields();
	staticFields();
	inheritance();
	instantiation();
	properties();
	dynamicTypes();

	return EXIT_SUCCESS;
}