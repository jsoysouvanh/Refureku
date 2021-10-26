/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/Misc/Pimpl.h"

namespace rfk
{
	//Forward declarations
	class Namespace;
	class NamespaceFragment;

	namespace internal
	{
		//Forward declaration
		class NamespaceFragmentRegistererImpl;
	}

	class NamespaceFragmentRegisterer final
	{
		public:
			REFUREKU_API NamespaceFragmentRegisterer(NamespaceFragment const&	namespaceFragment,
													 bool						isFileLevelNamespace)	noexcept;
			NamespaceFragmentRegisterer(NamespaceFragmentRegisterer const&)								= delete;
			NamespaceFragmentRegisterer(NamespaceFragmentRegisterer&&)									= delete;
			REFUREKU_API ~NamespaceFragmentRegisterer()													noexcept;

			/**
			*	@brief Get the namespace instance this fragment has been merged to.
			*	
			*	@return The namespace instance this fragment has been merged to.
			*/
			RFK_NODISCARD REFUREKU_API Namespace const* getNamespaceInstance()	const	noexcept;

		private:
			Pimpl<internal::NamespaceFragmentRegistererImpl> _pimpl;
	};
}