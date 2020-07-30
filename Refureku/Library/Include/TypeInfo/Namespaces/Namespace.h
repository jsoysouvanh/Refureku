/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <unordered_set>

#include "TypeInfo/Entity.h"
#include "TypeInfo/Namespaces/NamespaceFragment.h"
#include "TypeInfo/Archetypes/Archetype.h"

namespace rfk
{
	//Forward declarations
	class Struct;
	class Class;
	class Enum;

	class Namespace final : public Entity
	{
		public:
			/** Collection of all namespaces contained in this namespace. */
			std::unordered_set<Namespace const*, Entity::PtrNameHasher, Entity::PtrEqualName>	nestedNamespaces;

			/** Collection of all archetypes contained in this namespace. */
			std::unordered_set<Archetype const*, Entity::PtrNameHasher, Entity::PtrEqualName>	nestedArchetypes;

			Namespace(std::string&& newName,
					  uint64		newId	= 0u)	noexcept;
			Namespace(Namespace const&)				= delete;
			Namespace(Namespace&&)					= default;
			~Namespace()							= default;

			/**
			*	@brief Retrieve a namespace inside this namespace.
			*	
			*	@param namespaceName Name of the nested namespace to look for.
			*
			*	@return The found nested namespace if it exists, else nullptr.
			*/
			Namespace const*	getNestedNamespace(std::string namespaceName)	const	noexcept;

			/**
			*	@brief Retrieve a struct from this namespace.
			*	
			*	@param structName Name of the struct to look for.
			*
			*	@return The found struct if it exists, else nullptr.
			*/
			Struct const*		getStruct(std::string structName)				const	noexcept;

			/**
			*	@brief Retrieve a class from this namespace.
			*	
			*	@param className Name of the class to look for.
			*
			*	@return The found class if it exists, else nullptr.
			*/
			Class const*		getClass(std::string className)					const	noexcept;

			/**
			*	@brief Retrieve an enum from this namespace.
			*
			*	@param enumName	Name of the enum to look for.
			*
			*	@return The found enum if it exists, else nullptr.
			*/
			Enum const*			getEnum(std::string enumName)					const	noexcept;
	};
}