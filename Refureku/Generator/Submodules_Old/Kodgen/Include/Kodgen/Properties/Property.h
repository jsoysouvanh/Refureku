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
	class Property
	{
		public:
			/** Name of this property. */
			std::string	mainProperty;

			Property()							= default;
			Property(std::string mainProperty)	noexcept;
			Property(Property const&)			= default;
			Property(Property&&)				= default;
			~Property()							= default;

	};
}