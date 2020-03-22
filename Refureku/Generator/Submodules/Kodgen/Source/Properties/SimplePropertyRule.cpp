#include "Properties/SimplePropertyRule.h"

using namespace kodgen;

SimplePropertyRule::SimplePropertyRule(std::string&& name) noexcept:
	name{std::forward<std::string>(name)}
{}

bool SimplePropertyRule::hasSameName(SimplePropertyRule const& other) const noexcept
{
	return name == other.name;
}

bool SimplePropertyRule::operator<(SimplePropertyRule const& other) const
{
	return name < other.name;
}

std::ostream& kodgen::operator<<(std::ostream& out_stream, SimplePropertyRule const& simpleProp) noexcept
{
	out_stream << simpleProp.name;

	return out_stream;
}