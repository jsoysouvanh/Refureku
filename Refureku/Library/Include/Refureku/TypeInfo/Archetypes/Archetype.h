/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>

#include "Refureku/TypeInfo/Entity.h"
#include "Refureku/TypeInfo/EAccessSpecifier.h"

namespace rfk
{
	class Archetype : public Entity
	{
		protected:
			Archetype(std::string&& newName,
					  uint64		newId,
					  EKind			kind,
					  uint64		newMemorySize)	noexcept;
			Archetype(Archetype const&)				= delete;
			Archetype(Archetype&&)					= delete;
			~Archetype()							= default;

		public:
			/** Access specifier of this archetype. Relevant only when this archetype is nested (Undefined otherwise). */
			EAccessSpecifier	accessSpecifier	= EAccessSpecifier::Undefined;

			/** Size in bytes an instance of this archetype takes in memory, basically what sizeof(Type) returns */
			uint64				memorySize		= 0;
	};
}