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

#include "TypeInfo/Namespaces/Namespace.h"
#include "TypeInfo/Archetypes/Class.h"
#include "TypeInfo/Archetypes/Enum.h"
#include "Misc/FundamentalTypes.h"

namespace rfk
{
	class Database
	{
		friend class NamespaceFragmentRegisterer;
		friend class ArchetypeRegisterer;

		private:
			using EntitiesById		= std::unordered_set<Entity const*, Entity::PtrIdHasher, Entity::PtrEqualId>;
			using EntitiesByName	= std::unordered_set<Entity const*, Entity::PtrNameHasher, Entity::PtrEqualName>;

			/** Collection of all registered entities hashed by Id.  */
			static	EntitiesById	_entitiesById;

			/** Collection of all file level entities hashed by name. */
			static	EntitiesByName	_fileLevelEntitiesByName;

			/**
			*	@brief Register a file level entity to the database (add it to both _entitiesById & _fileLevelEntitiesByName).
			*	
			*	@param entity						The entity to register.
			*	@param shouldRegisterSubEntities	Should sub entities be registered by id recursively?
			*/
			static void	registerFileLevelEntity(Entity const&	entity,
												bool			shouldRegisterSubEntities)	noexcept;

			/**
			*	@brief Register an entity to the database.
			*	
			*	@param entity						The entity to register.
			*	@param shouldRegisterSubEntities	Should sub entities be registered by id recursively?
			*/
			static void registerEntity(Entity const&	entity,
									   bool				shouldRegisterSubEntities)			noexcept;

			/**
			*	@brief Add all nested entities to the _entitiesById map.
			*	
			*	@param archetype The parent archetype.
			*/
			static void registerSubEntities(Archetype const& archetype)						noexcept;
			
			/**
			*	@brief Add all nested entities to the _entitiesById map.
			*	
			*	@param n The parent namespace.
			*/
			static void registerSubEntities(Namespace const& n)								noexcept;
			
			/**
			*	@brief Add all nested entities to the _entitiesById map.
			*	
			*	@param s The parent struct.
			*/
			static void registerSubEntities(Struct const& s)								noexcept;
			
			/**
			*	@brief Add all nested entities to the _entitiesById map.
			*	
			*	@param e The parent enum.
			*/
			static void registerSubEntities(Enum const& e)									noexcept;

			/**
			*	TODO
			*/
			//static Namespace const* getNamespace(std::string	namespaceName,
			//									 bool			allowNestedNamespaces)		noexcept;

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
			static Entity const*			getEntity(uint64 id)					noexcept;

			/**
			*	@brief Retrieve an entity by name.
			*
			*	@param entityName The name of the entity (Entity::name).
			*
			*	@return A constant pointer to the queried entity if it exists, else nullptr.
			*/
			static Entity const*			getEntity(std::string entityName)		noexcept;

			/**
			*	@brief	Retrieve a namespace by name.
			*			Can search nested namespaces directly using :: separator.
			*			Example: getNamespace("namespace1::namespace2") will get the namespace2 nested inside namespace1 if it exists.
			*
			*	@param namespaceName The name of the namespace.
			*
			*	@return A constant pointer to the queried namespace if it exists, else nullptr.
			*
			*	@exception BadNamespaceFormat if the provided namespace name has : instead of :: as a separator, or ends with :.
			*/
			static Namespace const*			getNamespace(std::string namespaceName);

			/**
			*	@brief Retrieve a struct by name.
			*
			*	@param structName The name of the struct.
			*
			*	@return A constant pointer to the queried struct if it exists, else nullptr.
			*/
			static Struct const*			getStruct(std::string structName)		noexcept;

			/**
			*	@brief Retrieve a class by name.
			*
			*	@param className The name of the class.
			*
			*	@return A constant pointer to the queried class if it exists, else nullptr.
			*/
			static Class const*				getClass(std::string className)			noexcept;

			/**
			*	@brief Retrieve an enum by name.
			*
			*	@param enumName The name of the enum.
			*
			*	@return A constant pointer to the queried enum if it exists, else nullptr.
			*/
			static Enum const*				getEnum(std::string enumName)			noexcept;

			/**
			*	@brief Clear the whole database of any registered entity
			*/
			static void						clear()									noexcept;

			/**
			*	@return The unordered_set containing all registered entities hashed by id.
			*/
			static EntitiesById const&		getEntitiesById()						noexcept;

			/**
			*	@return The unordered_set containing all registered entities at file level, hashed by name.
			*/
			static EntitiesByName const&	getFileLevelEntities()					noexcept;
	};
}