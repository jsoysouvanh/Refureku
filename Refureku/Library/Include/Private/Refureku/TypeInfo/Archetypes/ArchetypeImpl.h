/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/ArchetypeAPI.h"
#include "Refureku/TypeInfo/Entity/EntityImpl.h"

namespace rfk
{
	class ArchetypeAPI::ArchetypeImpl : public EntityAPI::EntityImpl
	{
		private:
			/** Access specifier of this archetype. Relevant only when this archetype is nested (Undefined otherwise). */
			EAccessSpecifier	_accessSpecifier	= EAccessSpecifier::Undefined;

			/** Size in bytes an instance of this archetype takes in memory, basically what sizeof(Type) returns */
			std::size_t			_memorySize			= 0;

		public:
			inline ArchetypeImpl(char const*		name,
								 std::size_t		id,
								 EEntityKind		kind,
								 std::size_t		memorySize,
								 EntityAPI const*	outerEntity = nullptr)	noexcept;

			/**
			*	@brief Getter for the field _memorySize.
			* 
			*	@return _memorySize.
			*/
			inline std::size_t		getMemorySize()					const	noexcept;

			/**
			*	@brief Getter for the field _accessSpecifier.
			* 
			*	@return _accessSpecifier.
			*/
			inline EAccessSpecifier	getAccessSpecifier()			const	noexcept;

			/**
			*	@brief Setter for the field _accessSpecifier.
			* 
			*	@param The access specifier to set.
			*/
			inline void				setAccessSpecifier(EAccessSpecifier)	noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/ArchetypeImpl.inl"
}