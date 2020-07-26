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
			*	@param structName Name of the nested namespace to look for.
			*
			*	@return The found nested namespace if it exists, else nullptr.
			*/
			Namespace const*					getNestedNamespace(std::string namespaceName)								const	noexcept;

			/**
			*	@param structName	Name of the nested struct to look for.
			*	@param access		Access specifier of the nested struct in this struct. Use EAccessSpecifier::Undefined if it doesn't matter.
			*
			*	@return The found nested struct if it exists, else nullptr.
			*/
			Struct const*						getNestedStruct(std::string			structName,
																EAccessSpecifier	access = EAccessSpecifier::Undefined)	const	noexcept;

			/**
			*	@param className	Name of the nested class to look for.
			*	@param access		Access specifier of the nested class in this struct. Use EAccessSpecifier::Undefined if it doesn't matter.
			*
			*	@return The found nested class if it exists, else nullptr.
			*/
			Class const*						getNestedClass(std::string		className,
															   EAccessSpecifier	access = EAccessSpecifier::Undefined)		const	noexcept;

			/**
			*	@param enumName	Name of the nested enum to look for.
			*	@param access	Access specifier of the nested enum in this struct. Use EAccessSpecifier::Undefined if it doesn't matter.
			*
			*	@return The found nested class if it exists, else nullptr.
			*/
			Enum const*							getNestedEnum(std::string		enumName,
															  EAccessSpecifier	access = EAccessSpecifier::Undefined)		const	noexcept;

			Namespace& operator=(Namespace const&)	= delete;
			Namespace& operator=(Namespace&&)		= default;
	};
}