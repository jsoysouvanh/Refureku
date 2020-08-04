/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <vector>

#include "Refureku/TypeInfo/Properties/SimpleProperty.h"
#include "Refureku/TypeInfo/Properties/ComplexProperty.h"

namespace rfk
{
	class PropertyGroup
	{
		public:
			/** Collection of simple properties. */
			std::vector<SimpleProperty>		simpleProperties;

			/** Collection of complex properties. */
			std::vector<ComplexProperty>	complexProperties;

			PropertyGroup()						= default;
			PropertyGroup(PropertyGroup const&)	= default;
			PropertyGroup(PropertyGroup&&)		= default;
			~PropertyGroup()					= default;

			/**
			*	@brief Retrieve a simple property from the property group.
			*	
			*	@param mainProperty Main property of the simple property to look for.
			*	
			*	@return A pointer to the simple property if found, else nullptr.
			*/
			SimpleProperty const*	getSimpleProperty(std::string const& mainProperty)	const noexcept;

			/**
			*	@brief Retrieve a complex property from the property group.
			*	
			*	@param mainProperty Main property of the complex property to look for.
			*	
			*	@return A pointer to the complex property if found, else nullptr.
			*/
			ComplexProperty const*	getComplexProperty(std::string const& mainProperty)	const noexcept;
	};
}