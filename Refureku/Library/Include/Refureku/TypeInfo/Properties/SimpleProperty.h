/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

namespace rfk
{
	class SimpleProperty
	{
		public:
			/** Name of this property. */
			std::string mainProperty;

			SimpleProperty()							= default;
			SimpleProperty(std::string mainProperty)	noexcept;
			SimpleProperty(SimpleProperty const&)		= default;
			SimpleProperty(SimpleProperty&&)			= default;
			~SimpleProperty()							= default;
	};
}