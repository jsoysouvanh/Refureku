/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cstddef>	//std::size_t
#include <memory>	//std::shared_ptr
#include <cassert>

#include "Refureku/TypeInfo/Namespace/NamespaceFragmentRegisterer.h"
#include "Refureku/TypeInfo/Namespace/NamespaceFragment.h"
#include "Refureku/TypeInfo/Namespace/Namespace.h"
#include "Refureku/TypeInfo/DatabaseImpl.h"
#include "Refureku/Properties/Property.h"

namespace rfk
{
	class internal::NamespaceFragmentRegistererImpl final
	{
		private:
			/** Fragment registered by this registerer. */
			NamespaceFragment const&		_registeredFragment;

			/** Namespace this fragment is bound to. */
			std::shared_ptr<Namespace>	_namespaceInstance;

			/**
			*	@brief Add namespace fragment entities to the namespace held by this registerer.
			*/
			void	mergeFragmentToNamespace()						noexcept;

			/**
			*	@brief Append fragment properties to the namespace properties.
			*/
			void	mergeFragmentPropertiesToNamespaceProperties()	noexcept;

			/**
			*	@brief Remove namespace fragment entities from the namespace held by this registerer.
			*/
			void	removeFragmentFromNamespace()					noexcept;

		public:
			inline NamespaceFragmentRegistererImpl(NamespaceFragment const&	namespaceFragment,
												   bool						isFileLevelNamespace)	noexcept;
			inline ~NamespaceFragmentRegistererImpl();

			/**
			*	@brief Getter for the field _namespaceInstance.
			* 
			*	@return _namespaceInstance.
			*/
			RFK_NODISCARD Namespace const* getNamespaceInstance() const	noexcept;

			//===============================================================================
			//** Next methods are public but are only used internally by the implementation. **
			//===============================================================================

			/**
			*	@brief	**INTERNAL USAGE ONLY**
			*			Add a property to the linked namespace if the same property is not there yet.
			* 
			*	@param property Property to add.
			*/
			inline void addPropertyToNamespace(Property const& property)	const	noexcept;

			/**
			*	@brief	**INTERNAL USAGE ONLY**
			*			Add a namespace fragment nested entity to the namespace it is linked to (+ register to the database).
			* 
			*	@param entity Entity to add/register.
			*/
			inline void	addEntityToNamespace(Entity const& entity)		const	noexcept;

			/**
			*	@brief	**INTERNAL USAGE ONLY**
			*			Remove a namespace fragment nested entity from the namespace it is merged to (+ unregister from the database).
			* 
			*	@param entity	Entity to remove/unregister.
			*/
			inline void	removeEntityFromNamespace(Entity const& entity)	const	noexcept;
	};

	#include "Refureku/TypeInfo/Namespace/NamespaceFragmentRegistererImpl.inl"
}