#include <iostream>
#include <type_traits>

#include "ExampleClass.h"

#include "Utility/ICallable.h"
#include "Utility/NonMemberFunction.h"

int tests(std::string someParam)
{
	int const* test = nullptr;

	std::cout << std::is_const<decltype(test)>::value << std::endl;
	std::cout << std::is_const<std::remove_pointer<decltype(test)>::type>::value << std::endl;

	return 1;
}

int main()
{
	std::cout << "RefurekuDemo" << std::endl;

	ExampleClass exampleClass;

	refureku::Type const& exampleClassType = ExampleClass::staticGetType();

	refureku::Method const* method1 = exampleClassType.getMethod("method1");
	if (method1 != nullptr) method1->invoke(&exampleClass);

	//Static methods
	refureku::StaticMethod const* staticMethod1 = exampleClassType.getStaticMethod("staticMethod1");
	if (staticMethod1 != nullptr)
	{
		staticMethod1->invoke();
		staticMethod1->invoke<void>();
	}

	refureku::StaticMethod const* staticMethod2 = exampleClassType.getStaticMethod("staticMethod2");
	if (staticMethod2 != nullptr)
	{
		staticMethod2->invoke();
		std::cout << staticMethod2->invoke<int>() << std::endl;
	}

	refureku::StaticMethod const* staticMethod3 = exampleClassType.getStaticMethod("staticMethod3");
	if (staticMethod3 != nullptr)
	{
		staticMethod3->invoke(std::string("coucou"));
		std::cout << staticMethod3->invoke<int>(std::string("coucou")) << std::endl;
	}

	return EXIT_SUCCESS;
}