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
	class StaticMethod;	//Forward declaration

	class Archetype : public Entity
	{
		public:
			/**
			*	Category of an archetype.
			*	Actually represents the class of an archetype instance.
			*/
			enum class ECategory : uint8
			{
				/** Undefined archetype. Should never happen? */
				Undefined	= 0u,

				/** The archetype is a class, can safely be cast to Class. */
				Class		= 1 << 0,

				/** The archetype is a struct, can safely be cast to Struct. */
				Struct		= 1 << 1,

				/** The archetype is an enum, can safely by cast to Enum. */
				Enum		= 1 << 2,

				/** The archetype is a fundamental archetype. */
				Fundamental	= 1 << 3,
			};

			/** Access specifier of this archetype. Relevant only when this archetype is nested (Undefined otherwise). */
			EAccessSpecifier	accessSpecifier	= EAccessSpecifier::Undefined;

			/** Category of this type */
			ECategory			category		= ECategory::Undefined;

			/** Size in bytes an instance of this archetype takes in memory, basically what sizeof(Type) returns */
			uint64				memorySize		= 0;

			Archetype(std::string&& newName,
					  uint64		newId			= 0u,
					  ECategory		newCategory		= ECategory::Undefined,
					  uint64		newMemorySize	= 0u)					noexcept;
			Archetype(Archetype const&)										= delete;
			Archetype(Archetype&&)											= default;
			~Archetype()													= default;
	};
}