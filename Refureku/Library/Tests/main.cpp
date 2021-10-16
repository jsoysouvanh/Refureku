#include <gtest/gtest.h>

#include "EntityTests.cpp"
#include "ArchetypeTests.cpp"
#include "EnumTests.cpp"
#include "EnumValueTests.cpp"
#include "TypeTests.cpp"
#include "FunctionBaseTests.cpp"
#include "FunctionTests.cpp"
#include "FunctionParameterTests.cpp"
#include "VariableTests.cpp"
#include "StructTests.cpp"
#include "NamespaceTests.cpp"

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}