/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateParameter.h"
#include "Refureku/TypeInfo/Archetypes/Template/TemplateParameterImpl.h"

namespace rfk
{
	class NonTypeTemplateParameter::NonTypeTemplateParameterImpl final : public TemplateParameter::TemplateParameterImpl
	{
		private:
			/** Archetype of the non-type parameter. */
			Archetype const*	_archetype;

		public:
			inline NonTypeTemplateParameterImpl(char const*			name,
												Archetype const*	archetype) noexcept;

			/**
			*	@brief Getter for the field _archetype.
			* 
			*	@return _archetype.
			*/
			RFK_NODISCARD inline Archetype const* getArchetype()	const	noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateParameterImpl.inl"
}