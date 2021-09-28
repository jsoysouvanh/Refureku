/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/StructAPI.h"
#include "Refureku/TypeInfo/Archetypes/ArchetypeImpl.h"

namespace rfk
{
	class StructAPI::StructImpl : public ArchetypeAPI::ArchetypeImpl
	{
		private:
			//TODO

		public:
			StructImpl(char const*	name,
					   std::size_t	id,
					   std::size_t	memorySize,
					   bool			isClass,
					   EClassKind	classKind)	noexcept;

			//TODO
	};
}