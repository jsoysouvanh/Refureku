#include "RefurekuGenerator/Properties/DefaultSimplePropertyRule.h"

#include <cassert>

using namespace rfk;

DefaultSimplePropertyRule::DefaultSimplePropertyRule(std::string mainPropName, kodgen::EEntityType validEntityTypes) noexcept:
	kodgen::DefaultSimplePropertyRule(std::move(mainPropName), validEntityTypes)
{
}

std::string	DefaultSimplePropertyRule::generateCode(kodgen::EntityInfo const& entity, kodgen::Property const& property, void* userData) const noexcept
{
	PropertyCodeGenData* data = reinterpret_cast<PropertyCodeGenData*>(userData);

	switch (data->getCodeGenLocation())
	{
		case ECodeGenLocation::FileHeader:
			return generateFileHeaderCode(entity, property, *reinterpret_cast<PropertyCodeGenFileHeaderData*>(data));

		case ECodeGenLocation::PrePropertyAdd:
			return generatePrePropertyAddCode(entity, property, *reinterpret_cast<PropertyCodeGenPropertyAddData*>(data));

		case ECodeGenLocation::PostPropertyAdd:
			return generatePostPropertyAddCode(entity, property, *reinterpret_cast<PropertyCodeGenPropertyAddData*>(data));

		case ECodeGenLocation::ClassFooter:
			return generateClassFooterCode(entity, property, *reinterpret_cast<PropertyCodeGenClassFooterData*>(data));

		case ECodeGenLocation::FileFooter:
			return generateFileFooterCode(entity, property, *reinterpret_cast<PropertyCodeGenFileFooterData*>(data));
	}

	//Should never reach this point
	assert(false);

	return "";
}

std::string DefaultSimplePropertyRule::generateFileHeaderCode(kodgen::EntityInfo const& /* entity */, kodgen::Property const& /* property */, PropertyCodeGenFileHeaderData& /* data */) const noexcept
{
	//Default implementation generates no code

	return "";
}

std::string DefaultSimplePropertyRule::generatePrePropertyAddCode(kodgen::EntityInfo const& /* entity */, kodgen::Property const& /* property */, PropertyCodeGenPropertyAddData& /* data */) const noexcept
{
	//Default implementation generates no code

	return "";
}

std::string DefaultSimplePropertyRule::generatePostPropertyAddCode(kodgen::EntityInfo const& /* entity */, kodgen::Property const& /* property */, PropertyCodeGenPropertyAddData& /* data */) const noexcept
{
	//Default implementation generates no code

	return "";
}

std::string DefaultSimplePropertyRule::generateClassFooterCode(kodgen::EntityInfo const& /* entity */, kodgen::Property const& /* property */, PropertyCodeGenClassFooterData& /* data */) const noexcept
{
	//Default implementation generates no code

	return "";
}

std::string DefaultSimplePropertyRule::generateFileFooterCode(kodgen::EntityInfo const& /* entity */, kodgen::Property const& /* property */, PropertyCodeGenFileFooterData& /* data */) const noexcept
{
	//Default implementation generates no code

	return "";
}