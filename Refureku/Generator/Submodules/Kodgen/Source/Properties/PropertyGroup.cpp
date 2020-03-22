#include "Properties/PropertyGroup.h"

using namespace kodgen;

std::ostream& kodgen::operator<<(std::ostream& out_stream, PropertyGroup const& propertyGroup) noexcept
{
	out_stream << "Props(";

	for (SimpleProperty const& simpleProp : propertyGroup.simpleProperties)
	{
		out_stream << " " << simpleProp;
	}

	for (ComplexProperty const& complexProp : propertyGroup.complexProperties)
	{
		out_stream << " " << complexProp;
	}

	out_stream << " )";

	return out_stream;
}