#include <iostream>
#include <type_traits>

#include "ExampleClass.h"

void tests()
{
	int const* test = nullptr;

	std::cout << std::is_const<decltype(test)>::value << std::endl;
	std::cout << std::is_const<std::remove_pointer<decltype(test)>::type>::value << std::endl;
}

int main()
{
	std::cout << "RefurekuDemo" << std::endl;

	ExampleClass exampleClass;

	refureku::Type const& exampleClassType = ExampleClass::staticGetType();

	refureku::Method const* method1 = exampleClassType.getMethod("method1");
	if (method1 != nullptr) method1->invoke(&exampleClass);

	refureku::StaticMethod const* staticMethod1 = exampleClassType.getStaticMethod("staticMethod1");
	if (staticMethod1 != nullptr) staticMethod1->invoke();

	return EXIT_SUCCESS;
}