/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Entity/Entity.h"
#include "Refureku/TypeInfo/Variables/EVarFlags.h"
#include "Refureku/TypeInfo/Functions/EFunctionFlags.h"
#include "Refureku/TypeInfo/Functions/FunctionHelper.h"

namespace rfk
{
	//Forward declarations
	class Struct;
	using Class = Struct;
	class Enum;
	class Variable;
	class Function;
	class Archetype;

	class Namespace final : public Entity
	{
		public:
			REFUREKU_INTERNAL Namespace(char const*	name,
										std::size_t	id)		noexcept;
			Namespace(Namespace&&)							= delete;
			REFUREKU_INTERNAL ~Namespace()					noexcept;

			/**
			*	@brief Retrieve a namespace contained in this namespace.
			*	
			*	@param name Name of the nested namespace to look for.
			*
			*	@return The found nested namespace if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API Namespace const*				getNamespaceByName(char const* name)								const	noexcept;

			/**
			*	@brief Retrieve the first nested namespace satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid namespace.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return The first found namespace satisfying the predicate if any, else nullptr.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API Namespace const*				getNamespaceByPredicate(Predicate<Namespace>	predicate,
																							void*					userData)			const;

			/**
			*	@brief Retrieve all nested namespaces satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid namespace.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return All nested namespaces satisfying the provided predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API Vector<Namespace const*>		getNamespacesByPredicate(Predicate<Namespace>	predicate,
																							 void*					userData)			const;

			/**
			*	@brief Execute the given visitor on all nested namespaces.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool										foreachNamespace(Visitor<Namespace>	visitor,
																					 void*				userData)						const;

			/**
			*	@brief Get the number of namespaces nested in this namespace.
			* 
			*	@return The number of namespaces nested in this namespace.
			*/
			REFUREKU_API std::size_t								getNamespacesCount()												const	noexcept;

			/**
			*	@brief Retrieve a struct from this namespace.
			*	
			*	@param name Name of the struct to look for.
			*
			*	@return The found struct if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API Struct const*				getStructByName(char const* name)									const	noexcept;

			/**
			*	@brief Retrieve the first nested struct satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid namespace.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return The first found struct satisfying the predicate if any, else nullptr.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API Struct const*				getStructByPredicate(Predicate<Struct>	predicate,
																						 void*				userData)					const;

			/**
			*	@brief Retrieve all nested structs satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid namespace.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return All nested structs satisfying the provided predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API Vector<Struct const*>		getStructsByPredicate(Predicate<Struct> predicate,
																						  void*				userData)					const;

			/**
			*	@brief Execute the given visitor on all nested structs.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool										foreachStruct(Visitor<Struct>	visitor,
																				  void*				userData)							const;

			/**
			*	@brief Retrieve a class from this namespace.
			*	
			*	@param name Name of the class to look for.
			*
			*	@return The found class if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API Class const*					getClassByName(char const* name)									const	noexcept;

			/**
			*	@brief Retrieve the first nested class satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid namespace.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return The first found class satisfying the predicate if any, else nullptr.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API Class const*					getClassByPredicate(Predicate<Class>	predicate,
																						void*				userData)					const;

			/**
			*	@brief Retrieve all nested classes satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid namespace.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return All nested classes satisfying the provided predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API Vector<Class const*>			getClassesByPredicate(Predicate<Class>	predicate,
																						  void*				userData)					const;

			/**
			*	@brief Execute the given visitor on all nested classes.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool										foreachClass(Visitor<Class>	visitor,
																				  void*			userData)								const;

			/**
			*	@brief Retrieve an enum from this namespace.
			*
			*	@param name	Name of the enum to look for.
			*
			*	@return The found enum if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API Enum const*					getEnumByName(char const* name)										const	noexcept;

			/**
			*	@brief Retrieve the first nested enum satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid namespace.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return The first found enum satisfying the predicate if any, else nullptr.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API Enum const*					getEnumByPredicate(Predicate<Enum>	predicate,
																					   void*			userData)						const;

			/**
			*	@brief Retrieve all nested enums satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid namespace.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return All nested enums satisfying the provided predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API Vector<Enum const*>			getEnumsByPredicate(Predicate<Enum>	predicate,
																						void*			userData)						const;

			/**
			*	@brief Execute the given visitor on all nested enums.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool										foreachEnum(Visitor<Enum>	visitor,
																				 void*			userData)								const;

			/**
			*	@brief Execute the given visitor on all nested archetypes.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially throw from the provided visitor.
			*/
			REFUREKU_API bool										foreachArchetype(Visitor<Archetype>	visitor,
																					 void*				userData)						const;

			/**
			*	@brief Get the number of archetypes nested in this namespace.
			* 
			*	@return The number of archetypes nested in this namespace.
			*/
			REFUREKU_API std::size_t								getArchetypesCount()												const	noexcept;

			/**
			*	@brief Retrieve a variable from this namespace.
			*	
			*	@param name		The name of the variable.
			*	@param flags	Flags describing the queried variable.
			*					The result variable will have at least the provided flags.
			*	
			*	@return The found variable if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API Variable const*				getVariableByName(char const*	name,
																					  EVarFlags		flags = EVarFlags::Default)			const	noexcept;

			/**
			*	@brief Retrieve the first nested variable satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid namespace.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return The first found variable satisfying the predicate if any, else nullptr.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API Variable const*				getVariableByPredicate(Predicate<Variable>	predicate,
																						   void*				userData)				const;

			/**
			*	@brief Retrieve all nested variables satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid namespace.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return All nested variables satisfying the provided predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API Vector<Variable const*>		getVariablesByPredicate(Predicate<Variable>	predicate,
																							void*				userData)				const;

			/**
			*	@brief Execute the given visitor on all nested variables.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool										foreachVariable(Visitor<Variable>	visitor,
																					void*				userData)						const;

			/**
			*	@brief Get the number of variables nested in this namespace.
			* 
			*	@return The number of variables nested in this namespace.
			*/
			REFUREKU_API std::size_t								getVariablesCount()													const	noexcept;

			/**
			*	@brief Retrieve a function with a given name and signature from this namespace.
			*	
			*	@param name		The name of the function.
			*	@param flags	Flags describing the queried function.
			*					The result function will have at least the provided flags.
			*	
			*	@return The first function matching the provided name and flags if it exists, else nullptr.
			*/
			template <typename FunctionSignature>
			RFK_NODISCARD Function const*							getFunctionByName(char const*	 name,
																					  EFunctionFlags flags = EFunctionFlags::Default)	const	noexcept;

			/**
			*	@brief Retrieve a function with a given name from this namespace.
			*	
			*	@param name		The name of the function.
			*	@param flags	Flags describing the queried function.
			*					The result function will have at least the provided flags.
			*	
			*	@return The first function matching the provided name and flags if it exists, else nullptr.
			*/
			RFK_NODISCARD REFUREKU_API Function const*				getFunctionByName(char const*	 name,
																					  EFunctionFlags flags = EFunctionFlags::Default)	const	noexcept;

			/**
			*	@brief Retrieve all functions with a given name from this namespace.
			*	
			*	@param name		The name of the function.
			*	@param flags	Flags describing the queried function.
			*					The result function will have at least the provided flags.
			*	
			*	@return All functions matching the provided name and flags.
			*/
			RFK_NODISCARD REFUREKU_API Vector<Function const*>		getFunctionsByName(char const*	  name,
																					   EFunctionFlags flags = EFunctionFlags::Default)	const	noexcept;

			/**
			*	@brief Retrieve the first nested function satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid namespace.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return The first found function satisfying the predicate if any, else nullptr.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API Function const*				getFunctionByPredicate(Predicate<Function>	predicate,
																						   void*				userData)				const;

			/**
			*	@brief Retrieve all nested functions satisfying the provided predicate.
			*	
			*	@param predicate	Predicate defining a valid namespace.
			*	@param userData		User data forwarded to the predicate calls.
			* 
			*	@return All nested functions satisfying the provided predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			RFK_NODISCARD REFUREKU_API Vector<Function const*>		getFunctionsByPredicate(Predicate<Function>	predicate,
																							void*				userData)				const;

			/**
			*	@brief Execute the given visitor on all nested functions.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool										foreachFunction(Visitor<Function>	visitor,
																					void*				userData)						const;

			/**
			*	@brief Get the number of functions nested in this namespace.
			* 
			*	@return The number of functions nested in this namespace.
			*/
			REFUREKU_API std::size_t								getFunctionsCount()													const	noexcept;

			/**
			*	@brief Add a nested namespace to this namespace.
			* 
			*	@param nestedNamespace The namespace to add.
			*/
			REFUREKU_API void										addNamespace(Namespace const& nestedNamespace)								noexcept;

			/**
			*	@brief Add a nested archetype to this namespace.
			* 
			*	@param archetype The archetype to add.
			*/
			REFUREKU_API void										addArchetype(Archetype const& archetype)									noexcept;

			/**
			*	@brief Add a nested variable to this namespace.
			* 
			*	@param variable The variable to add.
			*/
			REFUREKU_API void										addVariable(Variable const& variable)										noexcept;

			/**
			*	@brief Add a nested function to this namespace.
			* 
			*	@param function The function to add.
			*/
			REFUREKU_API void										addFunction(Function const& function)										noexcept;

			/**
			*	@brief Remove a nested namespace from this namespace.
			* 
			*	@param nestedNamespace The namespace to add.
			*/
			REFUREKU_API void										removeNamespace(Namespace const& nestedNamespace)							noexcept;

			/**
			*	@brief Remove a nested archetype from this namespace.
			* 
			*	@param archetype The archetype to remove.
			*/
			REFUREKU_API void										removeArchetype(Archetype const& archetype)									noexcept;

			/**
			*	@brief Remove a nested variable from this namespace.
			* 
			*	@param variable The variable to remove.
			*/
			REFUREKU_API void										removeVariable(Variable const& variable)									noexcept;

			/**
			*	@brief Remove a nested function from this namespace.
			* 
			*	@param function The function to remove.
			*/
			REFUREKU_API void										removeFunction(Function const& function)									noexcept;

		private:
			//Forward declaration
			class NamespaceImpl;

			RFK_GEN_GET_PIMPL(NamespaceImpl, Entity::getPimpl())
	};

	REFUREKU_TEMPLATE_API(rfk::Allocator<Namespace const*>);
	REFUREKU_TEMPLATE_API(rfk::Vector<Namespace const*, rfk::Allocator<Namespace const*>>);

	#include "Refureku/TypeInfo/Namespace/Namespace.inl"
}