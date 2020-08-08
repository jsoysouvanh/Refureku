#include "Kodgen/Properties/DefaultComplexPropertyRule.h"

using namespace kodgen;

DefaultComplexPropertyRule::DefaultComplexPropertyRule(std::string mainPropName, EEntityType validEntityTypes, std::string description) noexcept:
	_description{std::move(description)},
	mainPropName{std::move(mainPropName)},
	validEntityTypes{validEntityTypes}
{
}

bool DefaultComplexPropertyRule::isMainPropSyntaxValid(std::string const& mainProperty, EEntityType entityType) const noexcept
{
	return mainProperty == mainPropName && ((validEntityTypes & entityType) != EEntityType::Undefined);
}

std::string	DefaultComplexPropertyRule::getMacroDocumentation() const noexcept
{
	return	"/**\n"
			"*	@brief " + _description + "\n"
			"*/";
}

std::string	DefaultComplexPropertyRule::getMacroDefinition() const noexcept
{
	return	getMacroDocumentation() + "\n"
			"#define " + mainPropName;
}

std::string const& DefaultComplexPropertyRule::getDescription() const noexcept
{
	return _description;
}