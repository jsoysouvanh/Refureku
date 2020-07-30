/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

namespace rfk
{
	class PropertyGroup
	{
		public:
			/** Collection of simple properties. */
			std::unordered_set<std::string>						simpleProperties;

			/** Collection of complex properties. */
			std::unordered_multimap<std::string, std::string>	complexProperties;

			PropertyGroup()						= default;
			PropertyGroup(PropertyGroup const&)	= default;
			PropertyGroup(PropertyGroup&&)		= default;
			~PropertyGroup()					= default;

			/** Return true if the property group contains the provided simple property */
			inline bool	hasProperty(std::string const& prop)							const	noexcept;

			/** Return true if the property group contains the provided complex property */
			inline bool	hasProperty(std::string const& main, std::string const& sub)	const	noexcept;
	};

	#include "TypeInfo/PropertyGroup.inl"
}