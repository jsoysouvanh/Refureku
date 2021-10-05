/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationRegistererAPI.h"
#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationAPI.h"
#include "Refureku/TypeInfo/DatabaseImpl.h"

namespace rfk
{
	class internal::ClassTemplateInstantiationRegistererImpl final
	{
		private:
			/** Registered template instantiation. */
			ClassTemplateInstantiationAPI const&	_registeredClassTemplateInstantiation;

		public:
			inline ClassTemplateInstantiationRegistererImpl(ClassTemplateInstantiationAPI const& instantiation)	noexcept;
			inline ~ClassTemplateInstantiationRegistererImpl()													noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationRegistererImpl.inl"
}