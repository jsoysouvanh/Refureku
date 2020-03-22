#include "Properties/ComplexProperty.h"

using namespace kodgen;

std::ostream& kodgen::operator<<(std::ostream& out_stream, ComplexProperty const& complexProp) noexcept
{
	std::string totalName = complexProp.name + "[";

	for (std::string const& subProp : complexProp.subProperties)
	{
		totalName += subProp + ", ";
	}

	if (!complexProp.subProperties.empty())
	{
		//Remove ", "
		totalName.pop_back();
		totalName.pop_back();
	}

	totalName += "]";

	out_stream << std::move(totalName);

	return out_stream;
}