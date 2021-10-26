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
	//Forward declaration
	class Entity;

	namespace internal
	{
		class DefaultEntityRegistererImpl;
	}

	class DefaultEntityRegisterer final
	{
		public:
			REFUREKU_API DefaultEntityRegisterer(Entity const& entity)	noexcept;
			DefaultEntityRegisterer(DefaultEntityRegisterer const&)		= delete;
			DefaultEntityRegisterer(DefaultEntityRegisterer&&)			= delete;
			REFUREKU_API ~DefaultEntityRegisterer()						noexcept;

		private:
			/** Pointer to DefaultEntityRegisterer implementation. */
			Pimpl<internal::DefaultEntityRegistererImpl> _pimpl;
	};
}