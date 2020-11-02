#include "Kodgen/Properties/DefaultComplexPropertyRule.h"

using namespace kodgen;

DefaultComplexPropertyRule::DefaultComplexPropertyRule(std::string mainPropName, EEntityType validEntityTypes) noexcept:
	mainPropName{std::move(mainPropName)},
	validEntityTypes{validEntityTypes}
{
}

bool DefaultComplexPropertyRule::isMainPropSyntaxValid(std::string const& mainProperty, EEntityType entityType) const noexcept
{
	return mainProperty == mainPropName && ((validEntityTypes & entityType) != EEntityType::Undefined);
}