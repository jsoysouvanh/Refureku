/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/EAccessSpecifier.h"

namespace rfk
{
	//Forward declaration
	class Struct;

	class ParentStruct
	{
		public:
			REFUREKU_INTERNAL ParentStruct(Struct const&	archetype,
										   EAccessSpecifier	inheritanceAccessSpecifier)	noexcept;
			REFUREKU_INTERNAL ParentStruct(ParentStruct const&)							= delete;
			REFUREKU_INTERNAL ParentStruct(ParentStruct&&)								noexcept;
			REFUREKU_INTERNAL ~ParentStruct()											noexcept;

			/**
			*	@brief Get the archetype of the parent struct.
			* 
			*	@return The archetype of the parent struct.
			*/
			RFK_NODISCARD REFUREKU_API Struct const&	getArchetype()					const	noexcept;

			/**
			*	@brief Get the inheritance access specifier used when inheriting this struct.
			* 
			*	@return The inheritance access specifier used when inheriting this struct.
			*/
			RFK_NODISCARD REFUREKU_API EAccessSpecifier	getInheritanceAccessSpecifier()	const	noexcept;

			REFUREKU_INTERNAL ParentStruct&				operator=(ParentStruct const&)			= delete;
			REFUREKU_INTERNAL ParentStruct&				operator=(ParentStruct&&)				noexcept;

		private:
			/** Archetype of the parent struct. */
			Struct const*		_archetype;

			/** Inheritance access specifier. */
			EAccessSpecifier	_inheritanceAccessSpecifier;
	};
}