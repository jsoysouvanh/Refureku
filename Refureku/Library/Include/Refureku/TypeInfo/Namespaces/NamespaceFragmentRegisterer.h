/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <memory>

#include "Refureku/Misc/FundamentalTypes.h"

namespace rfk
{
	//Forward declarations
	class Namespace;			
	class NamespaceFragment;

	class NamespaceFragmentRegisterer
	{
		private:
			/** Fragment registered by this registerer. */
			NamespaceFragment const*	_fragment			= nullptr;

			/** Namespace this fragment is bound to. */
			std::shared_ptr<Namespace>	_namespaceInstance	= nullptr;

			/** Registered namespace fragment. */
			NamespaceFragment const*	_mergedNamespaceFragment;

			/**
			*	@brief Add namespace fragment entities to the namespace held by this registerer.
			*	
			*	@param fragment The namespace fragment to merge.
			*/
			void	mergeFragmentToNamespace(NamespaceFragment const* fragment)						noexcept;

			/**
			*	@brief Append fragment properties to the namespace properties.
			*	
			*	@param fragment	The namespace fragment to merge.
			*/
			void	mergeFragmentPropertiesToNamespaceProperties(NamespaceFragment const* fragment)	noexcept;

			/**
			*	@brief Remove namespace fragment entities from the namespace held by this registerer.
			*	
			*	@param fragment The namespace fragment to remove.
			*/
			void	removeFragmentFromNamespace(NamespaceFragment const* fragment)					noexcept;

		public:
			NamespaceFragmentRegisterer()													= default;
			NamespaceFragmentRegisterer(char const*					name,
										uint64						id,
										NamespaceFragment const*	namespaceFragment,
										bool						isFileLevelNamespace)	noexcept;
			NamespaceFragmentRegisterer(NamespaceFragmentRegisterer const&)					= delete;
			NamespaceFragmentRegisterer(NamespaceFragmentRegisterer&&)						= delete;
			~NamespaceFragmentRegisterer()													noexcept;

			/**
			*	@brief Getter for _namespaceInstance.
			*	
			*	@return _namespaceInstance
			*/
			Namespace const* getNamespaceInstance()	const	noexcept;

			NamespaceFragmentRegisterer& operator=(NamespaceFragmentRegisterer const&)	= delete;
			NamespaceFragmentRegisterer& operator=(NamespaceFragmentRegisterer&&)		= delete;
	};
}