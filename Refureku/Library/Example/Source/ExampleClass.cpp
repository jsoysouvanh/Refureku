#include "ExampleClass.h"

#include <iostream>

void ExampleClass::method1()
{
	std::cout << "ExampleClass::method1()" << std::endl;
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

int ExampleClass::staticMethod3(std::string param)
{
	std::cout << "ExampleClass::staticMethod3(" << param << ")" << std::endl;

	return 3;
}