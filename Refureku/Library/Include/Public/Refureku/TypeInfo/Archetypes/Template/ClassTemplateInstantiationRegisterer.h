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
	class ClassTemplateInstantiation;

	namespace internal
	{
		class ClassTemplateInstantiationRegistererImpl;
	}

	class ClassTemplateInstantiationRegisterer final
	{
		public:
			REFUREKU_API ClassTemplateInstantiationRegisterer(ClassTemplateInstantiation const& instantiation)	noexcept;
			ClassTemplateInstantiationRegisterer(ClassTemplateInstantiationRegisterer const&)					= delete;
			ClassTemplateInstantiationRegisterer(ClassTemplateInstantiationRegisterer&&)						= delete;
			REFUREKU_API ~ClassTemplateInstantiationRegisterer()												noexcept;

		private:
			/** Pointer to the concrete ClassTemplateInstantiationRegisterer implementation. */
			Pimpl<internal::ClassTemplateInstantiationRegistererImpl> _pimpl;
	};
}