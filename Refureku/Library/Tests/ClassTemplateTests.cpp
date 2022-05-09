#include <vector>
#include <stdexcept>	//std::logic_error

#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

#include "TestEnum.h"

static rfk::ClassTemplate const* singleTypeClass;
static rfk::ClassTemplate const* multTypeClass;
static rfk::ClassTemplate const* singleNonTypeClass;
static rfk::ClassTemplate const* multNonTypeClass;
static rfk::ClassTemplate const* singleTemplateClass;
static rfk::ClassTemplate const* multTemplateClass;
static rfk::ClassTemplate const* mixedTemplateClass;
static rfk::ClassTemplate const* mixedTemplateClass2;

//=========================================================
//================= Init static variables =================
//=========================================================

TEST(Rfk_ClassTemplate, Init)
{
	singleTypeClass = rfk::classTemplateCast(rfk::getDatabase().getFileLevelClassByName("SingleTypeTemplateClassTemplate"));
	EXPECT_NE(singleTypeClass, nullptr);

	multTypeClass = rfk::classTemplateCast(rfk::getDatabase().getFileLevelClassByName("MultipleTypeTemplateClassTemplate"));
	EXPECT_NE(multTypeClass, nullptr);

	singleNonTypeClass = rfk::classTemplateCast(rfk::getDatabase().getFileLevelClassByName("SingleNonTypeTemplateClassTemplate"));
	EXPECT_NE(singleNonTypeClass, nullptr);

	multNonTypeClass = rfk::classTemplateCast(rfk::getDatabase().getFileLevelClassByName("MultipleNonTypeTemplateClassTemplate"));
	EXPECT_NE(multNonTypeClass, nullptr);

#if RFK_TEMPLATE_TEMPLATE_SUPPORT

	singleTemplateClass = rfk::classTemplateCast(rfk::getDatabase().getFileLevelClassByName("SingleTemplateTemplateClassTemplate"));
	EXPECT_NE(singleTemplateClass, nullptr);

	multTemplateClass = rfk::classTemplateCast(rfk::getDatabase().getFileLevelClassByName("MultipleTemplateTemplateClassTemplate"));
	EXPECT_NE(multTemplateClass, nullptr);

#endif

	mixedTemplateClass = rfk::classTemplateCast(rfk::getDatabase().getFileLevelClassByName("MixedClassTemplate"));
	EXPECT_NE(mixedTemplateClass, nullptr);

	mixedTemplateClass2 = rfk::classTemplateCast(rfk::getDatabase().getFileLevelClassByName("MixedClassTemplate2"));
	EXPECT_NE(mixedTemplateClass2, nullptr);
}

//=========================================================
//======= ClassTemplate::getTemplateParametersCount =======
//=========================================================

TEST(Rfk_ClassTemplate_getTemplateParametersCount, SingleParam)
{
	EXPECT_EQ(singleTypeClass->getTemplateParametersCount(), 1u);
}

TEST(Rfk_ClassTemplate_getTemplateParametersCount, MultipleParams)
{
	EXPECT_EQ(multTypeClass->getTemplateParametersCount(), 3u);
}

//=========================================================
//========= ClassTemplate::getTemplateParameterAt =========
//=========================================================

TEST(Rfk_ClassTemplate_getTemplateParameterAt, TypeTemplateParameters)
{
	EXPECT_STREQ(singleTypeClass->getTemplateParameterAt(0).getName(), "T");
	EXPECT_EQ(singleTypeClass->getTemplateParameterAt(0).getKind(), rfk::ETemplateParameterKind::TypeTemplateParameter);

	EXPECT_STREQ(multTypeClass->getTemplateParameterAt(0).getName(), "T");
	EXPECT_EQ(multTypeClass->getTemplateParameterAt(0).getKind(), rfk::ETemplateParameterKind::TypeTemplateParameter);
	EXPECT_STREQ(multTypeClass->getTemplateParameterAt(1).getName(), "U");
	EXPECT_EQ(multTypeClass->getTemplateParameterAt(1).getKind(), rfk::ETemplateParameterKind::TypeTemplateParameter);
	EXPECT_STREQ(multTypeClass->getTemplateParameterAt(2).getName(), "V");
	EXPECT_EQ(multTypeClass->getTemplateParameterAt(2).getKind(), rfk::ETemplateParameterKind::TypeTemplateParameter);
}

TEST(Rfk_ClassTemplate_getTemplateParameterAt, NonTypeTemplateParameters)
{
	EXPECT_STREQ(singleNonTypeClass->getTemplateParameterAt(0).getName(), "Value");
	EXPECT_EQ(singleNonTypeClass->getTemplateParameterAt(0).getKind(), rfk::ETemplateParameterKind::NonTypeTemplateParameter);

	EXPECT_STREQ(multNonTypeClass->getTemplateParameterAt(0).getName(), "EnumClass");
	EXPECT_EQ(multNonTypeClass->getTemplateParameterAt(0).getKind(), rfk::ETemplateParameterKind::NonTypeTemplateParameter);
	EXPECT_STREQ(multNonTypeClass->getTemplateParameterAt(1).getName(), "Size");
	EXPECT_EQ(multNonTypeClass->getTemplateParameterAt(1).getKind(), rfk::ETemplateParameterKind::NonTypeTemplateParameter);
}

#if RFK_TEMPLATE_TEMPLATE_SUPPORT

TEST(Rfk_ClassTemplate_getTemplateParameterAt, TemplateTemplateParameters)
{
	EXPECT_STREQ(singleTemplateClass->getTemplateParameterAt(0).getName(), "T");
	EXPECT_EQ(singleTemplateClass->getTemplateParameterAt(0).getKind(), rfk::ETemplateParameterKind::TemplateTemplateParameter);

	EXPECT_STREQ(multTemplateClass->getTemplateParameterAt(0).getName(), "T");
	EXPECT_EQ(multTemplateClass->getTemplateParameterAt(0).getKind(), rfk::ETemplateParameterKind::TemplateTemplateParameter);
	EXPECT_STREQ(multTemplateClass->getTemplateParameterAt(1).getName(), "U");
	EXPECT_EQ(multTemplateClass->getTemplateParameterAt(1).getKind(), rfk::ETemplateParameterKind::TemplateTemplateParameter);
}

#endif

TEST(Rfk_ClassTemplate_getTemplateParameterAt, MixedTemplateParameters)
{
	EXPECT_STREQ(mixedTemplateClass->getTemplateParameterAt(0).getName(), "T");
	EXPECT_EQ(mixedTemplateClass->getTemplateParameterAt(0).getKind(), rfk::ETemplateParameterKind::TypeTemplateParameter);
	EXPECT_STREQ(mixedTemplateClass->getTemplateParameterAt(1).getName(), "Size");
	EXPECT_EQ(mixedTemplateClass->getTemplateParameterAt(1).getKind(), rfk::ETemplateParameterKind::NonTypeTemplateParameter);

	EXPECT_STREQ(mixedTemplateClass2->getTemplateParameterAt(0).getName(), "T");
	EXPECT_EQ(mixedTemplateClass2->getTemplateParameterAt(0).getKind(), rfk::ETemplateParameterKind::TypeTemplateParameter);
	EXPECT_STREQ(mixedTemplateClass2->getTemplateParameterAt(1).getName(), "Size");
	EXPECT_EQ(mixedTemplateClass2->getTemplateParameterAt(1).getKind(), rfk::ETemplateParameterKind::NonTypeTemplateParameter);
	EXPECT_STREQ(mixedTemplateClass2->getTemplateParameterAt(2).getName(), "U");
	EXPECT_EQ(mixedTemplateClass2->getTemplateParameterAt(2).getKind(), rfk::ETemplateParameterKind::TemplateTemplateParameter);
}

//=========================================================
//======= ClassTemplate::getTemplateInstantiation<> =======
//=========================================================

TEST(Rfk_ClassTemplate_getTemplateInstantiationTemplate, ExistingTypeTemplateInstantiation)
{
	rfk::TypeTemplateArgument arg1(rfk::getType<int>());
	rfk::TypeTemplateArgument arg2(rfk::getType<float>());
	rfk::TypeTemplateArgument arg3(rfk::getType<double>());
	rfk::TemplateArgument const* templateArgs[] = { &arg1, &arg2, &arg3 };

	EXPECT_NE(multTypeClass->getTemplateInstantiation(templateArgs), nullptr);
}

TEST(Rfk_ClassTemplate_getTemplateInstantiationTemplate, NonExistingTypeTemplateInstantiation)
{
	rfk::TypeTemplateArgument arg1(rfk::getType<int>());
	rfk::TypeTemplateArgument arg2(rfk::getType<float>());
	rfk::TypeTemplateArgument arg3(rfk::getType<long double>());
	rfk::TemplateArgument const* templateArgs[] = { &arg1, &arg2, &arg3 };

	EXPECT_EQ(multTypeClass->getTemplateInstantiation(templateArgs), nullptr);
}

TEST(Rfk_ClassTemplate_getTemplateInstantiationTemplate, ExistingNonTypeTemplateInstantiation)
{
	std::size_t arg1Value = 1u;
	rfk::NonTypeTemplateArgument arg1(arg1Value);
	rfk::TemplateArgument const* templateArgs[] = { &arg1 };

	EXPECT_NE(singleNonTypeClass->getTemplateInstantiation(templateArgs), nullptr);

	EXPECT_EQ(singleNonTypeClass->getTemplateInstantiation(templateArgs)->getFieldByName("intArray")->getType().getCArraySize(), 1u);
}

TEST(Rfk_ClassTemplate_getTemplateInstantiationTemplate, NonExistingNonTypeTemplateInstantiation)
{
	std::size_t arg1Value = 0u;
	rfk::NonTypeTemplateArgument arg1(arg1Value);
	rfk::TemplateArgument const* templateArgs[] = { &arg1 };

	EXPECT_EQ(singleNonTypeClass->getTemplateInstantiation(templateArgs), nullptr);
}

#if RFK_TEMPLATE_TEMPLATE_SUPPORT

TEST(Rfk_ClassTemplate_getTemplateInstantiationTemplate, ExistingTemplateTemplateInstantiation)
{
	rfk::TemplateTemplateArgument arg1(rfk::classTemplateCast(rfk::getDatabase().getFileLevelClassByName("SingleTypeTemplateClassTemplate")));
	rfk::TemplateArgument const* templateArgs[] = { &arg1 };

	EXPECT_NE(singleTemplateClass->getTemplateInstantiation(templateArgs), nullptr);
}

TEST(Rfk_ClassTemplate_getTemplateInstantiationTemplate, NonExistingTemplateTemplateInstantiation)
{
	rfk::TemplateTemplateArgument arg1(rfk::classTemplateCast(rfk::getDatabase().getFileLevelClassByName("MultTypeTemplateClassTemplate")));
	rfk::TemplateArgument const* templateArgs[] = { &arg1 };

	EXPECT_EQ(singleTemplateClass->getTemplateInstantiation(templateArgs), nullptr);
}

#endif

TEST(Rfk_ClassTemplate_getTemplateInstantiationTemplate, ExistingMixedTemplateInstantiation)
{
	rfk::TypeTemplateArgument arg1(rfk::getType<int>());

	std::size_t arg2Value = 1u;
	rfk::NonTypeTemplateArgument arg2(arg2Value);

	rfk::TemplateArgument const* templateArgs[] = { &arg1, &arg2 };

	EXPECT_NE(mixedTemplateClass->getTemplateInstantiation(templateArgs), nullptr);
}

TEST(Rfk_ClassTemplate_getTemplateInstantiationTemplate, NonExistingMixedTemplateInstantiation)
{
	rfk::TypeTemplateArgument arg1(rfk::getType<float>());

	std::size_t arg2Value = 1u;
	rfk::NonTypeTemplateArgument arg2(arg2Value);

	rfk::TemplateArgument const* templateArgs[] = { &arg1, &arg2 };

	EXPECT_EQ(mixedTemplateClass->getTemplateInstantiation(templateArgs), nullptr);
}

//=========================================================
//======== ClassTemplate::getTemplateInstantiation ========
//=========================================================

TEST(Rfk_ClassTemplate_getTemplateInstantiation, ExistingTypeTemplateInstantiation)
{
	rfk::TypeTemplateArgument arg1(rfk::getType<int>());
	std::vector<rfk::TemplateArgument const*> templateArgs{ &arg1 };

	EXPECT_NE(singleTypeClass->getTemplateInstantiation(templateArgs.data(), templateArgs.size()), nullptr);
}

TEST(Rfk_ClassTemplate_getTemplateInstantiation, NonExistingTypeTemplateInstantiation)
{
	rfk::TypeTemplateArgument arg1(rfk::getType<long double>());
	std::vector<rfk::TemplateArgument const*> templateArgs{ &arg1 };

	EXPECT_EQ(singleTypeClass->getTemplateInstantiation(templateArgs.data(), templateArgs.size()), nullptr);
}

TEST(Rfk_ClassTemplate_getTemplateInstantiation, ExistingNonTypeTemplateInstantiation)
{
	constexpr TestEnumClass const arg1Value = TestEnumClass::Value1;
	rfk::NonTypeTemplateArgument arg1(arg1Value);
	
	constexpr std::size_t const arg2Value = 0u;
	rfk::NonTypeTemplateArgument arg2(arg2Value);

	std::vector<rfk::TemplateArgument const*> templateArgs{ &arg1, &arg2 };

	EXPECT_NE(multNonTypeClass->getTemplateInstantiation(templateArgs.data(), templateArgs.size()), nullptr);
}

TEST(Rfk_ClassTemplate_getTemplateInstantiation, NonExistingNonTypeTemplateInstantiation)
{
	constexpr TestEnumClass const arg1Value = TestEnumClass::Value2;
	rfk::NonTypeTemplateArgument arg1(arg1Value);

	constexpr std::size_t const arg2Value = 0u;
	rfk::NonTypeTemplateArgument arg2(arg2Value);

	std::vector<rfk::TemplateArgument const*> templateArgs{ &arg1, &arg2 };

	EXPECT_EQ(multNonTypeClass->getTemplateInstantiation(templateArgs.data(), templateArgs.size()), nullptr);
}

#if RFK_TEMPLATE_TEMPLATE_SUPPORT

TEST(Rfk_ClassTemplate_getTemplateInstantiation, ExistingTemplateTemplateInstantiation)
{
	rfk::TemplateTemplateArgument arg1(rfk::classTemplateCast(rfk::getDatabase().getFileLevelClassByName("MultipleTypeTemplateClassTemplate")));
	rfk::TemplateTemplateArgument arg2(rfk::classTemplateCast(rfk::getDatabase().getFileLevelClassByName("SingleTypeTemplateClassTemplate")));

	std::vector<rfk::TemplateArgument const*> templateArgs{ &arg1, &arg2 };

	EXPECT_NE(multTemplateClass->getTemplateInstantiation(templateArgs.data(), templateArgs.size()), nullptr);
}

TEST(Rfk_ClassTemplate_getTemplateInstantiation, NonExistingTemplateTemplateInstantiation)
{
	rfk::TemplateTemplateArgument arg1(rfk::classTemplateCast(rfk::getDatabase().getFileLevelClassByName("SingleTypeTemplateClassTemplate")));
	rfk::TemplateTemplateArgument arg2(rfk::classTemplateCast(rfk::getDatabase().getFileLevelClassByName("MultipleTypeTemplateClassTemplate")));

	std::vector<rfk::TemplateArgument const*> templateArgs{ &arg1, &arg2 };

	EXPECT_EQ(multTemplateClass->getTemplateInstantiation(templateArgs.data(), templateArgs.size()), nullptr);
}

#endif

TEST(Rfk_ClassTemplate_getTemplateInstantiation, ExistingMixedTemplateInstantiation)
{
	rfk::TypeTemplateArgument arg1(rfk::getType<float>());

	constexpr std::size_t const arg2Value = 2u;
	rfk::NonTypeTemplateArgument arg2(arg2Value);

	rfk::TemplateTemplateArgument arg3(singleTypeClass);

	std::vector<rfk::TemplateArgument const*> templateArgs{ &arg1, &arg2, &arg3 };

	EXPECT_NE(mixedTemplateClass2->getTemplateInstantiation(templateArgs.data(), templateArgs.size()), nullptr);
}

TEST(Rfk_ClassTemplate_getTemplateInstantiation, NonExistingMixedTemplateInstantiation)
{
	rfk::TypeTemplateArgument arg1(rfk::getType<float>());

	constexpr std::size_t const arg2Value = 3u;	//Non existing value here
	rfk::NonTypeTemplateArgument arg2(arg2Value);

	rfk::TemplateTemplateArgument arg3(singleTypeClass);

	std::vector<rfk::TemplateArgument const*> templateArgs{ &arg1, &arg2, &arg3 };

	EXPECT_EQ(mixedTemplateClass2->getTemplateInstantiation(templateArgs.data(), templateArgs.size()), nullptr);
}

//=========================================================
//===== ClassTemplate::getTemplateInstantiationsCount =====
//=========================================================

TEST(Rfk_ClassTemplate_getTemplateInstantiationsCount, TypeTemplateClass)
{
	EXPECT_EQ(singleTypeClass->getTemplateInstantiationsCount(), 2u);
	EXPECT_EQ(multTypeClass->getTemplateInstantiationsCount(), 2u);
}

TEST(Rfk_ClassTemplate_getTemplateInstantiationsCount, NonTypeTemplateClass)
{
	EXPECT_EQ(singleNonTypeClass->getTemplateInstantiationsCount(), 1u);
	EXPECT_EQ(multNonTypeClass->getTemplateInstantiationsCount(), 1u);
}

#if RFK_TEMPLATE_TEMPLATE_SUPPORT

TEST(Rfk_ClassTemplate_getTemplateInstantiationsCount, TemplateTemplateClass)
{
	EXPECT_EQ(singleTemplateClass->getTemplateInstantiationsCount(), 1u);
	EXPECT_EQ(multTemplateClass->getTemplateInstantiationsCount(), 1u);
}

#endif

TEST(Rfk_ClassTemplate_getTemplateInstantiationsCount, MixedTemplateClass)
{
	EXPECT_EQ(mixedTemplateClass->getTemplateInstantiationsCount(), 1u);
	EXPECT_EQ(mixedTemplateClass2->getTemplateInstantiationsCount(), 1u);
}

//=========================================================
//====== ClassTemplate::foreachTemplateInstantiation ======
//=========================================================

TEST(Rfk_ClassTemplate_foreachTemplateInstantiation, NullptrVisitor)
{
	EXPECT_FALSE(mixedTemplateClass->foreachTemplateInstantiation(nullptr, nullptr));
}

TEST(Rfk_ClassTemplate_foreachTemplateInstantiation, ThrowingVisitor)
{
	auto visitor = [](rfk::ClassTemplateInstantiation const&, void*) -> bool
	{
		throw std::logic_error("Error");
	};

	EXPECT_THROW(mixedTemplateClass->foreachTemplateInstantiation(visitor, nullptr), std::logic_error);
}

TEST(Rfk_ClassTemplate_foreachTemplateInstantiation, CompleteLoop)
{
	int counter = 0;
	auto visitor = [](rfk::ClassTemplateInstantiation const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return true;
	};

	EXPECT_TRUE(mixedTemplateClass->foreachTemplateInstantiation(visitor, &counter));

	EXPECT_EQ(counter, mixedTemplateClass->getTemplateInstantiationsCount());
}

TEST(Rfk_ClassTemplate_foreachTemplateInstantiation, BreakingLoop)
{
	int counter = 0;
	auto visitor = [](rfk::ClassTemplateInstantiation const&, void* data)
	{
		int& counter = *reinterpret_cast<int*>(data);
		counter++;

		return false;
	};

	EXPECT_FALSE(mixedTemplateClass->foreachTemplateInstantiation(visitor, &counter));

	EXPECT_EQ(counter, 1);
}