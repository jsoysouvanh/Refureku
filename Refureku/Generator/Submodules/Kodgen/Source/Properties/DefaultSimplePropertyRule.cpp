#include "Kodgen/Properties/DefaultSimplePropertyRule.h"

using namespace kodgen;

DefaultSimplePropertyRule::DefaultSimplePropertyRule(std::string mainPropName, EEntityType validEntityTypes, std::string description) noexcept:
	_description{std::move(description)},
	mainPropName{std::move(mainPropName)},
	validEntityTypes{validEntityTypes}
{
}

bool DefaultSimplePropertyRule::isMainPropSyntaxValid(std::string const& mainProperty, EEntityType entityType) const noexcept
{
	return mainProperty == mainPropName && ((validEntityTypes & entityType) != EEntityType::Undefined);
}

std::string	DefaultSimplePropertyRule::getMacroDocumentation() const noexcept
{
	return	"/**\n"
			"*	@brief " + _description + "\n"
			"*/";
}

std::string	DefaultSimplePropertyRule::getMacroDefinition() const noexcept
{
	return	getMacroDocumentation() + "\n"
			"#define " + mainPropName;
}