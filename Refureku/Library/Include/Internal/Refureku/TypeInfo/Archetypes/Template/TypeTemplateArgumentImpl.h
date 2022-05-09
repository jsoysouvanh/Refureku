/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Template/TypeTemplateArgument.h"
#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgumentImpl.h"
#include "Refureku/TypeInfo/Type.h"

namespace rfk
{
	class TypeTemplateArgument::TypeTemplateArgumentImpl : public TemplateArgument::TemplateArgumentImpl
	{
		private:
			/** Archetype of the template argument. */
			Type const& _type;

		public:
			inline TypeTemplateArgumentImpl(Type const& type) noexcept;

			/**
			*	@brief Getter for the field _archetype.
			* 
			*	@return _archetype.
			*/
			RFK_NODISCARD inline Type const& getType() const noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/Template/TypeTemplateArgumentImpl.inl"
}