#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestStruct.h"
#include "TestClass.h"
#include "TestClass2.h"
#include "TestEnum.h"
#include "TestNamespace.h"
#include "SingleTypeTemplateClassTemplate.h"
#include "MultipleTypeTemplateClassTemplate.h"

//=========================================================
//============== Enum::getEnumValueByName =================
//=========================================================

TEST(Rfk_Enum_getEnumValueByName, ExistantValue)
{
	EXPECT_NE(rfk::getEnum<TestEnum>()->getEnumValueByName("TestEnumValue1"), nullptr);
	EXPECT_NE(rfk::getEnum<TestEnumClass>()->getEnumValueByName("Value1"), nullptr);
}

TEST(Rfk_Enum_getEnumValueByName, NonExistantValue)
{
	EXPECT_EQ(rfk::getEnum<TestEnum>()->getEnumValueByName(""), nullptr);
	EXPECT_EQ(rfk::getEnum<TestEnum>()->getEnumValueByName("UnvalidValue"), nullptr);
	EXPECT_EQ(rfk::getEnum<TestEnum>()->getEnumValueByName("testEnumValue1"), nullptr);	//Test case
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getEnumValueByName(""), nullptr);
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getEnumValueByName("UnvalidValue"), nullptr);
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getEnumValueByName("value1"), nullptr);	//Test case
}

//=========================================================
//================= Enum::getEnumValue ====================
//=========================================================

TEST(Rfk_Enum_getEnumValue, ExistantValue)
{
	EXPECT_NE(rfk::getEnum<TestEnum>()->getEnumValue(0), nullptr);
	EXPECT_NE(rfk::getEnum<TestEnumClass>()->getEnumValue(1 << 1), nullptr);
}

TEST(Rfk_Enum_getEnumValue, NonExistantValue)
{
	EXPECT_EQ(rfk::getEnum<TestEnum>()->getEnumValue(-1), nullptr);
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getEnumValue(-1), nullptr);
}

//=========================================================
//============ Enum::getEnumValueByPredicate ==============
//=========================================================

TEST(Rfk_Enum_getEnumValueByPredicate, NullptrPredicate)
{
	EXPECT_EQ(rfk::getEnum<TestEnum>()->getEnumValueByPredicate(nullptr, nullptr), nullptr);
}

TEST(Rfk_Enum_getEnumValueByPredicate, MatchingValueFound)
{
	rfk::EnumValue const* result = rfk::getEnum<TestEnum>()->getEnumValueByPredicate([](rfk::EnumValue const& ev, void*)
																					 {
																						 return ev.getProperty<BaseTestProperty>() != nullptr;
																					 }, nullptr);

	EXPECT_NE(result, nullptr);
	EXPECT_STREQ(result->getName(), "TestEnumValue1");
}

TEST(Rfk_Enum_getEnumValueByPredicate, NoMatchingValueFound)
{
	rfk::EnumValue const* result = rfk::getEnum<TestEnum>()->getEnumValueByPredicate([](rfk::EnumValue const& ev, void*)
																					 {
																						 return ev.getProperty<MultipleInheritedProperty>() != nullptr;
																					 }, nullptr);

	EXPECT_EQ(result, nullptr);
}

//=========================================================
//================= Enum::getEnumValues ===================
//=========================================================

TEST(Rfk_Enum_getEnumValues, NoValue)
{
	EXPECT_EQ(rfk::getEnum<TestEnum>()->getEnumValues(-1).size(), 0u);
}

TEST(Rfk_Enum_getEnumValues, OneValue)
{
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getEnumValues(1 << 0).size(), 1u);
}

TEST(Rfk_Enum_getEnumValues, MultipleValues)
{
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getEnumValues(1 << 2).size(), 2u);
}

//=========================================================
//============ Enum::getEnumValuesByPredicate =============
//=========================================================

TEST(Rfk_Enum_getEnumValuesByPredicate, NullptrPredicate)
{
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getEnumValuesByPredicate(nullptr, nullptr).size(), 0u);
}

TEST(Rfk_Enum_getEnumValuesByPredicate, MatchingValuesFound)
{
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getEnumValuesByPredicate([](rfk::EnumValue const& ev, void*)
			  {
				  return ev.getName()[0] == 'V';
			  }, nullptr).size()
		, 5u);
}

TEST(Rfk_Enum_getEnumValuesByPredicate, NoMatchingValuesFound)
{
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getEnumValuesByPredicate([](rfk::EnumValue const& ev, void*)
			  {
				  return ev.getName()[0] == 'B';
			  }
		, nullptr).size(), 0u);
}

//=========================================================
//================= Enum::getEnumValueAt ==================
//=========================================================

TEST(Rfk_Enum_getEnumValueAt, getEnumValueAt)
{
	EXPECT_STREQ(rfk::getEnum<TestEnum>()->getEnumValueAt(0).getName(), "TestEnumValue1");
	EXPECT_STREQ(rfk::getEnum<TestEnum>()->getEnumValueAt(1).getName(), "TestEnumValue2");
	EXPECT_STREQ(rfk::getEnum<TestEnum>()->getEnumValueAt(2).getName(), "TestEnumValue3");

	EXPECT_STREQ(rfk::getEnum<TestEnumClass>()->getEnumValueAt(0).getName(), "Value1");
	EXPECT_STREQ(rfk::getEnum<TestEnumClass>()->getEnumValueAt(1).getName(), "Value2");
	EXPECT_STREQ(rfk::getEnum<TestEnumClass>()->getEnumValueAt(2).getName(), "Value3");
	EXPECT_STREQ(rfk::getEnum<TestEnumClass>()->getEnumValueAt(3).getName(), "Value3Alias");
	EXPECT_STREQ(rfk::getEnum<TestEnumClass>()->getEnumValueAt(4).getName(), "Value123");
}

//=========================================================
//=============== Enum::getEnumValuesCount ================
//=========================================================

TEST(Rfk_Enum_getEnumValuesCount, EmptyEnum)
{
	EXPECT_EQ(TestClass2::staticGetArchetype().getNestedEnumByName("PrivateNestedEnum")->getEnumValuesCount(), 0u);
}

TEST(Rfk_Enum_getEnumValuesCount, NotEmptyEnum)
{
	EXPECT_EQ(rfk::getEnum<TestEnum>()->getEnumValuesCount(), 3u);
}

//=========================================================
//============= Enum::getUnderlyingArchetype ==============
//=========================================================

TEST(Rfk_Enum_getUnderlyingArchetype, ImplicitUnderlyingArchetype)
{
	EXPECT_EQ(rfk::getEnum<TestEnum>()->getUnderlyingArchetype().getMemorySize(), sizeof(std::underlying_type_t<TestEnum>));
}

TEST(Rfk_Enum_getUnderlyingArchetype, ExplicitUnderlyingArchetype)
{
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getUnderlyingArchetype(), *rfk::getArchetype<char>());
}

//=========================================================
//================ Enum::foreachEnumValue =================
//=========================================================

TEST(Rfk_Enum_foreachEnumValue, fullLoop)
{
	int counter = 0;

	EXPECT_TRUE(rfk::getEnum<TestEnum>()->foreachEnumValue([](rfk::EnumValue const& ev, void* data)
				{
					(*reinterpret_cast<int*>(data))++;

					return true;
				}, &counter));

	EXPECT_EQ(counter, rfk::getEnum<TestEnum>()->getEnumValuesCount());
}

TEST(Rfk_Enum_foreachEnumValue, breakLoop)
{
	struct Data
	{
		int curItCount = 0;
		int maxItCount = 2;
	} data;

	EXPECT_FALSE(rfk::getEnum<TestEnumClass>()->foreachEnumValue([](rfk::EnumValue const& ev, void* data)
				{
					Data* castData = reinterpret_cast<Data*>(data);

					castData->curItCount++;

					return castData->curItCount != castData->maxItCount;
				}, &data));

	EXPECT_EQ(data.curItCount, data.maxItCount);
}