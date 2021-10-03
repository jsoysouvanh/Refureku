/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Entity/Entity.h"
#include "Refureku/TypeInfo/Variables/EVarFlags.h"
#include "Refureku/TypeInfo/Functions/EFunctionFlags.h"

namespace rfk
{
	//Forward declarations
	class StructAPI;
	class EnumAPI;
	class VariableAPI;
	class FunctionAPI;
	class ArchetypeAPI;

	namespace internal
	{
		class NamespaceFragmentRegistererImpl;
	}

	class NamespaceAPI final : public EntityAPI
	{
		public:
			REFUREKU_INTERNAL NamespaceAPI(char const*	name,
										   std::size_t	id)		noexcept;
			NamespaceAPI(NamespaceAPI&&)						= delete;
			REFUREKU_INTERNAL ~NamespaceAPI()					noexcept;

			/**
			*	@brief Retrieve a namespace contained in this namespace.
			*	
			*	@param name Name of the nested namespace to look for.
			*
			*	@return The found nested namespace if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API NamespaceAPI const*	getNamespaceByName(char const* name)								const	noexcept;

			/**
			*	@brief Execute the given visitor on all nested namespaces.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			*/
			REFUREKU_API bool								foreachNestedNamespace(bool (*visitor)(NamespaceAPI const&,
																								   void*),
																				   void* userData)								const	noexcept;

			/**
			*	@brief Retrieve a struct from this namespace.
			*	
			*	@param name Name of the struct to look for.
			*
			*	@return The found struct if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API StructAPI const*		getStructByName(char const* name)									const	noexcept;

			/**
			*	@brief Retrieve a class from this namespace.
			*	
			*	@param name Name of the class to look for.
			*
			*	@return The found class if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API StructAPI const*		getClassByName(char const* name)									const	noexcept;

			/**
			*	@brief Retrieve an enum from this namespace.
			*
			*	@param name	Name of the enum to look for.
			*
			*	@return The found enum if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API EnumAPI const*		getEnumByName(char const* name)										const	noexcept;

			/**
			*	@brief Execute the given visitor on all nested archetypes.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			*/
			REFUREKU_API bool								foreachNestedArchetype(bool (*visitor)(ArchetypeAPI const&,
																								   void*),
																				   void* userData)								const	noexcept;

			/**
			*	@brief Retrieve a variable from this namespace.
			*	
			*	@param name		The name of the variable.
			*	@param flags	Flags describing the queried variable.
			*					The result variable will have at least the provided flags.
			*	
			*	@return The found variable if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API VariableAPI const*	getVariableByName(char const* name,
																			  EVarFlags	  flags = EVarFlags::Default)			const	noexcept;

			/**
			*	@brief Execute the given visitor on all nested variables.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			*/
			REFUREKU_API bool								foreachNestedVariable(bool (*visitor)(VariableAPI const&,
																								  void*),
																				  void* userData)								const	noexcept;

			/**
			*	@brief Retrieve a function from this namespace.
			*	
			*	@param name		The name of the function.
			*	@param flags	Flags describing the queried function.
			*					The result function will have at least the provided flags.
			*	
			*	@return The first function matching the provided name and flags if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API FunctionAPI const*	getFunctionByName(char const*	 name,
																			  EFunctionFlags flags = EFunctionFlags::Default)	const	noexcept;

			/**
			*	@brief Execute the given visitor on all nested functions.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			*/
			REFUREKU_API bool								foreachNestedFunction(bool (*visitor)(FunctionAPI const&,
																								  void*),
																				  void* userData)								const	noexcept;

		private:
			//Forward declaration
			class NamespaceImpl;

		friend internal::NamespaceFragmentRegistererImpl; //Can access implementation
	};
}