#include "Properties/DynamicGetArchetypePropertyRule.h"

#include "Properties/NativeProperties.h"

using namespace rfk;

DynamicGetArchetypePropertyRule::DynamicGetArchetypePropertyRule() noexcept:
	kodgen::DefaultSimplePropertyRule(NativeProperties::dynamicGetArchetypeProperty, { kodgen::EntityInfo::EType::Struct, kodgen::EntityInfo::EType::Class }, "Struct and Class property. Tells the generator to generate an override for the getArchetype method for this class.")
{
}

bool DynamicGetArchetypePropertyRule::isPropertyGroupValid(kodgen::PropertyGroup const& propertyGroup, kodgen::uint8 propertyIndex, std::string& out_errorDescription) const noexcept
{
	return isUsedOnlyOnce(propertyGroup, propertyIndex, out_errorDescription);
}

bool DynamicGetArchetypePropertyRule::isEntityValid(kodgen::EntityInfo const& /* entity */, kodgen::uint8 /* propertyIndex */, std::string& /* out_errorDescription */) const noexcept
{
	//No particular check to make
	return true;
}