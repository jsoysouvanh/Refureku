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

#include "TypeInfo/Namespace.h"
#include "TypeInfo/Archetypes/Class.h"
#include "TypeInfo/Archetypes/Enum.h"
#include "Misc/FundamentalTypes.h"

namespace rfk
{
	class Database
	{
		friend class NamespaceRegisterer;
		friend class ArchetypeRegisterer;

		private:
			using EntitiesById		= std::unordered_set<Entity const*, Entity::PtrIdHasher, Entity::PtrEqualId>;
			using EntitiesByName	= std::unordered_set<Entity const*, Entity::PtrNameHasher, Entity::PtrEqualName>;

			/** Collection of all registered entities hashed by Id.  */
			static	EntitiesById	_entitiesById;

			/** Collection of all file level entities hashed by name. */
			static	EntitiesByName	_fileLevelEntitiesByName;

			/**
			*	@brief Register a file level entity to the database.
			*	
			*	@param entity The entity to register.
			*/
			static void	registerFileLevelEntity(Entity const& entity)	noexcept;

			/**
			*	@brief Register all nested entities to the _entitiesById map.
			*	
			*	@param entity The parent entity.
			*/
			static void	registerSubEntities(Entity const& entity)		noexcept;
			
			/**
			*	@brief Add all nested entities to the _entitiesById map.
			*	
			*	@param archetype The parent archetype.
			*/
			static void registerSubEntities(Archetype const& archetype)	noexcept;
			
			/**
			*	@brief Add all nested entities to the _entitiesById map.
			*	
			*	@param n The parent namespace.
			*/
			static void registerSubEntities(Namespace const& n)			noexcept;
			
			/**
			*	@brief Add all nested entities to the _entitiesById map.
			*	
			*	@param s The parent struct.
			*/
			static void registerSubEntities(Struct const& s)			noexcept;
			
			/**
			*	@brief Add all nested entities to the _entitiesById map.
			*	
			*	@param e The parent enum.
			*/
			static void registerSubEntities(Enum const& e)				noexcept;

		public:
			Database()					= delete;
			Database(Database const&)	= delete;
			Database(Database&&)		= delete;
			~Database()					= delete;

			/**
			*	@brief Retrieve an entity by id.
			*
			*	This is not limited to archetypes, as it can also retrieve
			*	Namespaces, [Static]Methods, [Static]Fields and EnumValues.
			*
			*	@param id The id of the entity.
			*
			*	@return A constant pointer to the queried entity if it exists, else nullptr.
			*/
			static Entity const*				getEntity(uint64 id)				noexcept;

			/**
			*	@brief Retrieve an entity by name.
			*
			*	@param entityName The name of the entity (Entity::name).
			*
			*	@return A constant pointer to the queried entity if it exists, else nullptr.
			*/
			static Entity const*				getEntity(std::string const& entityName)		noexcept;

			/**
			*	@brief Retrieve a struct by name.
			*
			*	@param structName The name of the struct.
			*
			*	@return A constant pointer to the queried struct if it exists, else nullptr.
			*/
			static Namespace const*				getNamespace(std::string const& namespaceName)	noexcept;

			/**
			*	@brief Retrieve a struct by name.
			*
			*	@param structName The name of the struct.
			*
			*	@return A constant pointer to the queried struct if it exists, else nullptr.
			*/
			static Struct const*				getStruct(std::string const& structName)		noexcept;

			/**
			*	@brief Retrieve a class by name.
			*
			*	@param className The name of the class.
			*
			*	@return A constant pointer to the queried class if it exists, else nullptr.
			*/
			static Class const*					getClass(std::string const& className)			noexcept;

			/**
			*	@brief Retrieve an enum by name.
			*
			*	@param enumName The name of the enum.
			*
			*	@return A constant pointer to the queried enum if it exists, else nullptr.
			*/
			static Enum const*					getEnum(std::string const& enumName)			noexcept;

			/**
			*	@brief Clear the whole database of any registered entity
			*/
			static void							clear()											noexcept;

			/**
			*	@return The unordered_map containing all registered entities sorted by id.
			*/
			static EntitiesById const&			getEntitiesById()								noexcept;

			/**
			*	@return The unordered_map containing all registered entities at file level, hashed by name.
			*/
			static EntitiesByName	const&		getFileLevelEntities()							noexcept;
	};
}