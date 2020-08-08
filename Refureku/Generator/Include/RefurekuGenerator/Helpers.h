/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <cassert>

#include <Kodgen/Misc/FundamentalTypes.h>
#include <Kodgen/InfoStructures/EEntityType.h>

namespace rfk
{
	class Helpers
	{
		public:
			Helpers()				= delete;
			Helpers(Helpers const&) = delete;
			Helpers(Helpers&&)		= delete;
			~Helpers()				= delete;

			/**
			*	@brief Convert a kodgen::EEntityType to the corresponding integer value in rfk::Entity::EKind
			*	
			*	@param entityType The enum value to convert.
			*	
			*	@return The converted value.
			*/
			constexpr static kodgen::uint8 convertToEntityKind(kodgen::EEntityType entityType)			noexcept;

			/**
			*	@brief Convert a kodgen::EEntityType to the corresponding integer value in rfk::Archetype::ECategory
			*
			*	@param entityType The enum value to convert.
			*	
			*	@return The converted value.
			*/
			constexpr static kodgen::uint8 convertToArchetypeCategory(kodgen::EEntityType entityType)	noexcept;
	};

	#include "RefurekuGenerator/Helpers.inl"
}