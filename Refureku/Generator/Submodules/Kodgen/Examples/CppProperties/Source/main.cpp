#include <iostream>

#include "SomeClass.h"
#include "SomeOtherClass.h"

int main()
{
	SomeNamespace::np1::SomeClass					someClass;
	SomeNamespace::np1::SomeClass::SomeNestedClass	someNestedClass;

	std::cout << someClass.get_someChar()				<< std::endl;
	std::cout << *someClass.get_someFloat()				<< std::endl;
	std::cout << someClass.get_someInt()				<< std::endl;
	std::cout << someClass.get_someUnsignedLongLong()	<< std::endl;
	std::cout << someClass.get_someString()				<< std::endl;
	someClass.get_someNestedClass();

	someClass.set_someFloat(640.45f);
	someClass.set_someInt(46);
	someClass.set_someUnsignedLongLong(123u);
	someClass.set_someString("This is another test");
	someClass.set_someNestedClass(&someNestedClass);

	std::cout << someClass.get_someChar()				<< std::endl;
	std::cout << someClass.get_someFloat()				<< std::endl;
	std::cout << someClass.get_someInt()				<< std::endl;
	std::cout << someClass.get_someUnsignedLongLong()	<< std::endl;
	std::cout << someClass.get_someString()				<< std::endl;

	SomeNamespace::SomeOtherClass	someOtherClass;

	std::cout << someOtherClass.get_someFloat() << std::endl;

	return EXIT_SUCCESS;
}