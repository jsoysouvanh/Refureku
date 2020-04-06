#include <iostream>

#include "ExampleClass.h"

#include "TypeInfo/Database.h"

#define TEST(...) if (!(__VA_ARGS__)) { std::cerr << "Test failed (" << __LINE__ << "): " << #__VA_ARGS__ << std::endl; exit(EXIT_FAILURE); }

void classes()
{
	TEST(rfk::Database::getClass("ParentParentParentClass") == nullptr);
	TEST(rfk::Database::getClass("ParentParentClass") != nullptr);
	TEST(rfk::Database::getClass("OtherClass") != nullptr);
	TEST(rfk::Database::getClass("ParentClass") != nullptr);
	TEST(rfk::Database::getClass("ParentClass2") != nullptr);
	TEST(rfk::Database::getClass("ExampleClass") != nullptr);
	TEST(rfk::Database::getEnum("ExampleClass") == nullptr);
	TEST(rfk::Database::getStruct("ExampleClass") == nullptr);
}

void enums()
{
	TEST(rfk::Database::getEnum("UnexistantEnum") == nullptr);

	TEST(rfk::Database::getArchetype("ExampleEnum") != nullptr);
	TEST(rfk::Database::getClass("ExampleEnum") == nullptr);
	TEST(rfk::Database::getStruct("ExampleEnum") == nullptr);

	rfk::Enum const* e = rfk::Database::getEnum("ExampleEnum");
	TEST(e != nullptr);

	TEST(e->memorySize == sizeof(char));
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
}

void methods()
{
	//ParentParentClass
	rfk::Class const& ppc = namespace2::ParentParentClass::staticGetArchetype();

	TEST(ppc.getMethod("SomeMethod") == nullptr);

	//ParentClass
	namespace3::ParentClass const	p;
	rfk::Class const&				pc = namespace3::ParentClass::staticGetArchetype();

	pc.getMethod("parentClassMethod1")->invoke(&p);

	rfk::Method const* pc_method1 = pc.getMethod("method1", rfk::EMethodFlags::Public | rfk::EMethodFlags::Virtual | rfk::EMethodFlags::Const);
	TEST(pc_method1->safeInvoke<int>(&p) == 1);
	TEST(pc.getMethod("method1", rfk::EMethodFlags::Protected | rfk::EMethodFlags::Virtual | rfk::EMethodFlags::Const) == nullptr);

	//ExampleClass
	namespace3::ExampleClass	e;
	rfk::Class const&			ec = namespace3::ExampleClass::staticGetArchetype();

	rfk::Method const*			ec_method1 = ec.getMethod("method1", rfk::EMethodFlags::Public | rfk::EMethodFlags::Override | rfk::EMethodFlags::Final | rfk::EMethodFlags::Virtual);
	TEST(ec_method1->invoke<int>(&e) != 1);
	TEST(ec_method1->invoke<int>(&e) == 2);

	rfk::Method const*			ec_method2 = ec.getMethod("method2", rfk::EMethodFlags::Protected | rfk::EMethodFlags::Const);
	ec_method2->invoke(&e);

	rfk::Method const*			ec_method3int = ec.getMethod("method3", rfk::EMethodFlags::Protected);
	TEST(ec_method3int->invoke<int>(&e) == 42);

	rfk::Method const*			ec_method3float	= ec.getMethod("method3", rfk::EMethodFlags::Private);
	
	#if REFUREKU_DEBUG

	try
	{
		ec_method3float->invoke<float>(&e);	// <- Bad number of arguments
		TEST(false);	//Should not reach this line, throw here ^ in DEBUG only
	}
	catch (rfk::MethodError const& e)
	{
		ec_method3float->invoke<float>(&e, 7);	// <- Call with correct arguments count
	}

	#else

	ec_method3float->invoke<float>(&e);	// <- This should not throw in release eventhough bad arguments count
	ec_method3float->invoke<float>(&e, 7);

	#endif

	rfk::Method const*	ec_method4	= ec.getMethod("method4", rfk::EMethodFlags::Public);
	TEST(ec_method4->invoke<unsigned long long>(&e, nullptr) == 0u);

	try
	{
		ec_method4->safeInvoke<unsigned long long>(&e, nullptr, 1);		// <- Bad number of arguments
		TEST(false);	//Should not reach this line, throw here ^
	}
	catch (rfk::MethodError const& e)
	{}

	try
	{
		ec_method4->safeInvoke<unsigned long long>(&e, 1);		// <- Bad argument type
		TEST(false);	//Should not reach this line, throw here ^
	}
	catch (rfk::MethodError const& e)
	{}

	//No lookup in parent classes
	TEST(ec.getMethod("parentClassMethod1", rfk::EMethodFlags::Private, false) == nullptr);

	//Lookup in parent classes
	rfk::Method const*	ec_parentClassMethod1 = ec.getMethod("parentClassMethod1", rfk::EMethodFlags::Private, true);
	TEST(ec_parentClassMethod1 != nullptr);

	ec_parentClassMethod1->invoke(&e);
}

void staticMethods()
{
	//ParentClass
	rfk::Class const& pc = namespace3::ParentClass::staticGetArchetype();

	TEST(pc.getStaticMethod("method1") == nullptr);	//Not static

	//ExampleClass
	rfk::Class const& ec = namespace3::ExampleClass::staticGetArchetype();

	ec.getStaticMethod("staticMethod1", rfk::EMethodFlags::Private)->invoke();

	TEST(ec.getStaticMethod("staticMethod2", rfk::EMethodFlags::Private)->invoke<int>() == 2);

	TEST(ec.getStaticMethod("staticMethod3", rfk::EMethodFlags::Public) == nullptr);

	TEST(ec.getStaticMethods("staticMethod3").size() == 2u);

	ec.getStaticMethod("staticMethod3", rfk::EMethodFlags::Protected)->invoke("This is a test, and let's try to make sure it works even when it's long");
	TEST(ec.getStaticMethod("staticMethod3", rfk::EMethodFlags::Private)->invoke<int, int, int>(1, 2) == 3);
}

void fields()
{
	/*namespace namespace2
	{
		class RFKClass(rfk::ReflectedObject) ParentParentClass : public namespace1::ParentParentParentClass, public rfk::ReflectedObject
		{
			private:
				RFKField()
				float ppFloat = 123456.123456f;
		};
	}*/

	//ParentParentClass
	//namespace2::ParentParentClass const	pp;
	//rfk::Class const& ppc = namespace2::ParentParentClass::staticGetArchetype();

	//ppc.getField()
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