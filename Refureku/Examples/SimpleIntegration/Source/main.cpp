#include <iostream>

#include <Refureku/TypeInfo/Database.h>

#include "Dir1/Class1.h"
#include "Dir2/Class2.h"
#include "Dir2/Struct1.h"
#include "Enum1.h"

int main()
{
	std::cout << "RefurekuTest" << std::endl;

	test::Class1	c1;
	Class2			c2;

	rfk::Class const* arch = rfk::Database::getNamespace("test")->getClass("Class1");

	std::cout << arch->name << std::endl;

	rfk::Method const* m = arch->getMethod("method1");
	m->invoke(&c1);

	for (auto& parent : Class2::staticGetArchetype().directParents)
		std::cout << "Parent: " << parent.type->name << std::endl;

	std::cout << Class2::staticGetArchetype().getField("class1")->type.archetype->name << std::endl;
	std::cout << Class2::staticGetArchetype().getField("vec")->type.archetype << std::endl;

	rfk::Struct const* arch2 = rfk::Database::getNamespace("test")->getStruct("Struct1");

	std::cout << arch2->name << std::endl;

	return EXIT_SUCCESS;
}