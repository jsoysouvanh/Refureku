#include "Properties/ComplexPropertyRule.h"

using namespace kodgen;

ComplexPropertyRule::ComplexPropertyRule(std::string&& name, std::string&& argumentPattern)	noexcept:
	SimplePropertyRule(std::forward<std::string>(name)),
	subPropertyPattern{std::forward<std::string>(argumentPattern)}
{}

bool ComplexPropertyRule::isValidSubProperty(std::string const& argument) const noexcept
{
	std::match_results<std::string::const_iterator>	matchResults;

	if (std::regex_search(argument, matchResults, subPropertyPattern, std::regex_constants::match_default))
	{
		return matchResults.prefix().str().empty() && matchResults.suffix().str().empty();
	}

	return false;
}