#pragma once

#include <vector>
#include <iostream>

#include "Properties/SimpleProperty.h"
#include "Properties/ComplexProperty.h"

namespace kodgen
{
	struct PropertyGroup
	{
		std::vector<SimpleProperty>		simpleProperties;
		std::vector<ComplexProperty>	complexProperties;
	};

	std::ostream& operator<<(std::ostream& out_stream, PropertyGroup const&) noexcept;
}