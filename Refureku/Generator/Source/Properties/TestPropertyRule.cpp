#include "RefurekuGenerator/Properties/TestPropertyRule.h"

using namespace rfk;

TestPropertyRule::TestPropertyRule() noexcept:
	DefaultComplexPropertyRule("TestProperty", (kodgen::EEntityType)~0) //~0 means all entity types
{
}

std::string TestPropertyRule::generateFileHeaderCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */, PropertyCodeGenFileHeaderData& /* data */) const noexcept
{
	return "/* FileHeader */";
}

std::string TestPropertyRule::generatePrePropertyAddCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */,  PropertyCodeGenPropertyAddData& data) const noexcept
{
	return "/* PrePropertyAdd  " + data.accessEntityVariable() + " : " + data.accessPropertyVariable() + " */";
}

std::string TestPropertyRule::generatePostPropertyAddCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */,  PropertyCodeGenPropertyAddData& data) const noexcept
{
	return "/* PostPropertyAdd " + data.accessEntityVariable() + " : " + data.accessPropertyVariable() + " */";
}

std::string TestPropertyRule::generateClassFooterCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */, PropertyCodeGenClassFooterData& /* data */) const noexcept
{
	return "/* ClassFooter */";
}

std::string TestPropertyRule::generateFileFooterCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */, PropertyCodeGenFileFooterData& data) const noexcept
{
	return "/* FileFooter */";
}