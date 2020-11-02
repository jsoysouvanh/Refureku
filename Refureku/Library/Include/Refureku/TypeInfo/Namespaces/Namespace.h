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
											EFunctionFlags	flags = EFunctionFlags::Default)	const noexcept;

			/**
			*	@brief Retrieve a namespace contained in this namespace.
			*	
			*	@param namespaceName Name of the nested namespace to look for.
			*
			*	@return The found nested namespace if it exists, else nullptr.
			*/
			Namespace const*	getNamespace(std::string namespaceName)							const noexcept;

			/**
			*	@brief Retrieve a struct from this namespace.
			*	
			*	@param structName Name of the struct to look for.
			*
			*	@return The found struct if it exists, else nullptr.
			*/
			Struct const*		getStruct(std::string structName)								const noexcept;

			/**
			*	@brief Retrieve a class from this namespace.
			*	
			*	@param className Name of the class to look for.
			*
			*	@return The found class if it exists, else nullptr.
			*/
			Class const*		getClass(std::string className)									const noexcept;

			/**
			*	@brief Retrieve an enum from this namespace.
			*
			*	@param enumName	Name of the enum to look for.
			*
			*	@return The found enum if it exists, else nullptr.
			*/
			Enum const*			getEnum(std::string enumName)									const noexcept;

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
											EVarFlags	flags = EVarFlags::Default)				const noexcept;

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