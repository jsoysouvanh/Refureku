#include "RefurekuGenerator/Properties/DefaultComplexPropertyRule.h"

#include <cassert>

using namespace rfk;

DefaultComplexPropertyRule::DefaultComplexPropertyRule(std::string mainPropName, kodgen::EEntityType validEntityTypes) noexcept:
	kodgen::DefaultComplexPropertyRule(std::move(mainPropName), validEntityTypes)
{
}

std::string	DefaultComplexPropertyRule::generateCode(kodgen::EntityInfo const& entity, kodgen::Property const& property, void* userData) const noexcept
{
	PropertyCodeGenData* data = reinterpret_cast<PropertyCodeGenData*>(userData);

	switch (data->getCodeGenLocation())
	{
		case ECodeGenLocation::FileHeader:
			return generateFileHeaderCode(entity, static_cast<kodgen::ComplexProperty const&>(property), *reinterpret_cast<PropertyCodeGenFileHeaderData*>(data));

		case ECodeGenLocation::PrePropertyAdd:
			return generatePrePropertyAddCode(entity, static_cast<kodgen::ComplexProperty const&>(property), *reinterpret_cast<PropertyCodeGenPropertyAddData*>(data));

		case ECodeGenLocation::PostPropertyAdd:
			return generatePostPropertyAddCode(entity, static_cast<kodgen::ComplexProperty const&>(property), *reinterpret_cast<PropertyCodeGenPropertyAddData*>(data));

		case ECodeGenLocation::ClassFooter:
			return generateClassFooterCode(entity, static_cast<kodgen::ComplexProperty const&>(property), *reinterpret_cast<PropertyCodeGenClassFooterData*>(data));

		case ECodeGenLocation::FileFooter:
			return generateFileFooterCode(entity, static_cast<kodgen::ComplexProperty const&>(property), *reinterpret_cast<PropertyCodeGenFileFooterData*>(data));
	}

	//Should never reach this point
	assert(false);

	return "";
}

std::string DefaultComplexPropertyRule::generateFileHeaderCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */, PropertyCodeGenFileHeaderData& /* data */) const noexcept
{
	//Default implementation generates no code

	return "";
}

std::string DefaultComplexPropertyRule::generatePrePropertyAddCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */, PropertyCodeGenPropertyAddData& /* data */) const noexcept
{
	//Default implementation generates no code

	return "";
}

std::string DefaultComplexPropertyRule::generatePostPropertyAddCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */, PropertyCodeGenPropertyAddData& /* data */) const noexcept
{
	//Default implementation generates no code

	return "";
}

std::string DefaultComplexPropertyRule::generateClassFooterCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */, PropertyCodeGenClassFooterData& /* data */) const noexcept
{
	//Default implementation generates no code

	return "";
}

std::string DefaultComplexPropertyRule::generateFileFooterCode(kodgen::EntityInfo const& /* entity */, kodgen::ComplexProperty const& /* property */, PropertyCodeGenFileFooterData& /* data */) const noexcept
{
	//Default implementation generates no code

	return "";
}