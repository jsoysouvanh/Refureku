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
	//Forward declaration
	class EntityAPI;

	namespace internal
	{
		class DefaultEntityRegistererImpl;
	}

	class DefaultEntityRegistererAPI final
	{
		public:
			REFUREKU_API DefaultEntityRegistererAPI(EntityAPI const& entity)	noexcept;
			DefaultEntityRegistererAPI(DefaultEntityRegistererAPI const&)		= delete;
			DefaultEntityRegistererAPI(DefaultEntityRegistererAPI&&)			= delete;
			REFUREKU_API ~DefaultEntityRegistererAPI()							noexcept;

		private:
			Pimpl<internal::DefaultEntityRegistererImpl> _pimpl;
	};
}