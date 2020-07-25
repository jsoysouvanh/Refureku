/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>
#include <iostream>

#include "Properties/SimpleProperty.h"
#include "Properties/ComplexProperty.h"

namespace kodgen
{
	struct PropertyGroup
	{
		/** Collection of simple properties. */
		std::vector<SimpleProperty>		simpleProperties;
		
		/** Collection of complex properties. */
		std::vector<ComplexProperty>	complexProperties;
	};

	std::ostream& operator<<(std::ostream& out_stream, PropertyGroup const&) noexcept;
}