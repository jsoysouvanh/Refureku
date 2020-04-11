#include <iostream>

#include "ExampleClass.h"
#include "TypeInfo/Database.h"

#define EXECUTE(FunctionCall) std::cout << #FunctionCall << std::endl; FunctionCall;
#define EXECUTE_RESULT(FunctionCall) std::cout << #FunctionCall << " --> " << FunctionCall << std::endl;

using namespace namespace1;
using namespace namespace2;
using namespace namespace3;

void nonStaticMethods()
{
	ExampleClass		exampleClass;
	ExampleClass const	constExampleClass;
	rfk::Class const&	exampleClassType = ExampleClass::staticGetArchetype();

	//Non const method which returns void without arguments
	rfk::Method const* method1 = exampleClassType.getMethod("method1", rfk::EMethodFlags::Const | rfk::EMethodFlags::Virtual, true);
	if (method1 != nullptr)
	{
		method1->invoke(&exampleClass);
		method1->checkedInvoke(&exampleClass);
		method1->invoke<void>(&exampleClass);
		method1->checkedInvoke<void>(&exampleClass);

		//Note that we can call non-const methods on const objects
		method1->invoke(&constExampleClass);
		method1->checkedInvoke(&constExampleClass);
		method1->invoke<void>(&constExampleClass);
		method1->checkedInvoke<void>(&constExampleClass);
	}

	//Const method which returns void without arguments
	rfk::Method const* method2 = exampleClassType.getMethod("method2");
	if (method2 != nullptr)
	{
		method2->invoke(&exampleClass);
		method2->checkedInvoke(&exampleClass);
		method2->invoke<void>(&exampleClass);
		method2->checkedInvoke<void>(&exampleClass);

		method2->invoke(&constExampleClass);
		method2->checkedInvoke(&constExampleClass);
		method2->invoke<void>(&constExampleClass);
		method2->checkedInvoke<void>(&constExampleClass);
	}

	//Non const method which returns an int without arguments
	rfk::Method const* method3 = exampleClassType.getMethod("method3");
	if (method3 != nullptr)
	{
		method3->invoke(&exampleClass);
		method3->checkedInvoke(&exampleClass);
		std::cout << method3->invoke<int>(&exampleClass) << std::endl;
		std::cout << method3->checkedInvoke<int>(&exampleClass) << std::endl;

		method3->invoke(&constExampleClass);
		method3->checkedInvoke(&constExampleClass);
		std::cout << method3->invoke<int>(&constExampleClass) << std::endl;
		std::cout << method3->checkedInvoke<int>(&constExampleClass) << std::endl;
	}

	//Non const method which returns an int with arguments
	rfk::Method const* method4 = exampleClassType.getMethod("method4");
	if (method4 != nullptr)
	{
		method4->invoke(&exampleClass, nullptr);
		method4->checkedInvoke(&exampleClass, nullptr);
		std::cout << method4->invoke<unsigned long long>(&exampleClass, nullptr) << std::endl;
		std::cout << method4->checkedInvoke<unsigned long long>(&exampleClass, nullptr) << std::endl;

		method4->invoke(&constExampleClass, nullptr);
		method4->checkedInvoke(&constExampleClass, nullptr);
		std::cout << method4->invoke<unsigned long long>(&constExampleClass, nullptr) << std::endl;
		std::cout << method4->checkedInvoke<unsigned long long>(&constExampleClass, nullptr) << std::endl;
	}

	//Private method of a parent class
	rfk::Method const* method5 = exampleClassType.getMethod("parentClassMethod1", rfk::EMethodFlags::Default, true);
	if (method5 != nullptr)
	{
		method5->invoke(&exampleClass);
		method5->checkedInvoke(&exampleClass);

		method5->invoke(&constExampleClass);
		method5->checkedInvoke(&constExampleClass);
	}

	std::vector<rfk::Method const*> methods3 = exampleClassType.getMethods("method3");
	for (auto method : methods3)
	{
		std::cout << method->name << " -> " << (rfk::int32)method->getAccess() << std::endl;
	}
}

void staticMethods()
{
	ExampleClass			exampleClass;
	rfk::Class const&	exampleClassType = ExampleClass::staticGetArchetype();

	rfk::StaticMethod const* staticMethod1 = exampleClassType.getStaticMethod("staticMethod1");
	if (staticMethod1 != nullptr)
	{
		staticMethod1->invoke();
		staticMethod1->checkedInvoke();
		staticMethod1->invoke<void>();
		staticMethod1->checkedInvoke<void>();
	}
	
	rfk::StaticMethod const* staticMethod2 = exampleClassType.getStaticMethod("staticMethod2");
	if (staticMethod2 != nullptr)
	{
		staticMethod2->invoke();
		staticMethod2->checkedInvoke();
		std::cout << staticMethod2->invoke<int>() << std::endl;
		std::cout << staticMethod2->checkedInvoke<int>() << std::endl;
	}

	rfk::StaticMethod const* staticMethod3 = exampleClassType.getStaticMethod("staticMethod3", rfk::EMethodFlags::Protected);
	if (staticMethod3 != nullptr)
	{
		try
		{
			staticMethod3->invoke("coucou");
			staticMethod3->checkedInvoke(static_cast<char const*>("coucou"));
			std::cout << staticMethod3->invoke<int>("coucou") << std::endl;
			std::cout << staticMethod3->checkedInvoke<int>("coucou") << std::endl;
		}
		catch (rfk::MethodError e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

	std::vector<rfk::StaticMethod const*> staticMethods3 = exampleClassType.getStaticMethods("staticMethod3");
	for (auto method : staticMethods3)
	{
		std::cout << method->name << " -> " << (rfk::int32)method->getAccess() << std::endl;
	}
}

void nonStaticFields()
{
	EXECUTE(ExampleClass ec);
	EXECUTE(rfk::Class const& type = ExampleClass::staticGetArchetype());

	std::cout << "Instance address: " << &ec << std::endl;

	EXECUTE(rfk::Field const* field = type.getField("someInt", rfk::EFieldFlags::Public | rfk::EFieldFlags::Mutable));

	if (field != nullptr)
	{
		std::cout << "Found address is  " << field->getDataAddress(&ec) << std::endl;
		std::cout << "Actual address is " << &ec.someInt << std::endl;

		EXECUTE(field->setData(&ec, 1));

		std::cout << field->getData<int>(&ec) << std::endl;
		std::cout << field->getData<int const&>(&ec) << std::endl;
		std::cout << field->getData<int&&>(&ec) << std::endl;

		EXECUTE(field->setData(&ec, 69))

		std::cout << field->getData<int const&>(&ec) << std::endl;
	}

	EXECUTE(rfk::Field const* field2 = type.getField("somePtrToInt"));

	if (field2 != nullptr)
	{
		std::cout << "Found address  is " << field2->getDataAddress(&ec) << std::endl;
		std::cout << "Actual address is " << &ec.somePtrToInt << std::endl;

		std::cout << field2->getData<int*>(&ec) << std::endl;
		std::cout << field2->getData<int*&>(&ec) << std::endl;
		std::cout << field2->getData<int*&&>(&ec) << std::endl;

		EXECUTE(field2->setData(&ec, &ec.someInt))

		std::cout << field2->getData<int*>(&ec) << " -> " << *field2->getData<int*>(&ec) << std::endl;
	}
	
	EXECUTE(rfk::Field const* field3 = type.getField("someParentClass"));

	if (field3 != nullptr)
	{
		std::cout << "Found address is  " << field3->getDataAddress(&ec) << std::endl;
		std::cout << "Actual address is " << &ec.someParentClass << std::endl;
		
		std::cout << "Original is: " << &ec.someParentClass << " -> " << ec.someParentClass << std::endl;

		EXECUTE(ParentClass copy = field3->getData<ParentClass>(&ec));
		std::cout << "Copy is:     " << &copy << " -> " << copy << std::endl;

		EXECUTE(ParentClass& ref = field3->getData<ParentClass&>(&ec));
		std::cout << "Reference is: " << &ref << " -> " << ref << std::endl;

		EXECUTE(ParentClass move = field3->getData<ParentClass&&>(&ec));
		std::cout << "Move is:     " << &move << " -> " << move << std::endl;
	}

	EXECUTE(rfk::Field const* field4 = type.getField("inexistantField"));

	std::cout << "Found field address: " << field4 << std::endl;

	rfk::Field const* field5 = type.getField("ppFloat", rfk::EFieldFlags::Private, true);
	if (field5 != nullptr)
	{
		EXECUTE_RESULT(field5->getDataAddress(&ec));

		EXECUTE(float copy = field5->getData<float>(&ec));
		std::cout << copy << std::endl;

		EXECUTE(field5->setData(&ec, 42.42f));
		EXECUTE_RESULT(field5->getData<float>(&ec));
	}
}

void staticFields()
{
	EXECUTE(rfk::Class const&	type = ExampleClass::staticGetArchetype());

	EXECUTE(rfk::StaticField const*	staticField	= type.getStaticField("someStaticInt"));

	if (staticField != nullptr)
	{
		std::cout << "Found address is  " << staticField->getDataAddress() << std::endl;
		std::cout << "Actual address is " << &ExampleClass::someStaticInt << std::endl;

		EXECUTE(staticField->setData(1));

		std::cout << staticField->getData<int>() << std::endl;
		std::cout << staticField->getData<int const&>() << std::endl;
		std::cout << staticField->getData<int&&>() << std::endl;

		EXECUTE(staticField->setData(69))

		std::cout << staticField->getData<int const&>() << std::endl;
	}

	EXECUTE(rfk::StaticField const*	staticField2	= type.getStaticField("someStaticParentClass"));

	if (staticField2 != nullptr)
	{
		std::cout << "Found address is  " << staticField2->getDataAddress() << std::endl;
		std::cout << "Actual address is " << &ExampleClass::someStaticParentClass << std::endl;

		std::cout << "Original is: " << &ExampleClass::someStaticParentClass << " -> " << ExampleClass::someStaticParentClass << std::endl;
		
		EXECUTE(ParentClass copy = staticField2->getData<ParentClass>())
		std::cout << "Copy is:     " << &copy << " -> " << copy << std::endl;

		EXECUTE(ParentClass& ref = staticField2->getData<ParentClass&>())
		std::cout << "Reference is: " << &ref << " -> " << ref << std::endl;

		EXECUTE(ParentClass move = staticField2->getData<ParentClass&&>())
		std::cout << "Move is:     " << &move << " -> " << move << std::endl;
	}

	EXECUTE(rfk::StaticField const* staticField3 = type.getStaticField("inexistantStaticField"))

	std::cout << "Found field address: " << staticField3 << std::endl;
}

void inheritance()
{
	//rfk::Class const& pppClass = ParentParentParentClass::staticGetArchetype(); //Not reflected type, so can't call staticGetArchetype();
	EXECUTE(rfk::Class const& ppClass = ParentParentClass::staticGetArchetype());
	EXECUTE(rfk::Class const& pClass  = ParentClass::staticGetArchetype());
	EXECUTE(rfk::Class const& p2Class = ParentClass2::staticGetArchetype());
	EXECUTE(rfk::Class const& exClass = ExampleClass::staticGetArchetype());
	EXECUTE(rfk::Class const& oClass  = OtherClass::staticGetArchetype());

	//IsBaseOf
	EXECUTE_RESULT(ppClass.isBaseOf(ppClass));
	EXECUTE_RESULT(ppClass.isBaseOf(pClass));
	EXECUTE_RESULT(ppClass.isBaseOf(p2Class));
	EXECUTE_RESULT(ppClass.isBaseOf(exClass));
	EXECUTE_RESULT(ppClass.isBaseOf(oClass));

	EXECUTE_RESULT(pClass.isBaseOf(ppClass));
	EXECUTE_RESULT(pClass.isBaseOf(pClass));
	EXECUTE_RESULT(pClass.isBaseOf(p2Class));
	EXECUTE_RESULT(pClass.isBaseOf(exClass));
	EXECUTE_RESULT(pClass.isBaseOf(oClass));

	EXECUTE_RESULT(exClass.isBaseOf(ppClass));
	EXECUTE_RESULT(exClass.isBaseOf(pClass));
	EXECUTE_RESULT(exClass.isBaseOf(p2Class));
	EXECUTE_RESULT(exClass.isBaseOf(exClass));
	EXECUTE_RESULT(exClass.isBaseOf(oClass));

	EXECUTE_RESULT(oClass.isBaseOf(ppClass));
	EXECUTE_RESULT(oClass.isBaseOf(pClass));
	EXECUTE_RESULT(oClass.isBaseOf(p2Class));
	EXECUTE_RESULT(oClass.isBaseOf(exClass));
	EXECUTE_RESULT(oClass.isBaseOf(oClass));

	EXECUTE_RESULT(p2Class.isBaseOf(ppClass));
	EXECUTE_RESULT(p2Class.isBaseOf(pClass));
	EXECUTE_RESULT(p2Class.isBaseOf(p2Class));
	EXECUTE_RESULT(p2Class.isBaseOf(exClass));
	EXECUTE_RESULT(p2Class.isBaseOf(oClass));

	//InheritsFrom
	EXECUTE_RESULT(ppClass.inheritsFrom(ppClass));
	EXECUTE_RESULT(ppClass.inheritsFrom(pClass));
	EXECUTE_RESULT(ppClass.inheritsFrom(p2Class));
	EXECUTE_RESULT(ppClass.inheritsFrom(exClass));
	EXECUTE_RESULT(ppClass.inheritsFrom(oClass));

	EXECUTE_RESULT(pClass.inheritsFrom(ppClass));
	EXECUTE_RESULT(pClass.inheritsFrom(pClass));
	EXECUTE_RESULT(pClass.inheritsFrom(p2Class));
	EXECUTE_RESULT(pClass.inheritsFrom(exClass));
	EXECUTE_RESULT(pClass.inheritsFrom(oClass));

	EXECUTE_RESULT(exClass.inheritsFrom(ppClass));
	EXECUTE_RESULT(exClass.inheritsFrom(pClass));
	EXECUTE_RESULT(exClass.inheritsFrom(p2Class));
	EXECUTE_RESULT(exClass.inheritsFrom(exClass));
	EXECUTE_RESULT(exClass.inheritsFrom(oClass));

	EXECUTE_RESULT(oClass.inheritsFrom(ppClass));
	EXECUTE_RESULT(oClass.inheritsFrom(pClass));
	EXECUTE_RESULT(oClass.inheritsFrom(p2Class));
	EXECUTE_RESULT(oClass.inheritsFrom(exClass));
	EXECUTE_RESULT(oClass.inheritsFrom(oClass));

	EXECUTE_RESULT(p2Class.inheritsFrom(ppClass));
	EXECUTE_RESULT(p2Class.inheritsFrom(pClass));
	EXECUTE_RESULT(p2Class.inheritsFrom(p2Class));
	EXECUTE_RESULT(p2Class.inheritsFrom(exClass));
	EXECUTE_RESULT(p2Class.inheritsFrom(oClass));
}

void instantiation()
{
	rfk::Class const& pc	= ParentClass::staticGetArchetype();
	rfk::Class const& pc2	= ParentClass2::staticGetArchetype();
	rfk::Class const& ec	= ExampleClass::staticGetArchetype();

	ParentClass* pcI = pc.makeInstance<ParentClass>();
	ParentClass2* pc2I = pc2.makeInstance<ParentClass2>();
	ExampleClass* ecI = ec.makeInstance<ExampleClass>();

	rfk::Class const& ec2 = ecI->getArchetype();

	std::cout << "makeInstance(): " << pcI->getArchetype().name << std::endl;
	//std::cout << "makeInstance(): " << pc2I->getArchetype().name << std::endl;
	std::cout << "makeInstance(): " << ecI->getArchetype().name << std::endl;

	rfk::Database::getArchetype("ExampleClass")->makeInstance<ExampleClass>();
}

void properties()
{
	rfk::Class const& ec = ExampleClass::staticGetArchetype();

	EXECUTE_RESULT(ec.properties.hasProperty("dynamictype"));
	EXECUTE_RESULT(ec.properties.hasProperty("rfk::ReflectedObject"));
	
	EXECUTE_RESULT(ec.getMethod("method4")->properties.hasProperty("CustomInstantiator"));
}

void reflectedObject()
{
	std::vector<rfk::ReflectedObject*>	objects;

	objects.push_back(new ExampleClass());
	objects.push_back(new ParentClass());
	objects.push_back(new ParentParentClass());

	for (rfk::ReflectedObject* object : objects)
	{
		std::cout << object->getArchetype().name << std::endl;
	}
}

void types()
{
	rfk::StaticMethod const* staticMethod = ExampleClass::staticGetArchetype().getStaticMethod("staticMethod3", rfk::EMethodFlags::Private);

	try
	{
		int v = staticMethod->checkedInvoke<int, int, int>(1, 2);	//<-- wrong arg
		std::cout << v << std::endl;
	}
	catch (rfk::MethodError error)
	{
		std::cerr << error.what() << std::endl;
	}

	try
	{
		staticMethod->checkedInvoke(1, 2);
	}
	catch (rfk::MethodError error)
	{
		std::cerr << error.what() << std::endl;
	}
}

void enums()
{
	rfk::Enum const* e = rfk::Database::getEnum("ExampleEnum");

	std::cout << e->name << " : " << e->values.size() << std::endl;

	for (auto& enumVal : e->values)
		std::cout << enumVal.name << " = " << enumVal.value << std::endl;

	std::cout << e->getEnumValue("ExampleValue4")->value << std::endl;
	std::cout << e->getEnumValue("ExampleValue5")->value << std::endl;
	std::cout << e->getEnumValue("ExampleValue6") << std::endl;
	std::cout << e->getEnumValues(1 << 3).size() << std::endl;
}

int main()
{
	nonStaticMethods();
	staticMethods();
	nonStaticFields();
	staticFields();
	inheritance();
	instantiation();
	properties();
	reflectedObject();
	types();
	enums();

	return EXIT_SUCCESS;
}