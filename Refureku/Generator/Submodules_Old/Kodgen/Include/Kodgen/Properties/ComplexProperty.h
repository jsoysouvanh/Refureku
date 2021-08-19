/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>

#include "Kodgen/Properties/Property.h"

namespace kodgen
{
	//Forward declaration
	class ComplexPropertyRule;

	class ComplexProperty : public Property
	{
		public:
			/** Collection of all subproperties. */
			std::vector<std::string>	subProperties;

			/** Pointer to the rule which validated this property syntax. */
			ComplexPropertyRule const*	boundPropertyRule	= nullptr;

			ComplexProperty()													= default;
			ComplexProperty(std::string					mainProperty,
							ComplexPropertyRule const*	matchingPropertyRule)	noexcept;
			ComplexProperty(ComplexProperty const&)								= default;
			ComplexProperty(ComplexProperty&&)									= default;
			~ComplexProperty()													= default;
	};
}