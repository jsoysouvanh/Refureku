/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/Utility/Pimpl.h"

namespace rfk
{
	//Forward declarations
	class NamespaceAPI;
	class NamespaceFragmentAPI;

	namespace internal
	{
		//Forward declaration
		class NamespaceFragmentRegistererImpl;
	}

	class NamespaceFragmentRegistererAPI final
	{
		public:
			REFUREKU_API NamespaceFragmentRegistererAPI(char const*					name,
														std::size_t					id,
														NamespaceFragmentAPI const&	namespaceFragment,
														bool						isFileLevelNamespace)	noexcept;
			NamespaceFragmentRegistererAPI(NamespaceFragmentRegistererAPI const&)							= delete;
			NamespaceFragmentRegistererAPI(NamespaceFragmentRegistererAPI&&)								= delete;
			REFUREKU_API ~NamespaceFragmentRegistererAPI()													noexcept;

			/**
			*	@brief Get the namespace instance this fragment has been merged to.
			*	
			*	@return The namespace instance this fragment has been merged to.
			*/
			RFK_NODISCARD REFUREKU_API NamespaceAPI const* getNamespaceInstance()	const	noexcept;

		private:
			Pimpl<internal::NamespaceFragmentRegistererImpl> _pimpl;
	};
}