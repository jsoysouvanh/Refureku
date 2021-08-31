#include <iostream>
#include <cstdint>

#include "AB.h"

#include "Generated/ExampleClass.rfks.h"

using namespace namespace1;
using namespace namespace2;
using namespace namespace3;

int ExampleStruct::staticInt = 123;

int ExampleClass::method1() const noexcept
{
	return 2;
}

void ExampleClass::method2() const
{
	std::cout << "ExampleClass::method2() const" << std::endl;
}

int ExampleClass::method3()
{
	std::cout << "ExampleClass::method3(): " << 42 << std::endl;

	return 42;
}

int ExampleClass::method3(int i) noexcept
{
	std::cout << "ExampleClass::method3(): " << i << std::endl;

	return 1;
}

int ExampleClass::method3(int i) const noexcept
{
	std::cout << "ExampleClass::method3() const: " << i << std::endl;

	return 2;
}

void ExampleClass::constMethod(int i) const	noexcept
{
	std::cout << "ExampleClass::constMethod(int i): " << i << std::endl;
}

unsigned long long ExampleClass::method4(void* ptr)
{
	std::cout << "ExampleClass::method4(void* ptr): " << ptr << std::endl;

	return static_cast<unsigned long long>(reinterpret_cast<std::uintptr_t>(ptr));
}

void ExampleClass::staticMethod1()
{
	std::cout << "ExampleClass::staticMethod1()" << std::endl;
}

int ExampleClass::staticMethod2()
{
	std::cout << "ExampleClass::staticMethod2()" << std::endl;

	return 2;
}

int ExampleClass::staticMethod3(char const* param)
{
	std::cout << "ExampleClass::staticMethod3(" << param << ")" << std::endl;

	return 3;
}

int ExampleClass::staticMethod3(int p1, int p2) noexcept
{
	return p1 + p2;
}

void ExampleClass::methodWithForwardDeclaredParam(D*)
{
	std::cout << "ExampleClass::methodWithForwardDeclaredParam()" << std::endl;
}

std::ostream& namespace3::operator<<(std::ostream& stream, ParentClass const& object) noexcept
{
	stream << object.pInt64;

	return stream;
}