/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cstddef>	//std::size_t
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
			NamespaceFragment const&	_registeredFragment;

		public:
			inline NamespaceFragmentRegistererImpl(NamespaceFragment const&	namespaceFragment)	noexcept;
			inline ~NamespaceFragmentRegistererImpl()											noexcept;
	};

	#include "Refureku/TypeInfo/Namespace/NamespaceFragmentRegistererImpl.inl"
}