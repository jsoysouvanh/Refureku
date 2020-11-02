#include "Kodgen/Properties/DefaultSimplePropertyRule.h"

using namespace kodgen;

DefaultSimplePropertyRule::DefaultSimplePropertyRule(std::string mainPropName, EEntityType validEntityTypes) noexcept:
	mainPropName{std::move(mainPropName)},
	validEntityTypes{validEntityTypes}
{
}

bool DefaultSimplePropertyRule::isMainPropSyntaxValid(std::string const& mainProperty, EEntityType entityType) const noexcept
{
	return mainProperty == mainPropName && ((validEntityTypes & entityType) != EEntityType::Undefined);
}