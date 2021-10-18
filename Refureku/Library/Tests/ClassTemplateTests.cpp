#include <vector>

#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

//#include "SingleTypeTemplateClassTemplate.h"
//#include "MultipleTypeTemplateClassTemplate.h"

static rfk::ClassTemplate const* singleTypeClass;
static rfk::ClassTemplate const* multTypeClass;

//=========================================================
//================= Init static variables =================
//=========================================================

TEST(Rfk_ClassTemplate, Init)
{
	singleTypeClass = rfk::entityCast<rfk::ClassTemplate>(rfk::getDatabase().getFileLevelClassByName("SingleTypeTemplateClassTemplate"));
	EXPECT_NE(singleTypeClass, nullptr);

	multTypeClass = rfk::entityCast<rfk::ClassTemplate>(rfk::getDatabase().getFileLevelClassByName("MultipleTypeTemplateClassTemplate"));
	EXPECT_NE(multTypeClass, nullptr);
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

TEST(Rfk_ClassTemplate_getTemplateParameterAt, Generic)
{
	EXPECT_STREQ(singleTypeClass->getTemplateParameterAt(0).getName(), "T");

	EXPECT_STREQ(multTypeClass->getTemplateParameterAt(0).getName(), "T");
	EXPECT_STREQ(multTypeClass->getTemplateParameterAt(1).getName(), "U");
	EXPECT_STREQ(multTypeClass->getTemplateParameterAt(2).getName(), "V");
}

//=========================================================
//======= ClassTemplate::getTemplateInstantiation<> =======
//=========================================================

TEST(Rfk_ClassTemplate_getTemplateInstantiationTemplate, ExistingTypeTemplateInstantiation)
{
	rfk::TypeTemplateArgument arg1(rfk::getDatabase().getFundamentalArchetypeByName("int"));
	rfk::TypeTemplateArgument arg2(rfk::getDatabase().getFundamentalArchetypeByName("float"));
	rfk::TypeTemplateArgument arg3(rfk::getDatabase().getFundamentalArchetypeByName("double"));
	rfk::TemplateArgument const* templateArgs[] = { &arg1, &arg2, &arg3 };

	EXPECT_NE(multTypeClass->getTemplateInstantiation(templateArgs), nullptr);
}

TEST(Rfk_ClassTemplate_getTemplateInstantiationTemplate, NonExistingTypeTemplateInstantiation)
{
	rfk::TypeTemplateArgument arg1(rfk::getDatabase().getFundamentalArchetypeByName("int"));
	rfk::TypeTemplateArgument arg2(rfk::getDatabase().getFundamentalArchetypeByName("float"));
	rfk::TypeTemplateArgument arg3(rfk::getDatabase().getFundamentalArchetypeByName("long double"));
	rfk::TemplateArgument const* templateArgs[] = { &arg1, &arg2, &arg3 };

	EXPECT_EQ(multTypeClass->getTemplateInstantiation(templateArgs), nullptr);
}

//=========================================================
//======== ClassTemplate::getTemplateInstantiation ========
//=========================================================

TEST(Rfk_ClassTemplate_getTemplateInstantiation, ExistingTypeTemplateInstantiation)
{
	rfk::TypeTemplateArgument arg1(rfk::getDatabase().getFundamentalArchetypeByName("int"));
	std::vector<rfk::TemplateArgument const*> templateArgs{ &arg1 };

	EXPECT_NE(singleTypeClass->getTemplateInstantiation(templateArgs.data(), templateArgs.size()), nullptr);
}

TEST(Rfk_ClassTemplate_getTemplateInstantiation, NonExistingTypeTemplateInstantiation)
{
	rfk::TypeTemplateArgument arg1(rfk::getDatabase().getFundamentalArchetypeByName("long double"));
	std::vector<rfk::TemplateArgument const*> templateArgs{ &arg1 };

	EXPECT_EQ(singleTypeClass->getTemplateInstantiation(templateArgs.data(), templateArgs.size()), nullptr);
}

////=========================================================
////===== ClassTemplate::getTemplateInstantiationsCount =====
////=========================================================
//
//TEST(Rfk_ClassTemplate_getTemplateInstantiation, ExistingInstantiation)
//{
//	//std::cout << 
//}