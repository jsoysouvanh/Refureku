#include <iostream>
#include <cfloat> //FLT_EPSILON
#include <cmath>  //std::fabs

#include <Refureku/Refureku.h>

#include "AB.h"
#include "ExampleClass.h"
#include "TestPropertyUsage.h"
#include "ThirdPartyEnumReflectionCode.h"
#include "CustomString.h"
#include "ContainerTestClasses.h"

//Template
#include "ClassTemplates/SingleTypeTemplateClassTemplate.h"
#include "ClassTemplates/MultipleTypeTemplateClassTemplate.h"

#define TEST(...) if (!(__VA_ARGS__)) { std::cerr << "Test failed (" << __LINE__ << "): " << #__VA_ARGS__ << std::endl; exit(EXIT_FAILURE); }

bool approximatelyEqual(float value1, float value2, float epsilon = FLT_EPSILON)
{
	return std::fabs(value1 - value2) <= epsilon;
}

void containers()
{
	rfk::Vector<int> intVec;

	TEST(intVec.empty());
	TEST(intVec.capacity() == 0u);

	intVec.push_back(1);
	TEST(!intVec.empty());
	TEST(intVec.capacity() == 1u);

	intVec.push_back(2);
	TEST(intVec.capacity() == 2u);
	TEST(intVec.size() == 2u);

	intVec.push_back(3);
	TEST(intVec.capacity() == 4u);
	TEST(intVec.size() == 3u);
	TEST(intVec.front() == 1);
	TEST(intVec.back() == 3);
	TEST(intVec[0] == 1);
	TEST(intVec[1] == 2);
	TEST(intVec[2] == 3);

	intVec.clear();
	TEST(intVec.empty());

	TEST(HugeClass::getInstanceCount() == 0u);
	{
		rfk::Vector<HugeClass> hugeClassVec;
		TEST(hugeClassVec.capacity() == 0u);

		hugeClassVec.emplace_back();
		TEST(hugeClassVec.capacity() == 1u);

		hugeClassVec.emplace_back(1);
		TEST(hugeClassVec.capacity() == 2u);

		//Trigger realloc here
		hugeClassVec.push_back(HugeClass());
		TEST(hugeClassVec.capacity() == 4u);
		TEST(HugeClass::getInstanceCount() == 3u);

		hugeClassVec.resize(10);
		TEST(HugeClass::getInstanceCount() == 10u);

		hugeClassVec.resize(2);
		TEST(HugeClass::getInstanceCount() == 2u);
	}
	TEST(HugeClass::getInstanceCount() == 0u);

	{
		rfk::Vector<CopyOnly> copyOnlyVec;

		copyOnlyVec.emplace_back();
		copyOnlyVec.emplace_back();
		copyOnlyVec.emplace_back();
	}

	{
		rfk::Vector<MoveOnly> moveOnlyVec;

		moveOnlyVec.emplace_back();
		moveOnlyVec.emplace_back();
		moveOnlyVec.emplace_back();
	}

	{
		//Doesn't compile
		//rfk::Vector<NotCopyNorMove> notCpyNorMoveVec;
	}
}

/*

void entities()
{
	rfk::EntityAPI entity("TestEntity", 12345u, rfk::EEntityKind::Undefined, nullptr);
	entity.setPropertiesCapacity(0);

	TEST(entity.getName() == std::string("TestEntity"));
	TEST(entity.getId() == 12345u);
	TEST(entity.getKind() == rfk::EEntityKind::Undefined);
	TEST(entity.getOuterEntity() == nullptr);

	TestProperty testProperty;
	TestProperty2 testProperty2;

	entity.addProperty(&testProperty);
	entity.addProperty(&testProperty2);

	TEST(entity.getPropertiesCount() == 2u);
	TEST(entity.getPropertyAt(0) == &testProperty);
	TEST(entity.getPropertyAt(1) == &testProperty2);

	TEST(entity.getPropertyByPredicate([](rfk::Property const& prop, void*)
		 {
			 return prop.getArchetypeAPI().getName() == "TestProperty";
		 }, nullptr) == &testProperty);
	TEST(entity.getPropertyByPredicate([](rfk::Property const& prop, void*)
		 {
			 return prop.getArchetypeAPI().getName() == "TestProperty2";
		 }, nullptr) == &testProperty2);

	TEST(entity.getPropertiesByPredicate([](rfk::Property const& prop, void*)
		 {
			 return prop.getArchetype().isSubclassOf(Instantiator::staticGetArchetype());
		 }, nullptr).size() == 0u);

	rfk::EntityAPI entity2("TestEntity2", 6789u, rfk::EEntityKind::Class, nullptr);

	entity.setOuterEntity(&entity2);
	TEST(entity.getOuterEntity() == &entity2);

	entity2.inheritProperties(entity); //Inherit only inheritable properties

	TEST(entity2.getPropertiesCount() == 1u);
	TEST(entity2.getPropertyByPredicate([](rfk::Property const& prop, void*)
		 {
			 return prop.getArchetype().getName() == "TestProperty";
		 }, nullptr) == &testProperty);
	TEST(entity2.getPropertyByPredicate([](rfk::Property const& prop, void*)
		 {
			 return prop.getArchetype().getName() == "TestProperty2";
		 }, nullptr) == nullptr);

	rfk::EntityAPI entity3("TestEntity3", 101112u, rfk::EEntityKind::Enum, nullptr);

	entity3.inheritAllProperties(entity);

	TEST(entity3.getPropertiesCount() == 2u);
	TEST(entity3.getPropertyByPredicate([](rfk::Property const& prop, void*)
		 {
			 return prop.getArchetype().getName() == "TestProperty";
		 }, nullptr) == &testProperty);
	TEST(entity3.getPropertyByPredicate([](rfk::Property const& prop, void*)
		 {
			 return prop.getArchetype().getName() == "TestProperty2";
		 }, nullptr) == &testProperty2);

	TEST(entity3.getPropertiesByPredicate([](rfk::Property const& prop, void*)
		 {
			 return prop.getArchetype().isSubclassOf(Instantiator::staticGetArchetype());
		 }, nullptr).size() == 0u);

	//TODO: Add test getProperty(Struct const& archetype, false)
	//TODO: Add test getProperty(Struct const& archetype, true)
	//TODO: Add test getProperties(Struct const& archetype, false)
	//TODO: Add test getProperties(Struct const& archetype, true)
}

void archetypes()
{
	rfk::ArchetypeAPI archetype("TestArchetype", 123u, rfk::EEntityKind::Struct, 8u, nullptr);

	TEST(archetype.getAccessSpecifier() == rfk::EAccessSpecifier::Undefined);
	
	archetype.setAccessSpecifier(rfk::EAccessSpecifier::Private);
	
	TEST(archetype.getAccessSpecifier() == rfk::EAccessSpecifier::Private);
	TEST(archetype.getMemorySize() == 8u);

	TEST(archetype.getName() == std::string("TestArchetype"));
	TEST(archetype.getId() == 123u);
	TEST(archetype.getKind() == rfk::EEntityKind::Struct);
	TEST(archetype.getPropertiesCount() == 0u);
}

void enumsAndEnumValues()
{
	rfk::ArchetypeAPI intArchetype("int", 1u, rfk::EEntityKind::FundamentalArchetype, sizeof(int), nullptr);
	rfk::EnumAPI enum1("TestEnum1", 123u, &intArchetype, nullptr);

	TEST(enum1.getName() == std::string("TestEnum1"));
	TEST(enum1.getId() == 123u);
	TEST(enum1.getUnderlyingArchetype() == intArchetype);
	TEST(enum1.getKind() == rfk::EEntityKind::Enum);
	TEST(enum1.getMemorySize() == sizeof(int));
	TEST(enum1.getOuterEntity() == nullptr);

	TestProperty testProperty;
	enum1.addProperty(&testProperty);

	TEST(enum1.getPropertiesCount() == 1u);
	TEST(enum1.getPropertyAt(0) == &testProperty);

	enum1.addEnumValue("TestEnumValue1", 10u, 0);
	enum1.addEnumValue("TestEnumValue2", 11u, 1)->addProperty(&testProperty);
	enum1.addEnumValue("TestEnumValue3", 12u, 42);

	TEST(enum1.getEnumValuesCount() == 3u);
	TEST(enum1.getEnumValueAt(0).getName() == std::string("TestEnumValue1"));
	TEST(enum1.getEnumValueAt(0).getKind() == rfk::EEntityKind::EnumValue);

	TEST(enum1.getEnumValue(0) != nullptr);
	TEST(enum1.getEnumValue(2) == nullptr);
	TEST(enum1.getEnumValueByName("TestEnumValue3")->getId() == 12u);
	TEST(enum1.getEnumValueByName("TestEnumValue4") == nullptr);
	TEST(enum1.getEnumValueByPredicate([](rfk::EnumValueAPI const& value, void* userData)
		 {
			 return value.getOuterEntity() == reinterpret_cast<rfk::EnumAPI*>(userData);
		 }, &enum1) != nullptr);
	TEST(enum1.getEnumValueByPredicate([](rfk::EnumValueAPI const& value, void*)
		 {
			 return value.getPropertiesCount() == 1u;
		 }, nullptr) == &enum1.getEnumValueAt(1));

	TEST(enum1.getEnumValueAt(0).getValue<uint16_t>() == 0u);
}

void types()
{
	rfk::TypeAPI const& intType = rfk::getTypeAPI<int>();

	TEST(!intType.isPointer());
	TEST(!intType.isRValueReference());
	TEST(!intType.isVolatile());
	TEST(!intType.isCArray());
	TEST(!intType.isConst());
	TEST(!intType.isLValueReference());
	TEST(intType.isValue());
	//TEST(intType.getArchetype() == rfk::getArchetypeAPI<int>());	//TODO: Uncomment later
	TEST(intType.getTypePartsCount() == 1u);

	rfk::TypeAPI const& floatConstPtrType = rfk::getTypeAPI<float const*>();

	TEST(floatConstPtrType.isPointer());
	TEST(!floatConstPtrType.isRValueReference());
	TEST(!floatConstPtrType.isVolatile());
	TEST(!floatConstPtrType.isCArray());
	TEST(!floatConstPtrType.isConst());
	TEST(!floatConstPtrType.isLValueReference());
	TEST(!floatConstPtrType.isValue());
	//TEST(floatConstPtrType.getArchetype() == rfk::getArchetypeAPI<float>());	//TODO: Uncomment later
	TEST(floatConstPtrType.getTypePartsCount() == 2u);
	TEST(floatConstPtrType.getTypePartAt(1).isValue());
	TEST(floatConstPtrType.getTypePartAt(1).isConst());
}

void fieldsAPI()
{
	//TODO
}

void functionAndMethods()
{
	auto lambda = [](int p1, float p2) -> void { std::cout << "lambda(" << p1 << ", " << p2 << ");" << std::endl; return; };

	rfk::FunctionAPI function("testFunc", 123u, rfk::getTypeAPI<void>(), new rfk::NonMemberFunction<void(int, float)>(lambda), rfk::EFunctionFlags::Inline);
	function.addParameter("p1", 0u, rfk::getTypeAPI<int>());
	function.addParameter("p2", 0u, rfk::getTypeAPI<float>());

	function.invoke<void>(1, 2.0f);
	function.checkedInvoke<void>(3, 4.0f);

	//struct Foo
	//{
	//	int bar(int i, float j) { std::cout << "Foo::bar(" << i << ", " << j << ")" << std::endl; return i + j; }
	//
	//	void baz() const { std::cout << "Foo::baz()" << std::endl; }
	//};

	//rfk::MethodAPI fooBarMethod = rfk::MethodAPI("bar", 123u, rfk::getTypeAPI<int>(), new rfk::MemberFunction<Foo, int(int, float)>(&Foo::bar), rfk::EMethodFlags::Public, nullptr);
	//rfk::MethodAPI fooBazMethod = rfk::MethodAPI("baz", 1234u, rfk::getTypeAPI<void>(), new rfk::MemberFunction<Foo, void()>(&Foo::baz), rfk::EMethodFlags::Public | rfk::EMethodFlags::Const, nullptr);

	//Foo foo;
	//Foo const constFoo;

	//TEST(fooBarMethod.invoke<int>(foo, 1, 2.0f) == 3);
	//TEST(fooBarMethod.invoke<int, Foo, int, float>(foo, 2, 3) == 5);
	//
	//try
	//{
	//	fooBarMethod.invoke<int>(constFoo, 1, 2.0f);
	//	assert(false);
	//}
	//catch (rfk::ConstViolation const& e)
	//{
	//	std::cout << e.what() << std::endl;
	//}

	//fooBazMethod.invoke<void>(constFoo);
	//fooBazMethod.invoke<void>(foo);
}

void outerEntities()
{
	//TEST(rfk::getDatabase().getNamespace("namespace3")->getOuterEntity() == nullptr);
	//TEST(rfk::getDatabase().getNamespace("namespace4")->getNamespace("namespace4_nested")->getOuterEntity() == rfk::getDatabase().getNamespace("namespace4"));
	//TEST(rfk::getDatabase().getNamespace("namespace3")->getClass("AnotherClassInNamespace3")->getOuterEntity() == rfk::getDatabase().getNamespace("namespace3"));
	//TEST(namespace3::ExampleClass::staticGetArchetype().getNestedStruct("NestedExampleStruct")->getOuterEntity() == rfk::getDatabase().getNamespace("namespace3")->getClass("ExampleClass"));
	//TEST(rfk::getDatabase().getNamespace("test1")->getNamespace("test2")->getEnum("NestedEnumInNestedNamespace")->getOuterEntity() == rfk::getDatabase().getNamespace("test1")->getNamespace("test2"));
	//TEST(rfk::getDatabase().getNamespace("test1")->getNamespace("test2")->getEnum("NestedEnumInNestedNamespace")->getEnumValue("SomeValue")->getOuterEntity() == rfk::getDatabase().getNamespace("test1")->getNamespace("test2")->getEnum("NestedEnumInNestedNamespace"));
	//TEST(ExampleStruct::staticGetArchetype().getStaticField("staticInt")->getOuterEntity() == &ExampleStruct::staticGetArchetype());
	//TEST(ExampleStruct::staticGetArchetype().getField("i")->getOuterEntity() == &ExampleStruct::staticGetArchetype());
	//TEST(ExampleStruct::staticGetArchetype().getStaticMethod("staticMethod")->getOuterEntity() == &ExampleStruct::staticGetArchetype());
	//TEST(rfk::getDatabase().getFunction("function1")->getOuterEntity() == nullptr);
	//TEST(rfk::getDatabase().getNamespace("namespace3")->getFunction("function1")->getOuterEntity() == rfk::getDatabase().getNamespace("namespace3"));
	//TEST(rfk::getDatabase().getVariable("variableInsideGlobalScope")->getOuterEntity() == nullptr);
	//TEST(rfk::getDatabase().getNamespace("namespace3")->getVariable("variableInsideNamespace")->getOuterEntity() == rfk::getDatabase().getNamespace("namespace3"));
}

void namespaces()
{
	TEST(rfk::getDatabase().getNamespace("namespace3") != nullptr);
	TEST(rfk::getDatabase().getNamespace(rfk::getDatabase().getNamespace("namespace3")->getId()) != nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace4") != nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace4_nested") == nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace4")->getNamespace("namespace4_nested") != nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getClass("AnotherClassInNamespace3") != nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getClass("OtherClass") != nullptr);
	TEST(rfk::getDatabase().getNamespace("test1")->getNamespace("test2")->getEnum("NestedEnumInNestedNamespace")->getEnumValue("SomeValue")->value() == 42u);
	
	TEST(rfk::getDatabase().getNamespace("namespace3")->getVariable("variableInsideNamespace")->getData<int>() == 42);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getVariable("variableInsideNamespace", rfk::EVarFlags::Static) == nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getVariable("variableInsideGlobalScope") == nullptr);

	rfk::getDatabase().getNamespace("namespace3")->getFunction("functionInsideNamespace", rfk::EFunctionFlags::Inline)->invoke(1);
	rfk::getDatabase().getNamespace("namespace3")->getFunction("functionInsideNamespace", rfk::EFunctionFlags::Default)->invoke(2);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getFunction("functionInsideNamespace", rfk::EFunctionFlags::Static) == nullptr);

	TEST(rfk::getDatabase().getNamespace("namespace3")->getFunction<int(int)>("function1")->rInvoke<int>(1) == 1);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getFunction<int(int, int)>("function1")->rInvoke<int>(1, 2) == 3);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getFunction<void(int, int)>("function1") == nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getFunction<int()>("function1") == nullptr);

	//By predicate
	TEST(rfk::getDatabase().getNamespace("namespace3")->getNamespace([](rfk::Namespace const*) { return true; }) == nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getArchetype([](rfk::Archetype const* a) { return a->getMemorySize() == sizeof(namespace3::ParentClass); }) != nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getStruct([](rfk::Struct const*) { return true; }) == nullptr );
	TEST(rfk::getDatabase().getNamespace("namespace3")->getClass([](rfk::Class const* c) { return c->getName() == "AnotherClassInNamespace3"; }) != nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getEnum([](rfk::Enum const* e) { return e->getEnumValuesCount() == 5; }) != nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getVariable([](rfk::Variable const* v) { return v->getData<int>() == 42; }) != nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getFunction([](rfk::Function const* f) { return f->getReturnType() == rfk::getType<int>() && f->getParameterCount() == 2; }) != nullptr);
}

void classes()
{
	TEST(rfk::getDatabase().getClass("ParentParentParentClass") == nullptr);
	TEST(rfk::getDatabase().getClass(namespace3::ExampleClass::staticGetArchetype().getId()) != nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace2")->getClass("ParentParentClass") != nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getClass("OtherClass") != nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getClass("ParentClass") != nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getClass("ParentClass2") != nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getClass("ExampleClass") != nullptr);
	TEST(rfk::getDatabase().getEnum("ExampleClass") == nullptr);
	TEST(rfk::getDatabase().getStruct("ExampleClass") == nullptr);

	//Nested classes
	TEST(rfk::getDatabase().getNamespace("namespace3")->getClass("ExampleClass")->getNestedClass("NestedExampleClass") != nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getClass("ExampleClass")->getNestedClass("NestedExampleClass", rfk::EAccessSpecifier::Private) != nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getClass("ExampleClass")->getNestedClass("NestedExampleClass", rfk::EAccessSpecifier::Public) == nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getClass("ExampleClass")->getNestedClass("NestedExampleClass")->getField("i") != nullptr);
	TEST(rfk::getDatabase().getNamespace("namespace3")->getClass("ExampleClass")->getNestedStruct("NestedExampleClass") == nullptr);
}

void structs()
{
	//TEST(rfk::getDatabase().getStruct("ExampleStruct") != nullptr);
	//TEST(rfk::getDatabase().getStruct(ExampleStruct::staticGetArchetype().getId()) != nullptr);
	//TEST(rfk::getDatabase().getEnum("ExampleStruct") == nullptr);
	//TEST(rfk::getDatabase().getClass("ExampleStruct") == nullptr);

	//ExampleStruct es;

	//TEST(ExampleStruct::staticGetArchetype().getStaticField("staticInt")->getData<int>() == 123);
	//TEST(ExampleStruct::staticGetArchetype().getField("i")->getData<int>(&es) == 2);
	//
	//ExampleStruct::staticGetArchetype().getStaticMethod("staticMethod")->invoke();
	//ExampleStruct::staticGetArchetype().getMethod("method")->invoke(es, 1, 42.0f);

	//try
	//{
	//	ExampleStruct::staticGetArchetype().getMethod<void(int, float)>("method")->checkedInvoke(es, 1, 2.0f);		//This passes
	//	ExampleStruct::staticGetArchetype().getMethod<void(int, float)>("method")->checkedInvoke(es, "a", "aa");	//This throws
	//	TEST(false);	//Never reach this line
	//}
	//catch (std::exception const& e)
	//{
	//	std::cout << e.what() << std::endl;
	//}

	//TEST(ExampleStruct::staticGetArchetype().getMethod<void(int, int)>("method") == nullptr);	//Bad parameter type
	//TEST(ExampleStruct::staticGetArchetype().getMethod<int(int, float)>("method") == nullptr);	//Bad return type
	//TEST(ExampleStruct::staticGetArchetype().getMethod<void(int, float)>("method") != nullptr);
	//TEST(ExampleStruct::staticGetArchetype().getStaticMethod<void(int, float)>("method") == nullptr);

	////Nested structs
	//TEST(rfk::getDatabase().getNamespace("namespace3")->getClass("ExampleClass")->getNestedStruct("NestedExampleStruct") != nullptr);
	//TEST(rfk::getDatabase().getNamespace("namespace3")->getClass("ExampleClass")->getNestedStruct("NestedExampleStruct", rfk::EAccessSpecifier::Protected) != nullptr);
	//TEST(rfk::getDatabase().getNamespace("namespace3")->getClass("ExampleClass")->getNestedStruct("NestedExampleStruct", rfk::EAccessSpecifier::Public) == nullptr);
	//TEST(rfk::getDatabase().getNamespace("namespace3")->getClass("ExampleClass")->getNestedStruct("NestedExampleStruct")->getMethod<void()>("foo") != nullptr);
	//TEST(rfk::getDatabase().getNamespace("namespace3")->getClass("ExampleClass")->getNestedClass("NestedExampleStruct") == nullptr);

	////Get struct content by predicate
	//TEST(ExampleStruct::staticGetArchetype().getNestedArchetype([](rfk::Archetype const&) { return true; }) == nullptr);
	//TEST(ExampleStruct::staticGetArchetype().getNestedStruct([](rfk::Struct const&) { return true; }) == nullptr);
	//TEST(ExampleStruct::staticGetArchetype().getNestedClass([](rfk::Class const&) { return true; }) == nullptr);
	//TEST(ExampleStruct::staticGetArchetype().getNestedEnum([](rfk::Enum const&) { return true; }) == nullptr);
	//TEST(ExampleStruct::staticGetArchetype().getField([](rfk::Field const& f) { return f.getType() == rfk::getType<int>(); }) != nullptr);
	//TEST(ExampleStruct::staticGetArchetype().getFields([](rfk::Field const&) { return true; }, true).size() == 1u);
	//TEST(ExampleStruct::staticGetArchetype().getStaticField([](rfk::StaticField const& sf) { return sf.getType() == rfk::getType<int>(); }) != nullptr);
	//TEST(ExampleStruct::staticGetArchetype().getStaticFields([](rfk::StaticField const&) { return true; }, true).size() == 1u);
	//TEST(ExampleStruct::staticGetArchetype().getMethod([](rfk::Method const& m) { return m.getParameterCount() == 2u; }, true) != nullptr);
	//TEST(ExampleStruct::staticGetArchetype().getMethods([](rfk::Method const&) { return true; }).size() == 1u);
	//TEST(ExampleStruct::staticGetArchetype().getStaticMethod([](rfk::StaticMethod const& sm) { return sm.getParameterCount() == 0u; }) != nullptr);
	//TEST(ExampleStruct::staticGetArchetype().getStaticMethods([](rfk::StaticMethod const& sm) { return sm.getReturnType() == rfk::getType<void>(); }).size() == 1u);
}

void enums()
{
	//TEST(rfk::getDatabase().getEnum("UnexistantEnum") == nullptr);

	//TEST(rfk::getDatabase().getEnum(rfk::getEnum<namespace3::ExampleEnum>()->getId()) != nullptr);
	//TEST(rfk::getDatabase().getNamespace("namespace3")->getEnum("ExampleEnum") != nullptr);
	//TEST(rfk::getDatabase().getClass("ExampleEnum") == nullptr);
	//TEST(rfk::getDatabase().getStruct("ExampleEnum") == nullptr);

	//rfk::Enum const* e = rfk::getDatabase().getNamespace("namespace3")->getEnum("ExampleEnum");
	//TEST(e != nullptr);

	//TEST(e->getMemorySize() == sizeof(uint8_t));
	//TEST(e->getName() == "ExampleEnum");
	//TEST(e->getEnumValue("ExampleValue1")->value() == 1 << 0);
	//TEST(e->getEnumValue("ExampleValue2")->value() == 1 << 1);
	//TEST(e->getEnumValue("ExampleValue3")->value() == 1 << 2);
	//TEST(e->getEnumValue("ExampleValue4")->value() == 1 << 3);
	//TEST(e->getEnumValue("ExampleValue5")->value() == 1 << 3);
	//TEST(e->getEnumValue(1 << 0)->getName() == "ExampleValue1");
	//TEST(e->getEnumValue(1 << 1)->getName() == "ExampleValue2");
	//TEST(e->getEnumValue(1 << 2)->getName() == "ExampleValue3");
	//TEST(e->getEnumValues(1 << 3).size() == 2);
	//TEST(e->getEnumValue("ExampleValue1") == rfk::getDatabase().getEnumValue(e->getEnumValue("ExampleValue1")->getId()));

	////By predicate
	//TEST(e->getEnumValue([](rfk::EnumValue const& v){ return v.value() == 1 << 3 && v.getName() == "ExampleValue4"; }) != nullptr);
	//TEST(e->getEnumValues([](rfk::EnumValue const& v){ return v.value() == 10; }).empty());

	////Nested enums
	//TEST(rfk::getDatabase().getNamespace("namespace3")->getClass("ExampleClass")->getNestedEnum("NestedExampleEnum")->getEnumValue("Value1")->value() == 0);

	//TEST(rfk::getEnum<C::PublicNestedEnum>() != nullptr);
	//TEST(C::staticGetArchetype().getNestedEnum("PrivateNestedEnum") != nullptr);
	//TEST(C::staticGetArchetype().getNestedClass("PrivateNestedClass")->getNestedEnum("PrivateNestedEnum") != nullptr);

	//rfk::Enum const* nestedEnum = C::staticGetArchetype().getNestedEnum("PrivateNestedEnum");
	//TEST(rfk::getDatabase().getEnum(nestedEnum->getId()) == nestedEnum);

	////Normal enum (no enum class)
	//TEST(rfk::getDatabase().getEnum("EThisIsANormalEnum") != nullptr);

	////Underlying type
	//TEST(rfk::getDatabase().getEnum("EThisIsANormalEnum")->getUnderlyingType().getName() == "int");
}

void methods()
{
	////ParentParentClass
	//rfk::Class const& ppc = namespace2::ParentParentClass::staticGetArchetype();

	//TEST(ppc.getMethod("SomeMethod") == nullptr);

	////ParentClass
	//namespace3::ParentClass	p;
	//rfk::Class const&		pc = namespace3::ParentClass::staticGetArchetype();

	//pc.getMethod("parentClassMethod1")->invoke(p);

	//rfk::Method const* pc_method1 = pc.getMethod("method1", rfk::EMethodFlags::Public | rfk::EMethodFlags::Virtual | rfk::EMethodFlags::Const);
	//TEST(pc_method1->checkedRInvoke<int>(p) == 1);
	//TEST(pc.getMethod("method1", rfk::EMethodFlags::Protected | rfk::EMethodFlags::Virtual | rfk::EMethodFlags::Const) == nullptr);
	//TEST(pc_method1 == rfk::getDatabase().getMethod(pc_method1->getId()));

	////ExampleClass
	//namespace3::ExampleClass	e;
	//rfk::Class const&			ec = namespace3::ExampleClass::staticGetArchetype();

	//rfk::Method const*			ec_method1 = ec.getMethod("method1", rfk::EMethodFlags::Public | rfk::EMethodFlags::Override | rfk::EMethodFlags::Final | rfk::EMethodFlags::Virtual);
	//TEST(ec_method1->rInvoke<int>(e) != 1);
	//TEST(ec_method1->rInvoke<int>(e) == 2);

	//rfk::Method const* ec_method2 = ec.getMethod("method2", rfk::EMethodFlags::Protected | rfk::EMethodFlags::Const);
	//ec_method2->invoke(e);

	//rfk::Method const* ec_method3int = ec.getMethod("method3", rfk::EMethodFlags::Protected);
	//TEST(ec_method3int->rInvoke<int>(e) == 42);

	//rfk::Method const* ec_method3float	= ec.getMethod("method3", rfk::EMethodFlags::Private);
	//
	////Handle functions when they use an incomplete type (forward declared type)
	//rfk::Method const* ec_methodWithForwardDeclaredParam = ec.getMethod<void(D*)>("methodWithForwardDeclaredParam");
	//ec_methodWithForwardDeclaredParam->invoke(e, nullptr);

	//rfk::Method const* ec_methodWithClassParam = ec.getMethod("methodWithClassParam");
	//ec_methodWithClassParam->invoke(e, namespace3::ParentClass());

	//#if RFK_DEBUG

	//try
	//{
	//	ec_method3float->invoke(e);	// <- Bad number of arguments
	//	TEST(false);	//Should not reach this line, throw here ^ in DEBUG only
	//}
	//catch (std::exception const&)
	//{
	//	ec_method3float->invoke(e, 7);	// <- Call with correct arguments count
	//}

	//#else

	//ec_method3float->invoke(e);	// <- This should not throw in release eventhough bad arguments count
	//ec_method3float->invoke(e, 7);

	//#endif

	//rfk::Method const*	ec_method4	= ec.getMethod("method4", rfk::EMethodFlags::Public);
	//TEST(ec_method4->rInvoke<unsigned long long>(e, nullptr) == 0u);

	//try
	//{
	//	ec_method4->checkedRInvoke<unsigned long long>(e, nullptr, 1);		// <- Bad number of arguments
	//	TEST(false);	//Should not reach this line, throw here ^
	//}
	//catch (std::exception const&)
	//{}

	//try
	//{
	//	ec_method4->checkedInvoke<namespace3::ExampleClass, unsigned long long>(e, 1);		// <- Bad argument type
	//	TEST(false);	//Should not reach this line, throw here ^
	//}
	//catch (std::exception const&)
	//{}

	////No lookup in parent classes
	//TEST(ec.getMethod("parentClassMethod1", rfk::EMethodFlags::Private, false) == nullptr);

	////Lookup in parent classes
	//rfk::Method const*	ec_parentClassMethod1 = ec.getMethod("parentClassMethod1", rfk::EMethodFlags::Private, true);
	//TEST(ec_parentClassMethod1 != nullptr);

	//ec_parentClassMethod1->invoke(e);

	////Check const / non-const
	//TEST(ec.getMethod("constMethod", rfk::EMethodFlags::Const) != nullptr);
	//TEST(ec.getMethod<void(int)>("constMethod") == nullptr);
	//TEST(ec.getMethod<void(int) const>("constMethod") != nullptr);
	//TEST(ec.getMethod<void(int) const>("constMethod", rfk::EMethodFlags::Const) != nullptr);

	//TEST(ec.getMethod("method3") != nullptr);			//We don't know if it's the const or non-const overload
	//TEST(ec.getMethod<int(int)>("method3")->rInvoke<int>(e, 1) == 1);	//non-const
	//TEST(ec.getMethod<int(int) const>("method3")->rInvoke<int>(e, 1) == 2);	//const
	//TEST(ec.getMethod("method3", rfk::EMethodFlags::Const)->rInvoke<int>(e, 1) == 2);	//const
	//TEST(ec.getMethod<int(int) const>("method3", rfk::EMethodFlags::Const)->rInvoke<int>(e, 1) == 2);	//const
	//TEST(ec.getMethod<int(int)>("method3", rfk::EMethodFlags::Const) == nullptr);	//Method signature is non const and flag is const -> contradiction

	////Check methods non-const method call throw when instance is const
	//namespace3::ParentClass	const constP;

	//try
	//{
	//	pc.getMethod("parentClassMethod1")->invoke(constP);
	//	TEST(false);
	//}
	//catch (rfk::ConstViolation const&)
	//{
	//}
}

void staticMethods()
{
	////ParentClass
	//rfk::Class const& pc = namespace3::ParentClass::staticGetArchetype();

	//TEST(pc.getStaticMethod("method1") == nullptr);	//Not static

	////ExampleClass
	//rfk::Class const& ec = namespace3::ExampleClass::staticGetArchetype();

	//ec.getStaticMethod("staticMethod1", rfk::EMethodFlags::Private)->invoke();

	//TEST(ec.getStaticMethod("staticMethod1") == rfk::getDatabase().getStaticMethod(ec.getStaticMethod("staticMethod1")->getId()));
	//TEST(ec.getStaticMethod("staticMethod2", rfk::EMethodFlags::Private)->rInvoke<int>() == 2);

	//TEST(ec.getStaticMethod("staticMethod3", rfk::EMethodFlags::Public) == nullptr);

	//TEST(ec.getStaticMethods("staticMethod3").size() == 2u);

	//ec.getStaticMethod("staticMethod3", rfk::EMethodFlags::Protected)->invoke("This is a test, and let's try to make sure it works even when it's long");
	//TEST(ec.getStaticMethod("staticMethod3", rfk::EMethodFlags::Private)->rInvoke<int>(1, 2) == 3);
}

void fields()
{
	////ParentParentClass
	//namespace2::ParentParentClass	pp;
	//rfk::Class const&				ppc = namespace2::ParentParentClass::staticGetArchetype();

	//TEST(ppc.getField("pFloat") == nullptr);
	//TEST(ppc.getField("ppFloat", rfk::EFieldFlags::Public) == nullptr);
	//TEST(static_cast<int>(ppc.getField("ppFloat", rfk::EFieldFlags::Private)->getData<float>(&pp)) == 123456);
	//TEST(ppc.getField("ppFloat", rfk::EFieldFlags::Private) == rfk::getDatabase().getField(ppc.getField("ppFloat", rfk::EFieldFlags::Private)->getId()));

	//ppc.getField("ppFloat", rfk::EFieldFlags::Private)->setData(&pp, 3.14f);

	//TEST(static_cast<int>(ppc.getField("ppFloat", rfk::EFieldFlags::Private)->getData<float>(&pp)) == 3);

	////ParentClass
	//namespace3::ParentClass	p;
	//rfk::Class const&		pc = namespace3::ParentClass::staticGetArchetype();

	//TEST(pc.getField("ppFloat", rfk::EFieldFlags::Private, false) == nullptr);
	//TEST(static_cast<int>(pc.getField("ppFloat", rfk::EFieldFlags::Private, true)->getData<float>(&p)) == 123456);

	//TEST(pc.getField("pInt64")->getData<unsigned long long>(&p) == 666u);
	//pc.getField("pInt64")->getData<unsigned long long&>(&p) = 642u;
	//TEST(pc.getField("pInt64")->getData<unsigned long long>(&p) == 642u);

	////ExampleClass
	//namespace3::ExampleClass	exampleClassInstance;
	//rfk::Class const&			exampleClass = namespace3::ExampleClass::staticGetArchetype();

	//TEST(exampleClass.getField("ppFloat", rfk::EFieldFlags::Private, false) == nullptr);
	//TEST(static_cast<int>(exampleClass.getField("ppFloat", rfk::EFieldFlags::Private, true)->getData<float>(&exampleClassInstance)) == 123456);

	//TEST(exampleClass.getField("pInt64", rfk::EFieldFlags::Default, true)->getData<unsigned long long>(&exampleClassInstance) == 666u);
	//exampleClass.getField("pInt64", rfk::EFieldFlags::Default, true)->getData<unsigned long long&>(&exampleClassInstance) = 642u;
	//TEST(exampleClass.getField("pInt64", rfk::EFieldFlags::Default, true)->getData<unsigned long long>(&exampleClassInstance) == 642u);

	//TEST(exampleClass.getField("someInt", rfk::EFieldFlags::Public | rfk::EFieldFlags::Mutable)->getData<int>(&exampleClassInstance) == 42);
	//TEST(exampleClass.getField("someParentClass")->getData<namespace3::ParentClass&>(&exampleClassInstance).pInt64 == 666u);

	////Make sure const fields can't be set
	//rfk::Class const& eClass = E::staticGetArchetype();
	//E eInstance;

	//try
	//{
	//	eClass.getField("constFloat")->setData(&eInstance, 0);
	//	TEST(false); //Should never pass here
	//}
	//catch (rfk::ConstViolation const&)
	//{
	//}

	//try
	//{
	//	eClass.getField("constFloat")->setData(&eInstance, 42.0f);
	//	TEST(false); //Should never pass here
	//}
	//catch (rfk::ConstViolation const&)
	//{
	//}

	////Make sure that const field can only be get as const
	//try
	//{
	//	eClass.getField("constFloat")->getData<float&&>(&eInstance);
	//	TEST(false);
	//}
	//catch (rfk::ConstViolation const&)
	//{
	//}

	//try
	//{
	//	eClass.getField("constFloat")->getData<float&>(&eInstance);
	//	TEST(false);
	//}
	//catch (rfk::ConstViolation const&)
	//{

	//}

	//try
	//{
	//	eClass.getField("constFloat")->getData<float const&>(&eInstance);
	//}
	//catch (rfk::ConstViolation const&)
	//{
	//	TEST(false);
	//}

	//try
	//{
	//	eClass.getField("constFloat")->getData<float>(&eInstance); //copy is ok
	//}
	//catch (rfk::ConstViolation const&)
	//{
	//	TEST(false);
	//}
}

void staticFields()
{
	////ExampleClass
	//rfk::Class const& ec = namespace3::ExampleClass::staticGetArchetype();

	//TEST(ec.getField("someStaticInt") == nullptr);
	//TEST(ec.getStaticField("someStaticInt") != nullptr);
	//TEST(ec.getStaticField("someStaticInt", rfk::EFieldFlags::Public) != nullptr);
	//TEST(ec.getStaticField("someStaticInt", rfk::EFieldFlags::Public) == rfk::getDatabase().getStaticField(ec.getStaticField("someStaticInt", rfk::EFieldFlags::Public)->getId()));
	//TEST(ec.getStaticField("someStaticInt", rfk::EFieldFlags::Public)->getData<int>() == namespace3::ExampleClass::someStaticInt);
	//
	//ec.getStaticField("someStaticInt", rfk::EFieldFlags::Public)->setData(2);
	//TEST(namespace3::ExampleClass::someStaticInt == 2);

	////Make sure const static fields can't be set
	//rfk::Class const& eClass = E::staticGetArchetype();

	//try
	//{
	//	eClass.getStaticField("staticConstFloat")->setData(nullptr, 0);
	//	TEST(false); //Should never pass here
	//}
	//catch (rfk::ConstViolation const&)
	//{
	//}

	//try
	//{
	//	eClass.getStaticField("staticConstFloat")->setData(42.0f);
	//	TEST(false); //Should never pass here
	//}
	//catch (rfk::ConstViolation const&)
	//{
	//}

	////Make sure that const static field can only be get as const
	//try
	//{
	//	eClass.getStaticField("staticConstFloat")->getData<float&&>();
	//	TEST(false);
	//}
	//catch (rfk::ConstViolation const&)
	//{
	//}

	//try
	//{
	//	eClass.getStaticField("staticConstFloat")->getData<float&>();
	//	TEST(false);
	//}
	//catch (rfk::ConstViolation const&)
	//{

	//}

	//try
	//{
	//	eClass.getStaticField("staticConstFloat")->getData<float const&>();
	//}
	//catch (rfk::ConstViolation const&)
	//{
	//	TEST(false);
	//}

	//try
	//{
	//	eClass.getStaticField("staticConstFloat")->getData<float>(); //copy is ok
	//}
	//catch (rfk::ConstViolation const&)
	//{
	//	TEST(false);
	//}
}

void variables()
{
	TEST(approximatelyEqual(rfk::getDatabase().getVariable("variableInsideGlobalScope", rfk::EVarFlags::Default)->getData<float>(), 10.0f));
	TEST(approximatelyEqual(rfk::getDatabase().getVariable("variableInsideGlobalScope", rfk::EVarFlags::Static)->getData<float>(), 10.0f));
	TEST(rfk::getDatabase().getVariable("variableInsideGlobalScope") == rfk::getDatabase().getVariable(rfk::getDatabase().getVariable("variableInsideGlobalScope")->getId()));

	TEST(rfk::getDatabase().getVariable("variableInsideNamespace") == nullptr);

	//Make sure const variables can't be set
	try
	{
		rfk::getDatabase().getVariable("constGlobalInt")->setData(nullptr, 0);
		TEST(false); //Should never pass here
	}
	catch (rfk::ConstViolation const&)
	{
	}

	try
	{
		rfk::getDatabase().getVariable("constGlobalInt")->setData(32);
		TEST(false); //Should never pass here
	}
	catch (rfk::ConstViolation const&)
	{
	}

	//Make sure that const variables can only be get as const
	try
	{
		rfk::getDatabase().getVariable("constGlobalInt")->getData<float&&>();
		TEST(false);
	}
	catch (rfk::ConstViolation const&)
	{
	}

	try
	{
		rfk::getDatabase().getVariable("constGlobalInt")->getData<float&>();
		TEST(false);
	}
	catch (rfk::ConstViolation const&)
	{

	}

	try
	{
		rfk::getDatabase().getVariable("constGlobalInt")->getData<float const&>();
	}
	catch (rfk::ConstViolation const&)
	{
		TEST(false);
	}

	try
	{
		rfk::getDatabase().getVariable("constGlobalInt")->getData<float>(); //copy is ok
	}
	catch (rfk::ConstViolation const&)
	{
		TEST(false);
	}
}

void functions()
{
	rfk::getDatabase().getFunction("functionInsideGlobalScope", rfk::EFunctionFlags::Default)->invoke(12.f);
	rfk::getDatabase().getFunction("functionInsideGlobalScope", rfk::EFunctionFlags::Static)->invoke(12.f);

	TEST(rfk::getDatabase().getFunction("functionInsideGlobalScope") == rfk::getDatabase().getFunction(rfk::getDatabase().getFunction("functionInsideGlobalScope")->getId()));
	TEST(rfk::getDatabase().getFunction("functionInsideGlobalScope", rfk::EFunctionFlags::Inline) == nullptr);
}

void inheritance()
{
	//rfk::Class const& pppClass = ParentParentParentClass::staticGetArchetype(); //Not reflected type, so can't call staticGetArchetype();
	rfk::ClassAPI const& ppc	= namespace2::ParentParentClass::staticGetArchetype();
	rfk::ClassAPI const& pc		= namespace3::ParentClass::staticGetArchetype();
	rfk::ClassAPI const& pc2	= namespace3::ParentClass2::staticGetArchetype();
	rfk::ClassAPI const& ec		= namespace3::ExampleClass::staticGetArchetype();
	rfk::ClassAPI const& oc		= namespace3::OtherClass::staticGetArchetype();

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
	rfk::ClassAPI const& pc		= namespace3::ParentClass::staticGetArchetype();
	rfk::ClassAPI const& pc2	= namespace3::ParentClass2::staticGetArchetype();
	rfk::ClassAPI const& ec		= namespace3::ExampleClass::staticGetArchetype();

	namespace3::ParentClass*	pcI		= pc.makeInstance<namespace3::ParentClass>();
	namespace3::ParentClass2*	pc2I	= pc2.makeInstance<namespace3::ParentClass2>();
	namespace3::ExampleClass*	ecI		= ec.makeInstance<namespace3::ExampleClass>();

	TEST(&pcI->getArchetypeAPI() == &pc);
	//TEST(&pc2I->getArchetype() == &pc2);	//Can't do that test because ParentClass2 is not a ReflectedObject
	TEST(&ecI->getArchetypeAPI() == &ec);

	TEST(pcI->pInt64 == 666u);
	TEST(ecI->someInt == 1);	//ExampleClass has a custom instantiator without parameters, which sets someInt to 1

	//This leaks :) Should clean pcI, pc2I & ecI
	delete pcI;
	delete pc2I;
	delete ecI;
}

void parseAllNested()
{
	TEST(rfk::getDatabase().getNamespace("parse_all_nested_namespace")->getClass("NestedClass1") != nullptr);
	TEST(rfk::getDatabase().getNamespace("parse_all_nested_namespace")->getStruct("NestedStruct1") != nullptr);
	TEST(rfk::getDatabase().getNamespace("parse_all_nested_namespace")->getEnum("NestedEnum1") != nullptr);
	TEST(rfk::getDatabase().getNamespace("parse_all_nested_namespace")->getNamespace("parse_all_nested_namespace") != nullptr);
}

void properties()
{
	rfk::ClassAPI const& ec = namespace3::ExampleClass::staticGetArchetype();

	//TEST(ec.getStaticMethod("customInstantiator")->getProperty<Instantiator>() != nullptr);

	//rfk::Class const& a = A::staticGetArchetype();

	//TEST(a.getProperty<CustomProperty2>() != nullptr);
	//TEST(a.getProperty(CustomProperty::staticGetArchetype()) != nullptr);
	//TEST(a.getProperties(CustomProperty::staticGetArchetype(), false).size() == 1u);
	//TEST(a.getProperties(CustomProperty::staticGetArchetype(), true).size() == 3u);
	//TEST(a.getProperties<CustomProperty2>().size() == 2u);
	//
	////with predicate
	//TEST(a.getProperty([](rfk::Property const* prop) { return CustomProperty::staticGetArchetype().isBaseOf(prop->getArchetype()); }) != nullptr);

	////Get all properties inheriting from CustomProperty (including CustomProperty)
	//TEST(a.getProperties([](rfk::Property const* prop) { return CustomProperty::staticGetArchetype().isBaseOf(prop->getArchetype()); }).size() == 3u);

	//rfk::Field const* f = a.getField("field");

	//TEST(f->getProperty([](rfk::Property const* prop){ return	prop->getArchetype() == CustomProperty::staticGetArchetype() && 
	//															reinterpret_cast<CustomProperty const*>(prop)->i == 1 &&
	//															reinterpret_cast<CustomProperty const*>(prop)->j == 456; }) != nullptr);
	//TEST(f->getProperties<CustomProperty2>().empty());

	//TEST(a.getMethod([](rfk::Method const& method) { return method.getName() == "testMethod" && method.getParameterCount() == 0u; })->getProperty<Tooltip>()->message == "This is a test");

	////Properties inheritance
	//rfk::Class const& b = B::staticGetArchetype();
	//rfk::Class const& c = C::staticGetArchetype();

	//TEST(b.getProperty<CustomProperty2>() == nullptr);											//CustomProperty2 is not a inherited property
	//TEST(b.getProperty<CustomProperty>()->i == 3 && b.getProperty<CustomProperty>()->j == 4);	//Overriden inherited property
	//TEST(c.getProperty<CustomProperty>()->j == 2);												//Inherited property
	//TEST(c.getMethod("testMethod")->getProperty<Tooltip>()->message == "This is a test");		//Overriden method inherit from base method

	//parseAllNested();
}

void dynamicTypes()
{
	std::vector<rfk::Object*>	objects;

	objects.push_back(new namespace3::ExampleClass());
	objects.push_back(new namespace3::ParentClass());
	objects.push_back(new namespace2::ParentParentClass());

	TEST(objects[0]->getArchetype().getName() == "ExampleClass");
	TEST(objects[1]->getArchetype().getName() == "ParentClass");
	TEST(objects[2]->getArchetype().getName() == "ParentParentClass");

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
	//TEST(rfk::getDatabase().getNamespace("namespace4") != nullptr);
	//TEST(rfk::getDatabase().getNamespace("namespace4::namespace4_nested") != nullptr);
	//TEST(rfk::getDatabase().getNamespace("namespace4_nested") == nullptr);
	//TEST(rfk::getDatabase().getNamespace("namespace4::namespace4_nested::namespace4_nested_nested") != nullptr);
	//
	//try
	//{
	//	TEST(rfk::getDatabase().getNamespace("namespace4::") != nullptr);
	//	TEST(false);	//Should never reach this line
	//}
	//catch (...)
	//{}

	//try
	//{
	//	TEST(rfk::getDatabase().getNamespace("names:pace4") != nullptr);
	//	TEST(false);	//Should never reach this line
	//}
	//catch (...)
	//{}

	//try
	//{
	//	TEST(rfk::getDatabase().getNamespace("namespace4:") != nullptr);
	//	TEST(false);	//Should never reach this line
	//}
	//catch (...)
	//{}

	//TEST(rfk::getDatabase().getFunction<int(int)>("function1")->rInvoke<int>(1) == 1);
	//TEST(rfk::getDatabase().getFunction<int(int, int)>("function1")->rInvoke<int>(1, 2) == 3);
	//TEST(rfk::getDatabase().getFunction<void(int, int)>("function1") == nullptr);
	//TEST(rfk::getDatabase().getFunction<int()>("function1") == nullptr);
	//TEST(rfk::getDatabase().getFunction<void(namespace3::ExampleClass)>("function1") != nullptr);

	////By predicate
	//TEST(rfk::getDatabase().getEntity([](rfk::Entity const* e) { return e->getId() == namespace3::ExampleClass::staticGetArchetype().getId(); }) != nullptr);
	//TEST(rfk::getDatabase().getArchetype([](rfk::Archetype const* a) { return a->getProperty<PropertySettings>() != nullptr; }) != nullptr);
	//TEST(rfk::getDatabase().getStruct([](rfk::Struct const* s) { return s->getMethod("method") != nullptr; })->getName() == "ExampleStruct");
	//TEST(rfk::getDatabase().getClass([](rfk::Class const* c){ CustomProperty const* prop = c->getProperty<CustomProperty>(); return prop != nullptr && prop->i == 3 && prop->j == 4; })->getName() == "B");
	//TEST(rfk::getDatabase().getEnum([](rfk::Enum const* e) { rfk::EnumValue const* ev = e->getEnumValue("Value2"); return ev != nullptr && ev->value() == 1; })->getName() == "EThisIsANormalEnum");
	//TEST(rfk::getDatabase().getFundamentalArchetype([](rfk::FundamentalArchetype const* ft) { return ft->getMemorySize() == 4; }) != nullptr);
	//TEST(rfk::getDatabase().getVariable([](rfk::Variable const* v) { return v->getType() == rfk::getType<float>() && v->getData<float>() == 10.0f; })->getName() == "variableInsideGlobalScope");
	//TEST(rfk::getDatabase().getFunction([](rfk::Function const* f) { return f->getReturnType() == rfk::getType<void>() && f->getParameterCount() == 1 && f->getParameter(0).getType() == rfk::getType<namespace3::ExampleClass>(); })->getName() == "function1");
}

void templateEnums()
{
	TEST(rfk::getEnum<namespace3::ExampleEnum>() == rfk::getDatabase().getNamespace("namespace3")->getEnum("ExampleEnum"));
}

void getArchetypes()
{
	//From database
	TEST(rfk::getDatabase().getArchetype("ExampleStruct") != nullptr);

	//Using templated version
	TEST(rfk::getArchetype<namespace3::ExampleClass>() == rfk::getDatabase().getNamespace("namespace3")->getClass("ExampleClass"));
	TEST(rfk::getArchetype<namespace3::ExampleClass2>() == rfk::getDatabase().getNamespace("namespace3")->getClass("ExampleClass2"));
	TEST(rfk::getDatabase().getArchetype(rfk::getArchetype<Vector3f>()->getId()) == rfk::getArchetype<Vector3f>());

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
	TEST(rfk::entityCast<rfk::Archetype>(rfk::getDatabase().getEntity(rfk::getArchetype<int>()->getId())) != nullptr);
	TEST(rfk::entityCast<rfk::FundamentalArchetype>(rfk::getDatabase().getEntity(rfk::getArchetype<float>()->getId())) != nullptr);

	//Enum
	rfk::Enum const* e = rfk::getEnum<namespace3::ExampleEnum>();

	TEST(rfk::entityCast<rfk::Archetype>(rfk::getDatabase().getEntity(e->getId())) != nullptr);
	TEST(rfk::entityCast<rfk::Enum>(rfk::getDatabase().getEntity(e->getId())) != nullptr);

	//EnumValue
	TEST(rfk::entityCast<rfk::EnumValue>(rfk::getDatabase().getEntity(e->getEnumValue(1)->getId())) != nullptr);

	//Struct
	rfk::StructAPI const& s = ExampleStruct::staticGetArchetype();

	TEST(rfk::entityCast<rfk::Archetype>(rfk::getDatabase().getEntity(s.getId())) != nullptr);
	TEST(rfk::entityCast<rfk::Struct>(rfk::getDatabase().getEntity(s.getId())) != nullptr);

	//Class
	rfk::ClassAPI const& c = namespace3::ExampleClass::staticGetArchetype();

	TEST(rfk::entityCast<rfk::Archetype>(rfk::getDatabase().getEntity(c.getId())) != nullptr);
	TEST(rfk::entityCast<rfk::Struct>(rfk::getDatabase().getEntity(c.getId())) != nullptr);
	TEST(rfk::entityCast<rfk::Class>(rfk::getDatabase().getEntity(c.getId())) != nullptr);

	//Fields
	rfk::FieldAPI const* field = s.getFieldByName("i");
	rfk::StaticFieldAPI const* sField = s.getStaticFieldByName("staticInt");

	TEST(rfk::entityCast<rfk::FieldBase>(rfk::getDatabase().getEntity(field->getId())) != nullptr);
	TEST(rfk::entityCast<rfk::Field>(rfk::getDatabase().getEntity(field->getId())) != nullptr);
	TEST(rfk::entityCast<rfk::FieldBase>(rfk::getDatabase().getEntity(sField->getId())) != nullptr);
	TEST(rfk::entityCast<rfk::StaticField>(rfk::getDatabase().getEntity(sField->getId())) != nullptr);

	//Methods
	rfk::MethodAPI const* method = s.getMethodByName("method");
	rfk::StaticMethodAPI const* sMethod = s.getStaticMethodByName("staticMethod");

	TEST(rfk::entityCast<rfk::MethodBase>(rfk::getDatabase().getEntity(method->getId())) != nullptr);
	TEST(rfk::entityCast<rfk::Method>(rfk::getDatabase().getEntity(method->getId())) != nullptr);
	TEST(rfk::entityCast<rfk::MethodBase>(rfk::getDatabase().getEntity(sMethod->getId())) != nullptr);
	TEST(rfk::entityCast<rfk::StaticMethod>(rfk::getDatabase().getEntity(sMethod->getId())) != nullptr);

	//Namespaces
	TEST(rfk::entityCast<rfk::Namespace>(rfk::getDatabase().getEntity(rfk::getDatabase().getNamespace("namespace3")->getId())) != nullptr);

	//Variables
	TEST(rfk::entityCast<rfk::Variable>(rfk::getDatabase().getEntity(rfk::getDatabase().getVariable("variableInsideGlobalScope")->getId())) != nullptr);

	//Functions
	TEST(rfk::entityCast<rfk::Function>(rfk::getDatabase().getEntity(rfk::getDatabase().getFunction("function1")->getId())) != nullptr);
}

void fundamentalArchetypes()
{
	TEST(rfk::getDatabase().getFundamentalArchetype("int") != nullptr);
	TEST(rfk::getDatabase().getFundamentalArchetype("void") != nullptr);
	TEST(rfk::getDatabase().getFundamentalArchetype("nullptr_t") != nullptr);
}

void enumManualReflection()
{
	rfk::Enum const* e = rfk::getDatabase().getEnum("ThirdPartyEnum");

	TEST(e != nullptr);
	TEST(rfk::getEnum<ThirdPartyEnum>() != nullptr);
	TEST(e == rfk::getEnum<ThirdPartyEnum>());
	TEST(e->getEnumValue("Value1")->value() == 0);
	TEST(e->getEnumValue(2)->getName() == "Value2");
}

void classManualReflection()
{
	rfk::ClassAPI const* vec3archetype = rfk::getDatabaseAPI().getClassByName("Vector3f");

	TEST(vec3archetype != nullptr);
	TEST(vec3archetype->getFieldByName("x") != nullptr);
	TEST(vec3archetype->getFieldByName("y") != nullptr);
	TEST(vec3archetype->getFieldByName("z") != nullptr);
	TEST(vec3archetype->getMethodByName("sqrSize", rfk::EMethodFlags::Public | rfk::EMethodFlags::Inline | rfk::EMethodFlags::Const) != nullptr);
	//TEST(vec3archetype->getStaticMethodByName<float(Vector3f const&, Vector3f const&)>("dot", rfk::EMethodFlags::Public | rfk::EMethodFlags::Inline) != nullptr);

	Vector3f vec{3.14f, 42.0f, 0.0f};

	TEST(approximatelyEqual(vec3archetype->getFieldByName("x")->get<float>(&vec), 3.14f));
	TEST(approximatelyEqual(vec3archetype->getFieldByName("y")->get<float>(&vec), 42.0f));
	TEST(approximatelyEqual(vec3archetype->getFieldByName("z")->get<float>(&vec), 0.0f));

	rfk::ClassAPI const& exampleClassArchetype = namespace3::ExampleClass::staticGetArchetype();
	TEST(exampleClassArchetype.getFieldByName("vec3")->getType().getArchetype() == vec3archetype);
	TEST(exampleClassArchetype.getFieldByName("vec3ptr")->getType().getArchetype() == vec3archetype);
}

void structDirectChildren()
{
	rfk::ClassAPI const& ppClass = namespace2::ParentParentClass::staticGetArchetype();

	TEST(ppClass.getDirectSubclasses().size() == 1u);
}

void testSingleTypeTemplateClassTemplate()
{
	rfk::Class const* c = rfk::getDatabase().getClass("SingleTypeTemplateClassTemplate");

	TEST(c->isTemplate());
	TEST(c->asTemplate()->getProperty<ParseAllNested>() != nullptr);

	TEST(c->asTemplate()->getInstantiation<TestClassA>() != nullptr);

	rfk::ArchetypeAPI const* testClassA[] = { &TestClassA::staticGetArchetype() };
	//TEST(c->asTemplate()->getInstantiation(testClassA) != nullptr);
	//TEST(c->asTemplate()->getInstantiation<TestClassB>() == nullptr);
	//TEST(c->asTemplate()->getInstantiation<int>() == nullptr);
	//TEST(rfk::getDatabase().getEntity(c->asTemplate()->getInstantiation<TestClassA>()->getId()) != nullptr);
	//TEST(rfk::getDatabase().getEntity(c->asTemplate()->getInstantiation<TestClassA>()->getId()) == c->asTemplate()->getInstantiation<TestClassA>());
	//TEST(rfk::getArchetype<SingleTypeTemplateClassTemplate<TestClassA>>() == &SingleTypeTemplateClassTemplate<TestClassA>::staticGetArchetype());
}

void testMultipleTypeTemplateClassTemplate()
{
	//TEST(rfk::getDatabase().getClass("MultipleTypeTemplateClassTemplate") != nullptr);
	//TEST(rfk::getDatabase().getClass("MultipleTypeTemplateClassTemplate")->isTemplate());

	//rfk::ClassTemplate const* c = rfk::getDatabase().getClass("MultipleTypeTemplateClassTemplate")->asTemplate();

	//TEST(c->getTemplateParametersCount() == 3u);

	//TEST(c->getInstantiationsCount() == 3u); //The last implicit instance is at the end of this test function.

	//TEST(c->getInstantiation<int, int, int>() != nullptr);
	//rfk::Archetype const* intintint[] = { rfk::getArchetype<int>(), rfk::getArchetype<int>(), rfk::getArchetype<int>() };
	//TEST(c->getInstantiation(intintint) != nullptr);
	//TEST(c->getInstantiation<int, float, double>() != nullptr);
	//rfk::Archetype const* intfloatdouble[] = { rfk::getArchetype<int>(), rfk::getArchetype<float>(), rfk::getArchetype<double>() };
	//TEST(c->getInstantiation(intfloatdouble) != nullptr);
	//TEST(rfk::getDatabase().getEntity(MultipleTypeTemplateClassTemplate<int, float, double>::staticGetArchetype().getId()) != nullptr);
	//TEST(rfk::getArchetype<MultipleTypeTemplateClassTemplate<int, float, double>>() == &MultipleTypeTemplateClassTemplate<int, float, double>::staticGetArchetype());

	//rfk::ClassTemplateInstantiation const* iiiInstantiation = c->getInstantiation<int, int, int>();

	//TEST(iiiInstantiation->getMethod<int(int const&)>("returnT") != nullptr);
	//TEST(iiiInstantiation->getMethod<int(int const&, int const&)>("returnT") != nullptr);
	//TEST(iiiInstantiation->getMethod("returnT")->getReturnType() == rfk::getType<int>());

	//rfk::ClassTemplateInstantiation const* ifdInstantiation = c->getInstantiation<int, float, double>();
	//MultipleTypeTemplateClassTemplate<int, float, double> o;

	//TEST(ifdInstantiation->getMethod("returnT") != nullptr);
	//TEST(ifdInstantiation->getMethod("returnT")->getReturnType() == rfk::getType<int>());
	//TEST(ifdInstantiation->getMethod<int(int const&, int const&)>("returnT")->rInvoke<int, decltype(o), int const&, int const&>(o, 3, 5) == 8);
	//TEST(ifdInstantiation->getMethod("returnU") != nullptr);
	//TEST(ifdInstantiation->getMethod("returnU")->getReturnType() == rfk::getType<float>());
	//TEST(ifdInstantiation->getMethod("returnV") != nullptr);
	//TEST(ifdInstantiation->getMethod("returnV")->getReturnType() == rfk::getType<double>());
	//TEST(rfk::getDatabase().getVariable("multipleTypeTemplateClassTemplateImplicitInstantiation") != nullptr);
	//TEST(rfk::getDatabase().getVariable("multipleTypeTemplateClassTemplateImplicitInstantiation")->getType().getArchetype() == &o.getArchetype());

	////Must stay at the end of this function to test if the implicit instantiation works
	//MultipleTypeTemplateClassTemplate<double, double, double> implicitelyInstantiated;
}

void templateClasses()
{
	testSingleTypeTemplateClassTemplate();
	testMultipleTypeTemplateClassTemplate();

	//TODO: Test with Single template template class
	//TODO: Test with Multiple template template class
	//TODO: Test with single non-type template class
	//TODO: Test with multiple non-type template class
	//TODO: Test with a mix of the above 3 (like std::array > Type template + non-type template param)
}

void oldTests()
{
	inheritance();
//	classes();
//	structs();
//	database();
//	outerEntities();
//	namespaces();
//	templateEnums();
//	getArchetypes();
//	entityCast();
//	enums();
//	methods();
//	staticMethods();
//	fields();
//	staticFields();
//	variables();
//	functions();
//	instantiation();
//	properties();
//	dynamicTypes();
//	makeInstance();
//	fundamentalArchetypes();
//	enumManualReflection();
//	classManualReflection();
//	structDirectChildren();
//	templateClasses();
}

void newTests()
{
	containers();
	entities();
	archetypes();
	enumsAndEnumValues();
	types();
	fieldsAPI();
	functionAndMethods();
}

*/

int main()
{
	//oldTests();
	//newTests();

	return EXIT_SUCCESS;
}