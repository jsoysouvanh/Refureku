#include "ExampleClass.h"

#include <iostream>
#include <cstdint>

using namespace exnamespace;

void ExampleClass::method1() const noexcept
{
	std::cout << "ExampleClass::method1() override:" << std::endl;
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

float ExampleClass::method3(int i) noexcept
{
	std::cout << "ExampleClass::method3(): " << i << std::endl;

	return 3.14f;
}

int ExampleClass::method4(void* ptr)
{
	std::cout << "ExampleClass::method4(void* ptr): " << ptr << std::endl;

	return reinterpret_cast<std::uintptr_t>(ptr);
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

float ExampleClass::staticMethod3(int param) noexcept
{
	return 69.1f;
}

std::ostream& exnamespace::operator<<(std::ostream& stream, ParentClass const& object) noexcept
{
	stream << object.pInt64;

	return stream;
}