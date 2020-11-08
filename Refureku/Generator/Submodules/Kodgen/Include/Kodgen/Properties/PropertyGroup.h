/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>
#include <string>

#include "Kodgen/Properties/SimpleProperty.h"
#include "Kodgen/Properties/ComplexProperty.h"

namespace kodgen
{
	class PropertyGroup
	{
		private:
			/**
			*	@brief Remove start and trail spaces of a string.
			*	
			*	@param string The string to process.
			*/
			static void removeStartAndTrailSpaces(std::string& string)	noexcept;

		public:
			/** Vector containing all simple properties of an entity. */
			std::vector<SimpleProperty>		simpleProperties;

			/** Vector containing all complex properties of an entity. */
			std::vector<ComplexProperty>	complexProperties;

			PropertyGroup()						= default;
			PropertyGroup(PropertyGroup const&)	= default;
			PropertyGroup(PropertyGroup&&)		= default;
			~PropertyGroup()					= default;

			/**
			*	@brief Remove start and trail spaces in property names (main prop name as well as complex subproperties).
			*/
			void removeStartAndTrailSpaces() noexcept;

			PropertyGroup&	operator=(PropertyGroup const&)	= default;
			PropertyGroup&	operator=(PropertyGroup&&)		= default;
	};
}