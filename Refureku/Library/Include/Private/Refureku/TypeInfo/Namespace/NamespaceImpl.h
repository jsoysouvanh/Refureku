/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <unordered_set>

#include "Refureku/TypeInfo/Namespace/NamespaceAPI.h"
#include "Refureku/TypeInfo/Entity/EntityImpl.h"
#include "Refureku/TypeInfo/Archetypes/ArchetypeAPI.h"
#include "Refureku/TypeInfo/Variables/VariableAPI.h"
#include "Refureku/TypeInfo/Functions/FunctionAPI.h"
#include "Refureku/TypeInfo/Entity/EntityHash.h"

namespace rfk
{
	class NamespaceAPI::NamespaceImpl final : public Entity::EntityImpl
	{
		public:
			using NamespaceHashSet	= std::unordered_set<NamespaceAPI const*, EntityPtrNameHash, EntityPtrNameEqual>;
			using ArchetypeHashSet	= std::unordered_set<ArchetypeAPI const*, EntityPtrNameHash, EntityPtrNameEqual>;
			using VariableHashSet	= std::unordered_set<VariableAPI const*, EntityPtrNameHash, EntityPtrNameEqual>;
			using FunctionHashSet	= std::unordered_multiset<FunctionAPI const*, EntityPtrNameHash, EntityPtrNameEqual>;

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
			inline void										addNamespace(NamespaceAPI const& nestedNamespace)			noexcept;

			/**
			*	@brief Add a nested archetype to this namespace.
			* 
			*	@param archetype The archetype to add.
			*/
			inline void										addArchetype(ArchetypeAPI const& archetype)					noexcept;

			/**
			*	@brief Add a nested variable to this namespace.
			* 
			*	@param variable The variable to add.
			*/
			inline void										addVariable(VariableAPI const& variable)					noexcept;

			/**
			*	@brief Add a nested function to this namespace.
			* 
			*	@param function The function to add.
			*/
			inline void										addFunction(FunctionAPI const& function)					noexcept;

			/**
			*	@brief Remove a nested namespace from this namespace.
			* 
			*	@param nestedNamespace The namespace to add.
			*/
			inline void										removeNamespace(NamespaceAPI const& nestedNamespace)		noexcept;

			/**
			*	@brief Remove a nested archetype from this namespace.
			* 
			*	@param archetype The archetype to remove.
			*/
			inline void										removeArchetype(ArchetypeAPI const& archetype)				noexcept;

			/**
			*	@brief Remove a nested variable from this namespace.
			* 
			*	@param variable The variable to remove.
			*/
			inline void										removeVariable(VariableAPI const& variable)					noexcept;

			/**
			*	@brief Remove a nested function from this namespace.
			* 
			*	@param function The function to remove.
			*/
			inline void										removeFunction(FunctionAPI const& function)					noexcept;

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