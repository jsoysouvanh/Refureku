#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

__RFK_DISABLE_WARNING_PUSH
__RFK_DISABLE_WARNING_UNUSED_RESULT

#include "EntityTests.cpp"
#include "ArchetypeTests.cpp"
#include "EnumTests.cpp"
#include "EnumValueTests.cpp"
#include "TypeTests.cpp"
#include "FunctionBaseTests.cpp"
#include "FunctionTests.cpp"
#include "VariableTests.cpp"
#include "StaticFieldTests.cpp"
#include "FieldTests.cpp"
#include "StructTests.cpp"
#include "NamespaceTests.cpp"
#include "PropertyInheritanceTests.cpp"

__RFK_DISABLE_WARNING_POP

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}