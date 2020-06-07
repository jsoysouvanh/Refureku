/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>

#include "TypeInfo/Entity.h"

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
				/** The archetype is a class, can safely be cast to Class. */
				Class	= 0,

				/** The archetype is a struct, can safely be cast to Struct. */
				Struct,

				/** The archetype is an enum, can safely by cast to Enum. */
				Enum,

				/** The archetype is a fundamental archetype. */
				Fundamental,

				/** Undefined archetype. Should never happen? */
				Undefined,

				/** Represent the total number of values in ECategory enum. */
				Count
			};

			/** Category of this type */
			ECategory	category	= ECategory::Undefined;

			/** Size in bytes an instance of this archetype takes in memory, basically what sizeof(Type) returns */
			uint64		memorySize	= 0;

			Archetype(std::string&& newName,
					  uint64		newId			= 0u,
					  ECategory		newCategory		= ECategory::Undefined,
					  uint64		newMemorySize	= 0u)					noexcept;
			Archetype(Archetype const&)										= delete;
			Archetype(Archetype&&)											= default;
			~Archetype()													= default;

			Archetype& operator=(Archetype const&)	= delete;
			Archetype& operator=(Archetype&&)		= default;
	};
}