/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <unordered_set>

#include "Refureku/TypeInfo/Entity/Entity.h"
#include "Refureku/TypeInfo/Archetypes/Archetype.h"
#include "Refureku/TypeInfo/Variables/Variable.h"
#include "Refureku/TypeInfo/Functions/Function.h"
#include "Refureku/TypeInfo/Functions/FunctionHelper.h"

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
			std::unordered_set<Namespace const*, Entity::PtrNameHasher, Entity::PtrEqualName>		namespaces;

			/** Collection of all archetypes contained in this namespace. */
			std::unordered_set<Archetype const*, Entity::PtrNameHasher, Entity::PtrEqualName>		archetypes;

			/** Collection of all (non-member) variables contained in this namespace. */
			std::unordered_set<Variable const*, Entity::PtrNameHasher, Entity::PtrEqualName>		variables;

			/** Collection of all (non-member) functions contained in this namespace. */
			std::unordered_multiset<Function const*, Entity::PtrNameHasher, Entity::PtrEqualName>	functions;

			Namespace(std::string&& newName,
					  uint64		newId)		noexcept;
			Namespace(Namespace const&)			= delete;
			Namespace(Namespace&&)				= delete;
			~Namespace()						= default;

			/**
			*	@brief Retrieve from this namespace an archetype matching with a given predicate.
			*
			*	@param predicate Predicate returning true for any matching nested archetype.
			*	
			*	@return The first matching archetype if any is found, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Archetype const*>>>
			Archetype const*	getArchetype(Predicate predicate)								const;

			/**
			*	@brief Retrieve a function from this namespace with a specific prototype.
			*
			*	@tparam FunctionSignature	Signature of the function to look for.
			*								The signature must be formatted like <ReturnType(ArgType1, ArgType2, ...)>
			*
			*	@param functionName	The name of the function.
			*	@param flags		Flags describing the queried function.
			*						The result function will have at least the provided flags.
			*
			*	@return The function matching with the provided prototype, name and flags if it exists, else nullptr.
			*/
			template <typename FunctionSignature>
			Function const*		getFunction(std::string		functionName,
											EFunctionFlags	flags = EFunctionFlags::Default)	const	noexcept;

			/**
			*	@brief Retrieve from this namespace a nested namespace matching with a given predicate.
			*
			*	@param predicate Predicate returning true for any matching nested namespace.
			*	
			*	@return The first matching nested namespace if any is found, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Namespace const*>>>
			Namespace const*	getNamespace(Predicate predicate)								const;

			/**
			*	@brief Retrieve a namespace contained in this namespace.
			*	
			*	@param namespaceName Name of the nested namespace to look for.
			*
			*	@return The found nested namespace if it exists, else nullptr.
			*/
			Namespace const*	getNamespace(std::string namespaceName)							const	noexcept;

			/**
			*	@brief Retrieve from this namespace a struct matching with a given predicate.
			*
			*	@param predicate Predicate returning true for any matching struct.
			*	
			*	@return The first matching struct if any is found, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Struct const*>>>
			Struct const*		getStruct(Predicate predicate)									const;

			/**
			*	@brief Retrieve a struct from this namespace.
			*	
			*	@param structName Name of the struct to look for.
			*
			*	@return The found struct if it exists, else nullptr.
			*/
			Struct const*		getStruct(std::string structName)								const	noexcept;

			/**
			*	@brief Retrieve from this namespace a class matching with a given predicate.
			*
			*	@param predicate Predicate returning true for any matching class.
			*	
			*	@return The first matching class if any is found, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Class const*>>>
			Class const*		getClass(Predicate predicate)									const;

			/**
			*	@brief Retrieve a class from this namespace.
			*	
			*	@param className Name of the class to look for.
			*
			*	@return The found class if it exists, else nullptr.
			*/
			Class const*		getClass(std::string className)									const	noexcept;

			/**
			*	@brief Retrieve from this namespace an enum matching with a given predicate.
			*
			*	@param predicate Predicate returning true for any matching enum.
			*	
			*	@return The first matching enum if any is found, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Enum const*>>>
			Enum const*			getEnum(Predicate predicate)									const;

			/**
			*	@brief Retrieve an enum from this namespace.
			*
			*	@param enumName	Name of the enum to look for.
			*
			*	@return The found enum if it exists, else nullptr.
			*/
			Enum const*			getEnum(std::string enumName)									const	noexcept;

			/**
			*	@brief Retrieve from this namespace a variable matching with a given predicate.
			*
			*	@param predicate Predicate returning true for any matching variable.
			*	
			*	@return The first matching variable if any is found, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Variable const*>>>
			Variable const*		getVariable(Predicate predicate)								const;

			/**
			*	@brief Retrieve a variable from this namespace.
			*	
			*	@param variableName The name of the variable.
			*	@param flags		Flags describing the queried variable.
			*						The result variable will have at least the provided flags.
			*	
			*	@return The found variable if it exists, else nullptr.
			*/
			Variable const*		getVariable(std::string variableName,
											EVarFlags	flags = EVarFlags::Default)				const	noexcept;

			/**
			*	@brief Retrieve from this namespace a function matching with a given predicate.
			*
			*	@param predicate Predicate returning true for any matching function.
			*	
			*	@return The first matching function if any is found, else nullptr.
			*/
			template <typename Predicate, typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, Function const*>>>
			Function const*		getFunction(Predicate predicate)								const;

			/**
			*	@brief Retrieve a function from this namespace.
			*	
			*	@param functionName The name of the function.
			*	@param flags		Flags describing the queried function.
			*						The result function will have at least the provided flags.
			*	
			*	@return The first function matching the provided name and flags if it exists, else nullptr.
			*/
			Function const*		getFunction(std::string		functionName,
											EFunctionFlags	flags = EFunctionFlags::Default)	const noexcept;
	};

	#include "Refureku/TypeInfo/Namespaces/Namespace.inl"
}