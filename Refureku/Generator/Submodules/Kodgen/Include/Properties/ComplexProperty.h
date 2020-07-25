/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

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
			/** Collection of all subproperties of the main property. */
			std::vector<std::string>	subProperties;

			ComplexProperty()						= default;
			ComplexProperty(ComplexProperty const&)	= default;
			ComplexProperty(ComplexProperty&&)		= default;
			~ComplexProperty()						= default;
	};

	std::ostream& operator<<(std::ostream& out_stream, ComplexProperty const& complexProp) noexcept;
}