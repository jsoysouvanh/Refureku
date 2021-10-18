/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Template/TemplateTemplateArgument.h"
#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgumentImpl.h"

namespace rfk
{
	class TemplateTemplateArgument::TemplateTemplateArgumentImpl : public TemplateArgument::TemplateArgumentImpl
	{
		private:
			/** Pointer to the argument template class archetype. Can be nullptr if the provided template class is not reflected. */
			ClassTemplate const* _value;

		public:
			inline TemplateTemplateArgumentImpl(ClassTemplate const* value)	noexcept;

			/**
			*	@brief Getter for the field _value.
			* 
			*	@return _value.
			*/
			RFK_NODISCARD inline ClassTemplate const* getValue() const noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/Template/TemplateTemplateArgumentImpl.inl"
}