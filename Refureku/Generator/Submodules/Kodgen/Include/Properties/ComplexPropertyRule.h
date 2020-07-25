/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <regex>

#include "Properties/SimplePropertyRule.h"

namespace kodgen
{
	class ComplexPropertyRule final : public SimplePropertyRule
	{
		public:
			/** Regex used to determine if a string if a valid subproperty or not. */
			std::regex	subPropertyPattern;
			
			ComplexPropertyRule()								= default;
			ComplexPropertyRule(std::string&& name,
								std::string&& argumentPattern)	noexcept;
			ComplexPropertyRule(ComplexPropertyRule const&)		= default;
			ComplexPropertyRule(ComplexPropertyRule&&)			= default;
			~ComplexPropertyRule()								= default;

			/**
			*	@brief Check whether a string is a valid subproperty or not.
			*
			*	@param argument The string we check the validity of.
			*	
			*	@return true if the argument is a valid subproperty, else false.
			*/
			bool isValidSubProperty(std::string const& argument)	const noexcept;
	};
}