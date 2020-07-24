/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <unordered_set>
#include <type_traits>

#include "Misc/FundamentalTypes.h"
#include "TypeInfo/Archetypes/Class.h"
#include "TypeInfo/Archetypes/Enum.h"

namespace rfk
{
	class Database
	{
		friend class ArchetypeRegisterer;

		private:
			using EntitiesById		= std::unordered_set<Entity const*, Entity::PtrIdHasher, Entity::PtrEqualId>;
			using ArchetypesByName	= std::unordered_set<Archetype const*, Entity::PtrNameHasher, Entity::PtrEqualName>;

			static	EntitiesById		_entitiesById;
			static	ArchetypesByName	_archetypesByName;

			static void	registerArchetype(Archetype const& archetype)	noexcept;
			static void registerSubEntities(Archetype const& archetype)	noexcept;
			static void registerStructSubEntities(Struct const& s)		noexcept;
			static void registerEnumSubEntities(Enum const& e)			noexcept;

		public:
			Database()								= delete;
			Database(Database const&)				= delete;
			Database(Database&&)					= delete;
			~Database()								= delete;

			/**
			*	@brief Retrieve an archetype by name.
			*
			*	@param typeName The name of the archetype (Archetype::name, inherited from Entity).
			*
			*	@return A constant pointer to the queried archetype if it exists, else nullptr.
			*/
			static Archetype const*				getArchetype(std::string typeName)	noexcept;

			/**
			*	@brief Retrieve a struct by name.
			*
			*	@param structName The name of the struct.
			*
			*	@return A constant pointer to the queried struct if it exists, else nullptr.
			*/
			static Struct const*				getStruct(std::string structName)	noexcept;

			/**
			*	@brief Retrieve a class by name.
			*
			*	@param className The name of the class.
			*
			*	@return A constant pointer to the queried class if it exists, else nullptr.
			*/
			static Class const*					getClass(std::string className)		noexcept;

			/**
			*	@brief Retrieve an enum by name.
			*
			*	@param enumName The name of the enum.
			*
			*	@return A constant pointer to the queried enum if it exists, else nullptr.
			*/
			static Enum const*					getEnum(std::string enumName)		noexcept;

			/**
			*	@brief Retrieve an entity by id.
			*
			*	This is not limited to archetypes, as it can also retrieve
			*	[Static]Methods, [Static]Fields and EnumValues.
			*
			*	@param id The id of the entity.
			*
			*	@return A constant pointer to the queried entity if it exists, else nullptr.
			*/
			static Entity const*				getEntity(uint64 id)				noexcept;

			/**
			*	@brief Clear the whole database of any registered entity
			*/
			static void							clear()								noexcept;

			/**
			*	@return The unordered_map containing all registered entities sorted by id.
			*/
			static EntitiesById const&			getEntitiesById()					noexcept;

			/**
			*	@return The unordered_map containing all registered archetypes sorted by name.
			*/
			static ArchetypesByName	const&		getArchetypesByName()				noexcept;

			Database& operator=(Database const&)	= delete;
			Database& operator=(Database&&)			= delete;
	};
}