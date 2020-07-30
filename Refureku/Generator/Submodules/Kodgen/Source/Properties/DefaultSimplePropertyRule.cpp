#include "Properties/DefaultSimplePropertyRule.h"

using namespace kodgen;

DefaultSimplePropertyRule::DefaultSimplePropertyRule(std::string mainPropName, std::unordered_set<EntityInfo::EType> validEntityTypes, std::string description) noexcept:
	_description{std::move(description)},
	mainPropName{std::move(mainPropName)},
	validEntityTypes{std::move(validEntityTypes)}
{
}

bool DefaultSimplePropertyRule::isMainPropSyntaxValid(std::string const& mainProperty, EntityInfo::EType entityType) const noexcept
{
	return mainProperty == mainPropName && validEntityTypes.find(entityType) != validEntityTypes.cend();
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