#include <iostream>

#include <TypeInfo/Database.h>

#include "Dir1/Class1.h"
#include "Dir2/Class2.h"
#include "Dir2/Struct1.h"
#include "Enum1.h"

int main()
{
	std::cout << "RefurekuTest" << std::endl;

	test::Class1	c1;
	Class2			c2;
	test::Struct1	s1;
	Enum1			e1;

	rfk::Class const& arch = test::Class1::staticGetArchetype();

	std::cout << arch.name << std::endl;

	rfk::Method const* m = arch.getMethod("method1");
	m->invoke(&c1);

	for (auto& parent : Class2::staticGetArchetype().directParents)
		std::cout << "Parent: " << parent.type->name << std::endl;

	std::cout << Class2::staticGetArchetype().getField("class1")->type.archetype->name << std::endl;
	std::cout << Class2::staticGetArchetype().getField("vec")->type.archetype << std::endl;

	return EXIT_SUCCESS;
}