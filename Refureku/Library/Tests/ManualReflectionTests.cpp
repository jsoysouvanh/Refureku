#include <stdexcept>	//std::logic_error

#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "ManualEnumReflection.h"
#include "ManualClassReflection.h"

//=========================================================
//================ Enum manual reflection =================
//=========================================================

TEST(Rfk_ManualReflection, EnumDatabase)
{
	EXPECT_NE(rfk::getDatabase().getFileLevelEnumByName("EManualEnumReflection"), nullptr);
}

TEST(Rfk_ManualReflection, EnumGetArchetype)
{
	EXPECT_NE(rfk::getArchetype<EManualEnumReflection>(), nullptr);
}

TEST(Rfk_ManualReflection, EnumGetEnum)
{
	EXPECT_NE(rfk::getEnum<EManualEnumReflection>(), nullptr);
}

TEST(Rfk_ManualReflection, EnumContent)
{
	rfk::Enum const* e = rfk::getEnum<EManualEnumReflection>();

	EXPECT_NE(e->getEnumValueByName("Value1"), nullptr);
	EXPECT_NE(e->getEnumValueByName("Value2"), nullptr);
	EXPECT_EQ(&e->getEnumValueAt(0), e->getEnumValueByName("Value1"));
	EXPECT_EQ(&e->getEnumValueAt(1), e->getEnumValueByName("Value2"));
}

//=========================================================
//================ Class manual reflection ================
//=========================================================

TEST(Rfk_ManualReflection, ClassDatabase)
{
	EXPECT_NE(rfk::getDatabase().getFileLevelClassByName("ThirdPartyClassWrapper"), nullptr);
}

TEST(Rfk_ManualReflection, ClassGetArchetype)
{
	EXPECT_NE(rfk::getArchetype<ThirdPartyClassWrapper>(), nullptr);
}

TEST(Rfk_ManualReflection, ClassContent)
{
	rfk::Class const* c = rfk::classCast(rfk::getArchetype<ThirdPartyClassWrapper>());

	EXPECT_NE(c->getMethodByName("protectedMethod"), nullptr);

	ThirdPartyClassWrapper instance;
	EXPECT_NO_THROW(c->getMethodByName("protectedMethod")->invoke(instance));

	EXPECT_EQ(c->getMethodByName("getProtectedField")->invoke<int&>(instance), 0);
	EXPECT_NO_THROW(c->getMethodByName("getProtectedField")->invoke<int&>(instance) = 42);
	EXPECT_EQ(c->getMethodByName("getProtectedField")->invoke<int&>(instance), 42);
}

//=========================================================
//============== Variable manual reflection ===============
//=========================================================

TEST(Rfk_ManualReflection, VariableDatabase)
{
	EXPECT_NE(rfk::getDatabase().getFileLevelVariableByName("manuallyReflectedVariable"), nullptr);
}

TEST(Rfk_ManualReflection, VariableContent)
{
	rfk::Variable const* var = rfk::getDatabase().getFileLevelVariableByName("manuallyReflectedVariable");

	EXPECT_STREQ(var->getName(), "manuallyReflectedVariable");
	EXPECT_EQ(var->getType(), rfk::getType<int const>());
	EXPECT_EQ(var->get<int>(), 24);
	EXPECT_FALSE(var->isStatic());
}

//=========================================================
//============== Function manual reflection ===============
//=========================================================

TEST(Rfk_ManualReflection, FunctionDatabase)
{
	EXPECT_NE(rfk::getDatabase().getFileLevelFunctionByName("manuallyReflectedFunction"), nullptr);
}

TEST(Rfk_ManualReflection, FunctionContent)
{
	rfk::Function const* func = rfk::getDatabase().getFileLevelFunctionByName("manuallyReflectedFunction");

	EXPECT_STREQ(func->getName(), "manuallyReflectedFunction");
	EXPECT_EQ(func->getReturnType(), rfk::getType<int>());

	EXPECT_TRUE(func->isInline());
	EXPECT_EQ(func->getParametersCount(), 2u);
	EXPECT_STREQ(func->getParameterAt(0u).getName(), "i");
	EXPECT_EQ(func->getParameterAt(0u).getType(), rfk::getType<int>());
	EXPECT_STREQ(func->getParameterAt(1u).getName(), "j");
	EXPECT_EQ(func->getParameterAt(1u).getType(), rfk::getType<float>());

	EXPECT_EQ(func->invoke<int>(21, 21.1f), 42);
}