/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

namespace kodgen
{
	//Forward declaration
	class SimplePropertyRule;

	class SimpleProperty
	{
		public:
			/** Name of this property. */
			std::string					mainProperty;

			/** Pointer to the rule which validated this property syntax. */
			SimplePropertyRule const*	boundPropertyRule	= nullptr;


			SimpleProperty()													= default;
			SimpleProperty(std::string					mainProperty,
							SimplePropertyRule const*	matchingPropertyRule)	noexcept;
			SimpleProperty(SimpleProperty const&)								= default;
			SimpleProperty(SimpleProperty&&)									= default;
			~SimpleProperty()													= default;

	};
}