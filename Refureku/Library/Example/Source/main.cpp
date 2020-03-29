#include <iostream>

#include "ExampleClass.h"

#define EXECUTE(FunctionCall) std::cout << #FunctionCall << std::endl; FunctionCall;

using namespace exnamespace;

void nonStaticMethods()
{
	ExampleClass			exampleClass;
	ExampleClass const		constExampleClass;
	refureku::Class const&	exampleClassType = ExampleClass::staticGetArchetype();

	//Non const method which returns void without arguments
	refureku::Method const* method1 = exampleClassType.getMethod("method1", refureku::EMethodFlags::Const | refureku::EMethodFlags::Virtual, true);
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

	//Const method which returns void without arguments
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

	//Non const method which returns an int without arguments
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

	//Non const method which returns an int with arguments
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

	//Private method of a parent class
	refureku::Method const* method5 = exampleClassType.getMethod("parentClassMethod1", refureku::EMethodFlags::Default, true);
	if (method5 != nullptr)
	{
		method5->invoke(&exampleClass, nullptr);
		method5->safeInvoke(&exampleClass, nullptr);

		method5->invoke(&constExampleClass, nullptr);
		method5->safeInvoke(&constExampleClass, nullptr);
	}

	std::vector<refureku::Method const*> methods3 = exampleClassType.getMethods("method3");
	for (auto method : methods3)
	{
		std::cout << method->name << " -> " << (refureku::int32)method->getAccess() << std::endl;
	}
}

void staticMethods()
{
	ExampleClass			exampleClass;
	refureku::Class const&	exampleClassType = ExampleClass::staticGetArchetype();

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

	std::vector<refureku::StaticMethod const*> staticMethods3 = exampleClassType.getStaticMethods("staticMethod3");
	for (auto method : staticMethods3)
	{
		std::cout << method->name << " -> " << (refureku::int32)method->getAccess() << std::endl;
	}
}

void nonStaticFields()
{
	EXECUTE(ExampleClass ec);
	EXECUTE(refureku::Class const& type = ExampleClass::staticGetArchetype());

	std::cout << "Instance address: " << &ec << std::endl;

	EXECUTE(refureku::Field const* field = type.getField("someInt"));

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

	EXECUTE(refureku::Field const* field2 = type.getField("somePtrToInt"));

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

	std::cout << std::endl << "Search field: " << "someParentClass" << std::endl;
	refureku::Field const*	field3	= type.getField("someParentClass");

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

	EXECUTE(refureku::Field const* field4 = type.getField("inexistantField"));

	std::cout << "Found field address: " << field4 << std::endl;
}

void staticFields()
{
	EXECUTE(refureku::Class const&	type = ExampleClass::staticGetArchetype());

	EXECUTE(refureku::StaticField const*	staticField	= type.getStaticField("someStaticInt"));

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

	EXECUTE(refureku::StaticField const*	staticField2	= type.getStaticField("someStaticParentClass"));

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

	EXECUTE(refureku::StaticField const* staticField3 = type.getStaticField("inexistantStaticField"))

	std::cout << "Found field address: " << staticField3 << std::endl;
}

struct Test;

class Base
{
	friend Test;

	private:
		char	a[8];

	public:
		virtual ~Base() = default;

		template <typename T>
		void registerAndAppendOwnMembers()
		{
			std::cout << std::is_base_of_v<std::decay_t<decltype(*this)>, T> << std::endl;
		}
};

//class Base2 : public Base
//{
//	friend Test;
//
//	private:
//		char	b[4];
//	
//	public:
//		virtual ~Base2() = default;
//
//		template <typename T>
//		void appendOwnMembers(std::vector<uint32_t>& offsets, uint64_t& accumulatedSize)
//		{
//			std::cout << "Offset of b in " << typeid(T).raw_name() << " is " << offsetof(T, b) << std::endl;
//		}
//};
//
//class Base3 : public Base2
//{
//	friend Test;
//
//	private:
//		char	c[8];
//
//	public:
//		virtual ~Base3() = default;
//
//		template <typename T>
//		void registerAndAppendOwnMembers(std::vector<uint32_t>& offsets, uint64_t& accumulatedSize)
//		{
//
//
//			std::cout << "Offset of c in " << typeid(T).raw_name() << " is " << offsetof(T, c) << std::endl;
//		}
//};

class Derived : public Base
{
	friend Test;

	private:
		virtual ~Derived() = default;

		template <typename T>
		void registerAndAppendOwnMembers()
		{
			Base::registerAndAppendOwnMembers<Derived>();
		}
};

struct Test
{
	void method()
	{
		Derived d;
		d.registerAndAppendOwnMembers<Derived>();

		//std::cout << "Offset of a in Derived: " << offsetof(Derived, a) << " + " << sizeof(Derived::a) << " = " << offsetof(Derived, a) + sizeof(Derived::a) << std::endl;
		//std::cout << "Offset of b in Derived: " << offsetof(Derived, b) << " + " << sizeof(Derived::b) << " = " << offsetof(Derived, b) + sizeof(Derived::b) << std::endl;
		//std::cout << "Offset of c in Derived: " << offsetof(Derived, c) << " + " << sizeof(Derived::c) << " = " << offsetof(Derived, c) + sizeof(Derived::c) << std::endl;
	}
};

int main()
{
	//nonStaticMethods();
	//staticMethods();
	//nonStaticFields();
	//staticFields();

	Test t;
	t.method();

	//refureku::Class const& type = ExampleClass::staticGetArchetype();

	return EXIT_SUCCESS;
}