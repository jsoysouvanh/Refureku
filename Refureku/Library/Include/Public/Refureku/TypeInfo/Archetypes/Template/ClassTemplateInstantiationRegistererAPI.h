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
	class ClassTemplateInstantiationAPI;

	namespace internal
	{
		class ClassTemplateInstantiationRegistererImpl;
	}

	class ClassTemplateInstantiationRegistererAPI final
	{
		public:
			REFUREKU_API ClassTemplateInstantiationRegistererAPI(ClassTemplateInstantiationAPI const& instantiation)	noexcept;
			ClassTemplateInstantiationRegistererAPI(ClassTemplateInstantiationRegistererAPI const&)						= delete;
			ClassTemplateInstantiationRegistererAPI(ClassTemplateInstantiationRegistererAPI&&)							= delete;
			REFUREKU_API ~ClassTemplateInstantiationRegistererAPI()														noexcept;

		private:
			/** Pointer to the concrete implementation. */
			Pimpl<internal::ClassTemplateInstantiationRegistererImpl> _pimpl;
	};
}