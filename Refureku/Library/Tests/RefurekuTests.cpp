#include <iostream>
#include <vector>

#include "ExampleClass.h"

#include "TypeInfo/Database.h"

#define TEST(...) if (!(__VA_ARGS__)) { std::cerr << "Test failed (" << __LINE__ << "): " << #__VA_ARGS__ << std::endl; exit(EXIT_FAILURE); }

void namespaces()
{
	TEST(rfk::Database::getNamespace("namespace3") != nullptr);
	TEST(rfk::Database::getNamespace("namespace4") != nullptr);
	TEST(rfk::Database::getNamespace("namespace4_nested") == nullptr);
	TEST(rfk::Database::getNamespace("namespace4")->getNestedNamespace("namespace4_nested") != nullptr);
	TEST(rfk::Database::getNamespace("namespace3")->getClass("AnotherClassInNamespace3") != nullptr);
	TEST(rfk::Database::getNamespace("test1")->getNestedNamespace("test2")->getEnum("NestedEnumInNestedNamespace")->getEnumValue("SomeValue")->value == 42u);
}

void classes()
{
	TEST(rfk::Database::getClass("ParentParentParentClass") == nullptr);
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
}

void enums()
{
	TEST(rfk::Database::getEnum("UnexistantEnum") == nullptr);

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

	//Nested enum
	TEST(rfk::Database::getNamespace("namespace3")->getClass("ExampleClass")->getNestedEnum("NestedExampleEnum")->getEnumValue("Value1")->value == 0);
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
	TEST(pc_method1->checkedInvoke<int>(&p) == 1);
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
	catch (std::exception const&)
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
		ec_method4->checkedInvoke<unsigned long long>(&e, nullptr, 1);		// <- Bad number of arguments
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
	//ParentParentClass
	namespace2::ParentParentClass	pp;
	rfk::Class const&				ppc = namespace2::ParentParentClass::staticGetArchetype();

	TEST(ppc.getField("pFloat") == nullptr);
	TEST(ppc.getField("ppFloat", rfk::EFieldFlags::Public) == nullptr);
	TEST(static_cast<int>(ppc.getField("ppFloat", rfk::EFieldFlags::Private)->getData<float>(&pp)) == 123456);

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
	namespace3::ExampleClass	e;
	rfk::Class const&			ec = namespace3::ExampleClass::staticGetArchetype();

	TEST(ec.getField("ppFloat", rfk::EFieldFlags::Private, false) == nullptr);
	TEST(static_cast<int>(ec.getField("ppFloat", rfk::EFieldFlags::Private, true)->getData<float>(&e)) == 123456);

	TEST(ec.getField("pInt64", rfk::EFieldFlags::Default, true)->getData<unsigned long long>(&e) == 666u);
	ec.getField("pInt64", rfk::EFieldFlags::Default, true)->getData<unsigned long long&>(&e) = 642u;
	TEST(ec.getField("pInt64", rfk::EFieldFlags::Default, true)->getData<unsigned long long>(&e) == 642u);

	TEST(ec.getField("someInt", rfk::EFieldFlags::Public | rfk::EFieldFlags::Mutable)->getData<int>(&e) == 42);
	TEST(ec.getField("someParentClass")->getData<namespace3::ParentClass&>(&e).pInt64 == 666u);
}

void staticFields()
{
	//ExampleClass
	namespace3::ExampleClass	e;
	rfk::Class const&			ec = namespace3::ExampleClass::staticGetArchetype();

	TEST(ec.getField("someStaticInt") == nullptr);
	TEST(ec.getStaticField("someStaticInt") != nullptr);
	TEST(ec.getStaticField("someStaticInt", rfk::EFieldFlags::Public) != nullptr);
	TEST(ec.getStaticField("someStaticInt", rfk::EFieldFlags::Public)->getDataAddress() == &namespace3::ExampleClass::someStaticInt);
	TEST(ec.getStaticField("someStaticInt", rfk::EFieldFlags::Public)->getData<int>() == namespace3::ExampleClass::someStaticInt);

	ec.getStaticField("someStaticInt", rfk::EFieldFlags::Public)->setData(2);

	TEST(namespace3::ExampleClass::someStaticInt == 2);
	TEST(ec.getStaticField("someStaticParentClass", rfk::EFieldFlags::Public)->getDataAddress() == &namespace3::ExampleClass::someStaticParentClass);
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

	//InheritsFrom
	TEST(!ppc.inheritsFrom(ppc));
	TEST(!ppc.inheritsFrom(pc));
	TEST(!ppc.inheritsFrom(pc2));
	TEST(!ppc.inheritsFrom(ec));
	TEST(!ppc.inheritsFrom(oc));

	TEST(pc.inheritsFrom(ppc));
	TEST(!pc.inheritsFrom(pc));
	TEST(!pc.inheritsFrom(pc2));
	TEST(!pc.inheritsFrom(ec));
	TEST(!pc.inheritsFrom(oc));

	TEST(ec.inheritsFrom(ppc));
	TEST(ec.inheritsFrom(pc));
	TEST(ec.inheritsFrom(pc2));
	TEST(!ec.inheritsFrom(ec));
	TEST(!ec.inheritsFrom(oc));

	TEST(!oc.inheritsFrom(ppc));
	TEST(!oc.inheritsFrom(pc));
	TEST(!oc.inheritsFrom(pc2));
	TEST(!oc.inheritsFrom(ec));
	TEST(!oc.inheritsFrom(oc));

	TEST(!pc2.inheritsFrom(ppc));
	TEST(!pc2.inheritsFrom(pc));
	TEST(!pc2.inheritsFrom(pc2));
	TEST(!pc2.inheritsFrom(ec));
	TEST(!pc2.inheritsFrom(oc));
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
	TEST(ecI->someInt == 42);

	//This leaks :) Should clean pcI, pc2I & ecI
	delete pcI;
	delete pc2I;
	delete ecI;
}

void properties()
{
	rfk::Class const& ec = namespace3::ExampleClass::staticGetArchetype();

	TEST(!ec.properties.hasProperty("dynamicGetArchetype"));
	TEST(ec.properties.hasProperty("DynamicGetArchetype"));

	TEST(ec.getStaticMethod("customInstantiator")->properties.hasProperty("CustomInstantiator"));
}

void dynamicTypes()
{
	std::vector<rfk::ReflectedObject*>	objects;

	objects.push_back(new namespace3::ExampleClass());
	objects.push_back(new namespace3::ParentClass());
	objects.push_back(new namespace2::ParentParentClass());

	TEST(objects[0]->getArchetype().name == "ExampleClass");
	TEST(objects[1]->getArchetype().name == "ParentClass");
	TEST(objects[2]->getArchetype().name == "ParentParentClass");

	//Yummy leak
	for (rfk::ReflectedObject* o : objects)
	{
		delete o;
	}
}

void makeInstance()
{
	//ExampleClass has a default constructor, can call makeInstance()
	TEST(namespace3::ExampleClass::staticGetArchetype().makeInstance() != nullptr);
	TEST(namespace3::ExampleClass::staticGetArchetype().makeInstance(1, 3.14f) != nullptr);		//use customInstantiator method
	TEST(namespace3::ExampleClass::staticGetArchetype().makeInstance(10.0f, 3.14f) == nullptr);

	//ExampleClass2 has a deleted default constructor, makeInstance should return nullptr
	TEST(namespace3::ExampleClass2::staticGetArchetype().makeInstance() == nullptr);
	TEST(namespace3::ExampleClass2::staticGetArchetype().makeInstance<namespace3::ExampleClass2>(42)->i == 42);		//use customInstantiator method
}

void entityIdRegistration()
{

}

int main()
{
	namespaces();
	classes();
	structs();
	enums();
	methods();
	staticMethods();
	fields();
	staticFields();
	inheritance();
	instantiation();
	properties();
	dynamicTypes();
	makeInstance();

	return EXIT_SUCCESS;
}