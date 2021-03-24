#include "RefurekuGenerator/Properties/TestPropertyRule.h"

#include <iostream>

using namespace rfk;

TestPropertyRule::TestPropertyRule() noexcept:
	DefaultComplexPropertyRule("TestProperty", (kodgen::EEntityType)~0) //~0 means all entity types
{
}

std::string TestPropertyRule::generateFileHeaderCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */, PropertyCodeGenFileHeaderData& /* data */) const noexcept
{
	std::cout << "TestPropertyRule Header" << std::endl;
	return "/* FileHeader */";
}

std::string TestPropertyRule::generatePrePropertyAddCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */,  PropertyCodeGenPropertyAddData& data) const noexcept
{
	std::cout << "TestPropertyRule PrePropertyAdd" << std::endl;
	return "/* PrePropertyAdd  " + data.accessEntityVariable() + " : " + data.accessPropertyVariable() + " */";
}

std::string TestPropertyRule::generatePostPropertyAddCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */,  PropertyCodeGenPropertyAddData& data) const noexcept
{
	std::cout << "TestPropertyRule PostPropertyAdd" << std::endl;
	return "/* PostPropertyAdd " + data.accessEntityVariable() + " : " + data.accessPropertyVariable() + " */";
}

std::string TestPropertyRule::generateClassFooterCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */, PropertyCodeGenClassFooterData& /* data */) const noexcept
{
	std::cout << "TestPropertyRule ClassFooter" << std::endl;
	return "/* ClassFooter */";
}

std::string TestPropertyRule::generateFileFooterCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */, PropertyCodeGenFileFooterData& /* data */) const noexcept
{
	std::cout << "TestPropertyRule FileFooter" << std::endl;
	return "/* FileFooter */";
}

//------------------------------------

TestPropertyRule2::TestPropertyRule2() noexcept:
	DefaultComplexPropertyRule("TestProperty2", (kodgen::EEntityType)~0) //~0 means all entity types
{
}

std::string TestPropertyRule2::generateFileHeaderCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */, PropertyCodeGenFileHeaderData& /* data */) const noexcept
{
	std::cout << "TestPropertyRule2 Header" << std::endl;
	return "/* FileHeader */";
}

std::string TestPropertyRule2::generatePrePropertyAddCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */,  PropertyCodeGenPropertyAddData& data) const noexcept
{
	std::cout << "TestPropertyRule2 PrePropertyAdd" << std::endl;
	return "/* PrePropertyAdd  " + data.accessEntityVariable() + " : " + data.accessPropertyVariable() + " */";
}

std::string TestPropertyRule2::generatePostPropertyAddCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */,  PropertyCodeGenPropertyAddData& data) const noexcept
{
	std::cout << "TestPropertyRule2 PostPropertyAdd" << std::endl;
	return "/* PostPropertyAdd " + data.accessEntityVariable() + " : " + data.accessPropertyVariable() + " */";
}

std::string TestPropertyRule2::generateClassFooterCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */, PropertyCodeGenClassFooterData& /* data */) const noexcept
{
	std::cout << "TestPropertyRule2 ClassFooter" << std::endl;
	return "/* ClassFooter */";
}

std::string TestPropertyRule2::generateFileFooterCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */, PropertyCodeGenFileFooterData& /* data */) const noexcept
{
	std::cout << "TestPropertyRule2 FileFooter" << std::endl;
	return "/* FileFooter */";
}

//------------------------------------

TestPropertyRule3::TestPropertyRule3() noexcept:
	DefaultComplexPropertyRule("TestProperty3", (kodgen::EEntityType)~0) //~0 means all entity types
{
}

std::string TestPropertyRule3::generateFileHeaderCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */, PropertyCodeGenFileHeaderData& /* data */) const noexcept
{
	std::cout << "TestPropertyRule3 Header" << std::endl;
	return "/* FileHeader */";
}

std::string TestPropertyRule3::generatePrePropertyAddCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */,  PropertyCodeGenPropertyAddData& data) const noexcept
{
	std::cout << "TestPropertyRule3 PrePropertyAdd" << std::endl;
	return "/* PrePropertyAdd  " + data.accessEntityVariable() + " : " + data.accessPropertyVariable() + " */";
}

std::string TestPropertyRule3::generatePostPropertyAddCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */,  PropertyCodeGenPropertyAddData& data) const noexcept
{
	std::cout << "TestPropertyRule3 PostPropertyAdd" << std::endl;
	return "/* PostPropertyAdd " + data.accessEntityVariable() + " : " + data.accessPropertyVariable() + " */";
}

std::string TestPropertyRule3::generateClassFooterCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */, PropertyCodeGenClassFooterData& /* data */) const noexcept
{
	std::cout << "TestPropertyRule3 ClassFooter" << std::endl;
	return "/* ClassFooter */";
}

std::string TestPropertyRule3::generateFileFooterCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */, PropertyCodeGenFileFooterData& /* data */) const noexcept
{
	std::cout << "TestPropertyRule3 FileFooter" << std::endl;
	return "/* FileFooter */";
}