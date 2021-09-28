/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Entity/Entity.h"
#include "Refureku/TypeInfo/EAccessSpecifier.h"

namespace rfk
{
	class ArchetypeAPI : public EntityAPI
	{
		public:
			//TODO: Delete this since it will never be used in real situations (just for tests)
			REFUREKU_API ArchetypeAPI(char const*		name,
									  std::size_t		id,
									  EEntityKind		kind,
									  std::size_t		memorySize,
									  EntityAPI const*	outerEntity = nullptr)	noexcept;
			ArchetypeAPI(ArchetypeAPI const&)									noexcept;
			ArchetypeAPI(ArchetypeAPI&&)										noexcept;
			REFUREKU_API ~ArchetypeAPI()										noexcept;	//TODO: Maybe move this to protected as well

			/**
			*	@brief Getter for the field _accessSpecifier.
			* 
			*	@return _accessSpecifier.
			*/
			REFUREKU_API EAccessSpecifier	getAccessSpecifier()			const	noexcept;

			/**
			*	@brief Setter for the field _accessSpecifier.
			* 
			*	@param The access specifier to set.
			*/
			REFUREKU_API void				setAccessSpecifier(EAccessSpecifier)	noexcept;

			/**
			*	@brief Getter for the field _memorySize.
			* 
			*	@return _memorySize.
			*/
			REFUREKU_API std::size_t		getMemorySize()					const	noexcept;

		protected:
			//Forward declaration
			class ArchetypeImpl;

			ArchetypeAPI()	noexcept;

			/**
			*	@brief Set the underlying implementation to the provided implementation.
			*
			*	@param implementation The implementation pointer to use.
			*/
			void setImpl(ArchetypeImpl* implementation) noexcept;

		private:
			/** Concrete implementation of the Archetype class. */
			Pimpl<ArchetypeImpl> _pimpl;
	};

	//TODO: getArchetype base implementation should maybe be here?
}