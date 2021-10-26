/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <unordered_set>

#include "Refureku/TypeInfo/Namespace/Namespace.h"
#include "Refureku/TypeInfo/Entity/EntityImpl.h"
#include "Refureku/TypeInfo/Archetypes/Archetype.h"
#include "Refureku/TypeInfo/Variables/Variable.h"
#include "Refureku/TypeInfo/Functions/Function.h"
#include "Refureku/TypeInfo/Entity/EntityHash.h"

namespace rfk
{
	class Namespace::NamespaceImpl final : public Entity::EntityImpl
	{
		public:
			using NamespaceHashSet	= std::unordered_set<Namespace const*, EntityPtrNameHash, EntityPtrNameEqual>;
			using ArchetypeHashSet	= std::unordered_set<Archetype const*, EntityPtrNameHash, EntityPtrNameEqual>;
			using VariableHashSet	= std::unordered_set<Variable const*, EntityPtrNameHash, EntityPtrNameEqual>;
			using FunctionHashSet	= std::unordered_multiset<Function const*, EntityPtrNameHash, EntityPtrNameEqual>;

		private:
			/** Collection of all namespaces contained in this namespace. */
			NamespaceHashSet	_namespaces;

			/** Collection of all archetypes contained in this namespace. */
			ArchetypeHashSet	_archetypes;

			/** Collection of all (non-member) variables contained in this namespace. */
			VariableHashSet		_variables;

			/** Collection of all (non-member) functions contained in this namespace. */
			FunctionHashSet		_functions;
			
		public:
			inline NamespaceImpl(char const* name,
								 std::size_t id)		noexcept;

			/**
			*	@brief Add a nested namespace to this namespace.
			* 
			*	@param nestedNamespace The namespace to add.
			*/
			inline void										addNamespace(Namespace const& nestedNamespace)			noexcept;

			/**
			*	@brief Add a nested archetype to this namespace.
			* 
			*	@param archetype The archetype to add.
			*/
			inline void										addArchetype(Archetype const& archetype)					noexcept;

			/**
			*	@brief Add a nested variable to this namespace.
			* 
			*	@param variable The variable to add.
			*/
			inline void										addVariable(Variable const& variable)					noexcept;

			/**
			*	@brief Add a nested function to this namespace.
			* 
			*	@param function The function to add.
			*/
			inline void										addFunction(Function const& function)					noexcept;

			/**
			*	@brief Remove a nested namespace from this namespace.
			* 
			*	@param nestedNamespace The namespace to add.
			*/
			inline void										removeNamespace(Namespace const& nestedNamespace)		noexcept;

			/**
			*	@brief Remove a nested archetype from this namespace.
			* 
			*	@param archetype The archetype to remove.
			*/
			inline void										removeArchetype(Archetype const& archetype)				noexcept;

			/**
			*	@brief Remove a nested variable from this namespace.
			* 
			*	@param variable The variable to remove.
			*/
			inline void										removeVariable(Variable const& variable)					noexcept;

			/**
			*	@brief Remove a nested function from this namespace.
			* 
			*	@param function The function to remove.
			*/
			inline void										removeFunction(Function const& function)					noexcept;

			/**
			*	@brief Getter for the field _namespaces.
			* 
			*	@return _namespaces.
			*/
			RFK_NODISCARD inline NamespaceHashSet const&	getNamespaces()										const	noexcept;

			/**
			*	@brief Getter for the field _archetypes.
			* 
			*	@return _archetypes.
			*/
			RFK_NODISCARD inline ArchetypeHashSet const&	getArchetypes()										const	noexcept;

			/**
			*	@brief Getter for the field _variables.
			* 
			*	@return _variables.
			*/
			RFK_NODISCARD inline VariableHashSet const&		getVariables()										const	noexcept;

			/**
			*	@brief Getter for the field _functions.
			* 
			*	@return _functions.
			*/
			RFK_NODISCARD inline FunctionHashSet const&		getFunctions()										const	noexcept;
	};

	#include "Refureku/TypeInfo/Namespace/NamespaceImpl.inl"
}