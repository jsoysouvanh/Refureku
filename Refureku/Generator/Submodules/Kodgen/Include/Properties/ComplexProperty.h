#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Properties/SimpleProperty.h"

namespace kodgen
{
	class ComplexProperty final : public SimpleProperty
	{
		public:
			std::vector<std::string>	subProperties;

			ComplexProperty()						= default;
			ComplexProperty(ComplexProperty const&)	= default;
			ComplexProperty(ComplexProperty&&)		= default;
			~ComplexProperty()						= default;
	};

	std::ostream& operator<<(std::ostream& out_stream, ComplexProperty const& complexProp) noexcept;
}