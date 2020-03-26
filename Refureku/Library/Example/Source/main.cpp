#include <iostream>
#include <type_traits>

#include "ExampleClass.h"

#include "Utility/MemberFunction.h"
#include "Utility/TypeTraits.h"

using namespace exnamespace;

void nonStaticMethods()
{
	ExampleClass			exampleClass;
	ExampleClass const		constExampleClass;
	refureku::Type const&	exampleClassType = ExampleClass::staticGetType();

	// Non const method which returns void without arguments
	refureku::Method const* method1 = exampleClassType.getMethod("method1");
	if (method1 != nullptr)
	{
		method1->invoke(&exampleClass);
		method1->safeInvoke(&exampleClass);
		method1->invoke<void>(&exampleClass);
		method1->safeInvoke<void>(&exampleClass);

		//Note that we can call non-const methods on const objects
		method1->invoke(&constExampleClass);
		method1->safeInvoke(&constExampleClass);
		method1->invoke<void>(&constExampleClass);
		method1->safeInvoke<void>(&constExampleClass);
	}

	// Const method which returns void without arguments
	refureku::Method const* method2 = exampleClassType.getMethod("method2");
	if (method2 != nullptr)
	{
		method2->invoke(&exampleClass);
		method2->safeInvoke(&exampleClass);
		method2->invoke<void>(&exampleClass);
		method2->safeInvoke<void>(&exampleClass);

		method2->invoke(&constExampleClass);
		method2->safeInvoke(&constExampleClass);
		method2->invoke<void>(&constExampleClass);
		method2->safeInvoke<void>(&constExampleClass);
	}

	// Non const method which returns an int without arguments
	refureku::Method const* method3 = exampleClassType.getMethod("method3");
	if (method3 != nullptr)
	{
		method3->invoke(&exampleClass);
		method3->safeInvoke(&exampleClass);
		std::cout << method3->invoke<int>(&exampleClass) << std::endl;
		std::cout << method3->safeInvoke<int>(&exampleClass) << std::endl;

		method3->invoke(&constExampleClass);
		method3->safeInvoke(&constExampleClass);
		std::cout << method3->invoke<int>(&constExampleClass) << std::endl;
		std::cout << method3->safeInvoke<int>(&constExampleClass) << std::endl;
	}

	// Non const method which returns an int with arguments
	refureku::Method const* method4 = exampleClassType.getMethod("method4");
	if (method4 != nullptr)
	{
		method4->invoke(&exampleClass, nullptr);
		method4->safeInvoke(&exampleClass, nullptr);
		std::cout << method4->invoke<int>(&exampleClass, nullptr) << std::endl;
		std::cout << method4->safeInvoke<int>(&exampleClass, nullptr) << std::endl;

		method4->invoke(&constExampleClass, nullptr);
		method4->safeInvoke(&constExampleClass, nullptr);
		std::cout << method4->invoke<int>(&constExampleClass, nullptr) << std::endl;
		std::cout << method4->safeInvoke<int>(&constExampleClass, nullptr) << std::endl;
	}
}

void staticMethods()
{
	ExampleClass			exampleClass;
	refureku::Type const&	exampleClassType = ExampleClass::staticGetType();

	refureku::StaticMethod const* staticMethod1 = exampleClassType.getStaticMethod("staticMethod1");
	if (staticMethod1 != nullptr)
	{
		staticMethod1->invoke();
		staticMethod1->safeInvoke();
		staticMethod1->invoke<void>();
		staticMethod1->safeInvoke<void>();
	}

	refureku::StaticMethod const* staticMethod2 = exampleClassType.getStaticMethod("staticMethod2");
	if (staticMethod2 != nullptr)
	{
		staticMethod2->invoke();
		staticMethod2->safeInvoke();
		std::cout << staticMethod2->invoke<int>() << std::endl;
		std::cout << staticMethod2->safeInvoke<int>() << std::endl;
	}

	refureku::StaticMethod const* staticMethod3 = exampleClassType.getStaticMethod("staticMethod3");
	if (staticMethod3 != nullptr)
	{
		staticMethod3->invoke("coucou");
		staticMethod3->safeInvoke("coucou");
		std::cout << staticMethod3->invoke<int>("coucou") << std::endl;
		std::cout << staticMethod3->safeInvoke<int>("coucou") << std::endl;
	}
}

int main()
{
	//refureku::Type const& type = ExampleClass::staticGetType();
	//
	//std::cout << type.name << std::endl;
	//std::cout << type.id << std::endl;

	//nonStaticMethods();
	//staticMethods();

	//std::cout <<  << std::endl;

	//refureku::Type const& type = TestClass::staticGetType();

	//refureku::Method const* method = type.getMethod("hey", "void(int)const");

	//Test test({ 1, 2, 3 });
	//
	//refureku::Type const& type = ExampleClass::staticGetType();

	//std::cout << "Name: " << type.name << std::endl;
	//std::cout << "Id: " << type.id << std::endl;
	//std::cout << "Category: " << (int)type.category << std::endl;

	//refureku::StaticMethod testMethod = refureku::StaticMethod(new refureku::NonMemberFunction<ExampleClass*()>(&ExampleClass::instantiate));

	//testMethod.invoke<ExampleClass*>();
	//testMethod.invoke<ExampleClass*>(42);

	refureku::Type const& exampleType = ExampleClass::staticGetType();
	//refureku::Type const& parentType = ParentClass::staticGetType();
	//
	//ParentParentParentClass* instance = exampleType.makeInstance<ParentParentParentClass>();

	//if (instance != nullptr)
	//	std::cout << reinterpret_cast<ExampleClass*>(instance)->someInt << std::endl;
	//else
	//	std::cout << "RIP" << std::endl;

	return EXIT_SUCCESS;
}