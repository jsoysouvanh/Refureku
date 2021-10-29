#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestEnum.h"

//=========================================================
//================ EnumValue::getValue<> ==================
//=========================================================

TEST(Rfk_EnumValue_getValueTemplate, getValueTemplate)
{
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getEnumValueAt(0).getValue<rfk::int64>(), 1 << 0);
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getEnumValueAt(1).getValue<TestEnumClass>(), TestEnumClass::Value2);
}

//=========================================================
//================ EnumValue::getValue ====================
//=========================================================

TEST(Rfk_EnumValue_getValue, getValue)
{
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getEnumValueAt(0).getValue(), 1 << 0);
	EXPECT_EQ(rfk::getEnum<TestEnumClass>()->getEnumValueAt(1).getValue(), 1 << 1);
}