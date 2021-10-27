/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Entity/Entity.h"
#include "Refureku/TypeInfo/EAccessSpecifier.h"

namespace rfk
{
	class Archetype : public Entity
	{
		public:
			Archetype(Archetype&&) = delete;

			/**
			*	@brief	Get the access specifier of the archetype if it is nested in a struct or class.
			*			If the archetype is not nested in a struct or class, EAccessSpecifier::Undefined is returned.
			* 
			*	@return The access specifier of the archetype.
			*/
			RFK_NODISCARD REFUREKU_API
				EAccessSpecifier			getAccessSpecifier()				const	noexcept;

			/**
			*	@brief Get the memory size of an instance of the archetype, as the operator sizeof(type) would do.
			* 
			*	@return The memory size of an instance of the archetype.
			*/
			RFK_NODISCARD REFUREKU_API
				std::size_t					getMemorySize()						const	noexcept;

			/**
			*	@brief Set the access specifier of the archetype in its outer struct/class.
			* 
			*	@param access The new access specifier of this archetype.
			*/
			REFUREKU_API
				void						setAccessSpecifier(EAccessSpecifier access)	noexcept;

		protected:
			//Forward declaration
			class ArchetypeImpl;

			REFUREKU_INTERNAL Archetype(ArchetypeImpl* implementation)	noexcept;
			REFUREKU_INTERNAL ~Archetype()								noexcept;

			RFK_GEN_GET_PIMPL(ArchetypeImpl, Entity::getPimpl())
	};

	REFUREKU_TEMPLATE_API(rfk::Allocator<Archetype const*>);
	REFUREKU_TEMPLATE_API(rfk::Vector<Archetype const*, rfk::Allocator<Archetype const*>>);
}