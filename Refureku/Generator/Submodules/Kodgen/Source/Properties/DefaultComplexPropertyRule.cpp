#include "Properties/DefaultComplexPropertyRule.h"

using namespace kodgen;

DefaultComplexPropertyRule::DefaultComplexPropertyRule(std::string mainPropName, std::unordered_set<EntityInfo::EType> validEntityTypes, std::string description) noexcept:
	_description{std::move(description)},
	mainPropName{std::move(mainPropName)},
	validEntityTypes{std::move(validEntityTypes)}
{
}

bool DefaultComplexPropertyRule::isMainPropSyntaxValid(std::string const& mainProperty, EntityInfo::EType entityType) const noexcept
{
	return mainProperty == mainPropName && validEntityTypes.find(entityType) != validEntityTypes.cend();
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