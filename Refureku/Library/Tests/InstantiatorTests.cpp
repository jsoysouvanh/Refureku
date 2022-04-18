#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "Include/TestInstantiator.h"

//=========================================================
//================= Default Instantiators =================
//=========================================================

TEST(Rfk_Instantiators, DefaultSharedInstantiator)
{
	rfk::SharedPtr<TestInstantiatorBase> ptr = rfk::getDatabase().getFileLevelClassByName("TestInstantiatorBase")->makeSharedInstance<TestInstantiatorBase>();

	EXPECT_NE(ptr, nullptr);
	EXPECT_EQ(ptr->value, 0);
}

TEST(Rfk_Instantiators, DefaultUniqueInstantiator)
{
	rfk::UniquePtr<TestInstantiatorBase> ptr = rfk::getDatabase().getFileLevelClassByName("TestInstantiatorBase")->makeUniqueInstance<TestInstantiatorBase>();

	EXPECT_NE(ptr, nullptr);
	EXPECT_EQ(ptr->value, 0);
}

//=========================================================
//============ Overriden Default Instantiators ============
//=========================================================

TEST(Rfk_Instantiators, OverridenDefaultSharedInstantiator)
{
	rfk::SharedPtr<TestInstantiatorBase> ptr = rfk::getDatabase().getFileLevelClassByName("TestInstantiator")->makeSharedInstance<TestInstantiatorBase>();

	EXPECT_NE(ptr, nullptr);
	EXPECT_EQ(ptr->value, 1);
}

TEST(Rfk_Instantiators, OverridenDefaultUniqueInstantiator)
{
	rfk::UniquePtr<TestInstantiatorBase> ptr = rfk::getDatabase().getFileLevelClassByName("TestInstantiator")->makeUniqueInstance<TestInstantiatorBase>();

	EXPECT_NE(ptr, nullptr);
	EXPECT_EQ(ptr->value, 2);
}

//=========================================================
//================= Unique Instantiators ==================
//=========================================================

TEST(Rfk_Instantiators, DefaultUniqueInstantiatorNoDefaultCtor)
{
	rfk::UniquePtr<TestInstantiatorBase> ptr = rfk::getDatabase().getFileLevelClassByName("TestUniqueInstantiatorNotDefaultCtor")->makeUniqueInstance<TestInstantiatorBase>();

	EXPECT_EQ(ptr, nullptr);
}

TEST(Rfk_Instantiators, DefaultUniqueInstantiatorDefaultCtor)
{
	rfk::UniquePtr<TestInstantiatorBase> ptr = rfk::getDatabase().getFileLevelClassByName("TestUniqueInstantiatorDefaultCtor")->makeUniqueInstance<TestInstantiatorBase>();

	EXPECT_NE(ptr, nullptr);
	EXPECT_EQ(ptr->value, 0);
}

TEST(Rfk_Instantiators, UniqueInstantiatorWithOneArg)
{
	rfk::UniquePtr<TestInstantiatorBase> ptr = rfk::getDatabase().getFileLevelClassByName("TestUniqueInstantiatorNotDefaultCtor")->makeUniqueInstance<TestInstantiatorBase>(10);

	EXPECT_NE(ptr, nullptr);
	EXPECT_EQ(ptr->value, 10);
}

TEST(Rfk_Instantiators, UniqueInstantiatorWithTwoArgs)
{
	rfk::UniquePtr<TestInstantiatorBase> ptr = rfk::getDatabase().getFileLevelClassByName("TestUniqueInstantiatorNotDefaultCtor")->makeUniqueInstance<TestInstantiatorBase>(10, 11);

	EXPECT_NE(ptr, nullptr);
	EXPECT_EQ(ptr->value, 21);
}

TEST(Rfk_Instantiators, InexistantUniqueInstantiator)
{
	rfk::UniquePtr<TestInstantiatorBase> ptr = rfk::getDatabase().getFileLevelClassByName("TestUniqueInstantiatorNotDefaultCtor")->makeUniqueInstance<TestInstantiatorBase>(3.14f);

	EXPECT_EQ(ptr, nullptr);
}

TEST(Rfk_Instantiators, ThrowingUniqueInstantiator)
{
	rfk::Class const* c = rfk::getDatabase().getFileLevelClassByName("TestInstantiator");

	EXPECT_THROW(c->makeUniqueInstance<TestInstantiatorBase>(0), std::logic_error);
}

//=========================================================
//============ Shared Instantiator fallbacks ==============
//=========================================================

TEST(Rfk_Instantiators, sharedInstantiatorOneArgFallback)
{
	rfk::SharedPtr<TestInstantiatorBase> ptr = rfk::getDatabase().getFileLevelClassByName("TestUniqueInstantiatorNotDefaultCtor")->makeSharedInstance<TestInstantiatorBase>(11);

	EXPECT_NE(ptr, nullptr);
	EXPECT_EQ(ptr->value, 11);
}

TEST(Rfk_Instantiators, sharedInstantiatorTwoArgsFallback)
{
	rfk::SharedPtr<TestInstantiatorBase> ptr = rfk::getDatabase().getFileLevelClassByName("TestUniqueInstantiatorNotDefaultCtor")->makeSharedInstance<TestInstantiatorBase>(11, 12);

	EXPECT_NE(ptr, nullptr);
	EXPECT_EQ(ptr->value, 23);
}

TEST(Rfk_Instantiators, sharedInstantiatorNoFallback)
{
	rfk::SharedPtr<TestInstantiatorBase> ptr = rfk::getDatabase().getFileLevelClassByName("TestUniqueInstantiatorNotDefaultCtor")->makeSharedInstance<TestInstantiatorBase>(3.14f);

	EXPECT_EQ(ptr, nullptr);
}

//=========================================================
//============ Unaligned class instantiation ==============
//=========================================================

TEST(Rfk_Instantiators, AlignedClassSharedInstantiation)
{
	rfk::SharedPtr<VirtualClass1> ptr = rfk::getDatabase().getFileLevelClassByName("MultipleInheritanceInstantiator")->makeSharedInstance<VirtualClass1>();

	EXPECT_EQ(ptr->method11(), 3); //OK since VirtualClass1 is the first inherited class -> VirtualClass1 / MultipleInheritanceInstantiator memory offset is 0
}

TEST(Rfk_Instantiators, UnalignedClassSharedInstantiation)
{
	rfk::SharedPtr<VirtualClass2> ptr = rfk::getDatabase().getFileLevelClassByName("MultipleInheritanceInstantiator")->makeSharedInstance<VirtualClass2>();

	EXPECT_EQ(ptr->method22(), 3);
}

TEST(Rfk_Instantiators, AlignedClassUniqueInstantiation)
{
	rfk::UniquePtr<VirtualClass1> ptr = rfk::getDatabase().getFileLevelClassByName("MultipleInheritanceInstantiator")->makeUniqueInstance<VirtualClass1>();

	EXPECT_EQ(ptr->method11(), 3); //OK since VirtualClass1 is the first inherited class -> VirtualClass1 / MultipleInheritanceInstantiator memory offset is 0
}

TEST(Rfk_Instantiators, UnalignedClassUniqueInstantiation)
{
	rfk::UniquePtr<VirtualClass2> ptr = rfk::getDatabase().getFileLevelClassByName("MultipleInheritanceInstantiator")->makeUniqueInstance<VirtualClass2>();

	EXPECT_EQ(ptr->method22(), 3);
}