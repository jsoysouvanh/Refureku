/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Template/TypeTemplateArgument.h"
#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgumentImpl.h"

namespace rfk
{
	class TypeTemplateArgument::TypeTemplateArgumentImpl : public TemplateArgument::TemplateArgumentImpl
	{
		private:
			/** Archetype of the template argument. */
			Archetype const* _archetype;

		public:
			inline TypeTemplateArgumentImpl(Archetype const* archetype) noexcept;

			/**
			*	@brief Getter for the field _archetype.
			* 
			*	@return _archetype.
			*/
			RFK_NODISCARD inline Archetype const* getArchetype() const noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/Template/TypeTemplateArgumentImpl.inl"
}