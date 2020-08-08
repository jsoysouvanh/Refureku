#include "RefurekuGenerator/Properties/DynamicGetArchetypePropertyRule.h"

#include "RefurekuGenerator/Properties/NativeProperties.h"

using namespace rfk;

DynamicGetArchetypePropertyRule::DynamicGetArchetypePropertyRule() noexcept:
	kodgen::DefaultSimplePropertyRule(NativeProperties::dynamicGetArchetypeProperty,
									  kodgen::EEntityType::Struct | kodgen::EEntityType::Class,
									  "Struct and Class property. Tells the generator to generate an override for the getArchetype method for this class.")
{
}

bool DynamicGetArchetypePropertyRule::isPropertyGroupValid(kodgen::PropertyGroup const& propertyGroup, kodgen::uint8 propertyIndex, std::string& out_errorDescription) const noexcept
{
	return isUsedOnlyOnce(propertyGroup, propertyIndex, out_errorDescription);
}