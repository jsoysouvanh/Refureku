/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/ArchetypeAPI.h"
#include "Refureku/TypeInfo/Archetypes/EClassKind.h"

namespace rfk
{
	class StructAPI : public ArchetypeAPI
	{
		public:
			REFUREKU_API StructAPI(char const*	name,
								   std::size_t	id,
								   std::size_t	memorySize,
								   bool			isClass)		noexcept;
			StructAPI(StructAPI const&)							noexcept;
			StructAPI(StructAPI&&)								noexcept;
			REFUREKU_API ~StructAPI()							noexcept;

		protected:
			StructAPI(char const*	name,
					  std::size_t	id,
					  std::size_t	memorySize,
					  bool			isClass,
					  EClassKind	classKind)	noexcept;

			//Forward declaration
			class StructImpl;

			/**
			*	@brief Set the underlying implementation to the provided implementation.
			*
			*	@param implementation The implementation pointer to use.
			*/
			void setImpl(StructImpl* implementation) noexcept;

		private:
			/** Concrete implementation of the Struct class. */
			Pimpl<StructImpl> _pimpl;
	};
}