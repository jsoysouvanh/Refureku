#include <stdexcept>	//std::logic_error

#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "ManualEnumReflection.h"
#include "ManualClassReflection.h"
#include "ManualClassTemplateReflection.h"

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
//============ Class template manual reflection ===========
//=========================================================

TEST(Rfk_ManualReflection, VectorDatabase)
{
	rfk::Class const* c = rfk::getDatabase().getFileLevelClassByName("Vector");

	EXPECT_NE(c, nullptr);
	EXPECT_NE(rfk::classTemplateCast(c), nullptr);
}

TEST(Rfk_ManualReflection, VectorInstantiation)
{
	VectorDerived<int> vec2;

	rfk::ClassTemplate const* c = rfk::classTemplateCast(rfk::getDatabase().getFileLevelClassByName("Vector"));

	EXPECT_EQ(c->getTemplateInstantiationsCount(), 1u);

	rfk::TypeTemplateArgument arg1(rfk::getType<int>());
	rfk::TemplateArgument const* args[] = { &arg1 };

	rfk::ClassTemplateInstantiation const* inst = c->getTemplateInstantiation(args);

	EXPECT_NE(inst, nullptr);
	EXPECT_NE(rfk::getDatabase().getClassById(inst->getId()), nullptr);
}

TEST(Rfk_ManualReflection, VectorMethods)
{
	rfk::ClassTemplateInstantiation const& c = VectorDerived<int>::staticGetArchetype();
	rfk::Method const* push_backRefMethod = c.getMethodByName<void(int const&)>("push_back", rfk::EMethodFlags::Default, true);
	rfk::Method const* push_backRValMethod = c.getMethodByName<void(int&&)>("push_back", rfk::EMethodFlags::Default, true);
	rfk::Method const* resizeMethod = c.getMethodByName("resize", rfk::EMethodFlags::Default, true);
	rfk::Method const* sizeMethod = c.getMethodByName("size", rfk::EMethodFlags::Default, true);
	rfk::Method const* accessOperator = c.getMethodByName("operator[]", rfk::EMethodFlags::Default, true);

	VectorDerived<int> vec2;

	//size
	EXPECT_EQ(vec2.size(), 0u);
	EXPECT_EQ(vec2.size(), sizeMethod->invoke<std::size_t>(vec2));

	//push_back
	int toPushBack = 42;
	EXPECT_NO_THROW(push_backRefMethod->invoke(vec2, toPushBack));
	EXPECT_NO_THROW((push_backRValMethod->invoke<void, decltype(vec2), int&&>(vec2, 43)));

	EXPECT_EQ(vec2.size(), 2u);
	EXPECT_EQ(vec2.size(), sizeMethod->invoke<std::size_t>(vec2));
	EXPECT_EQ(vec2[0], 42);
	EXPECT_EQ(vec2[1], 43);

	//resize
	EXPECT_NO_THROW(resizeMethod->invoke(vec2, 42u));

	EXPECT_EQ(vec2.size(), 42u);
	EXPECT_EQ(vec2.size(), sizeMethod->invoke<std::size_t>(vec2));
	EXPECT_EQ(vec2[0], 42);
	EXPECT_EQ(vec2[1], 43);

	//operator[]
	EXPECT_NO_THROW((accessOperator->invoke<int&, decltype(vec2), std::size_t>(vec2, 0) = 1));
	EXPECT_EQ(vec2[0], 1);
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

//=========================================================
//============== Namespace manual reflection ==============
//=========================================================

TEST(Rfk_ManualReflection, NamespaceDatabase)
{
	EXPECT_NE(rfk::getDatabase().getNamespaceByName("third_party_namespace"), nullptr);
}

TEST(Rfk_ManualReflection, NamespaceContent)
{
	rfk::Namespace const* np = rfk::getDatabase().getNamespaceByName("third_party_namespace");

	EXPECT_STREQ(np->getName(), "third_party_namespace");
	EXPECT_EQ(np->getOuterEntity(), nullptr);

	rfk::Namespace const* nested_np = rfk::getDatabase().getNamespaceByName("third_party_namespace::nested_third_party_namespace");
	EXPECT_NE(nested_np, nullptr);
	EXPECT_EQ(nested_np->getOuterEntity(), np);

	rfk::Function const* nestedFunc = nested_np->getFunctionByName("thirdPartyFunc");
	EXPECT_NE(nestedFunc, nullptr);
	EXPECT_NE(rfk::getDatabase().getFunctionById(nestedFunc->getId()), nullptr);
	EXPECT_EQ(nestedFunc->getOuterEntity(), nested_np);

	rfk::Enum const* nested_enum = np->getEnumByName("ThirdPartyEnum");
	EXPECT_NE(nested_enum, nullptr);
	EXPECT_NE(rfk::getDatabase().getEnumById(nested_enum->getId()), nullptr);
	EXPECT_EQ(nested_enum->getOuterEntity(), np);
}