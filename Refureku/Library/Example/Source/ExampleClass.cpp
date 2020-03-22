#include "ExampleClass.h"

#include <iostream>
#include <cstdint>

void ExampleClass::method1()
{
	std::cout << "ExampleClass::method1(): " << someInt-- << " > " << someInt << std::endl;
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