/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <iostream>

namespace kodgen
{
	class SimplePropertyRule
	{
		public:
			/** Name of this property rule. */
			std::string name = "";

			SimplePropertyRule()							= default;
			SimplePropertyRule(std::string&& name)			noexcept;
			SimplePropertyRule(SimplePropertyRule const&)	= default;
			SimplePropertyRule(SimplePropertyRule&&)		= default;
			~SimplePropertyRule()							= default;

			/**
			*	@brief Check whether 2 property rules have the same name or not.
			*	
			*	@param other The other property rule.
			*	
			*	@return true if both property rules have the same name, else false.
			*/
			bool hasSameName(SimplePropertyRule const& other)	const noexcept;

			bool operator<(SimplePropertyRule const& other)		const;
	};

	std::ostream& operator<<(std::ostream& out_stream, SimplePropertyRule const&) noexcept;
}