/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/EAccessSpecifier.h"

namespace rfk
{
	//Forward declaration
	class StructAPI;

	class ParentStruct
	{
		public:
			ParentStruct(StructAPI const&	archetype,
						 EAccessSpecifier	inheritanceAccessSpecifier)	noexcept;
			ParentStruct(ParentStruct const&)							= delete;
			ParentStruct(ParentStruct&&)								noexcept;
			~ParentStruct()												noexcept;

			/**
			*	@brief Get the archetype of the parent struct.
			* 
			*	@return The archetype of the parent struct.
			*/
			RFK_NODISCARD REFUREKU_API StructAPI const&	getArchetype()					const	noexcept;

			/**
			*	@brief Get the inheritance access specifier used when inheriting this struct.
			* 
			*	@return The inheritance access specifier used when inheriting this struct.
			*/
			RFK_NODISCARD REFUREKU_API EAccessSpecifier	getInheritanceAccessSpecifier()	const	noexcept;

		private:
			/** Archetype of the parent struct. */
			StructAPI const&	_archetype;

			/** Inheritance access specifier. */
			EAccessSpecifier	_inheritanceAccessSpecifier;
	};
}