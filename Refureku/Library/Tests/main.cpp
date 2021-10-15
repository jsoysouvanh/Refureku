#include <gtest/gtest.h>

#include "EntityTests.cpp"
#include "ArchetypeTests.cpp"
#include "EnumTests.cpp"
#include "EnumValueTests.cpp"
#include "FunctionTests.cpp"

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}