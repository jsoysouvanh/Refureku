/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgumentAPI.h"

namespace rfk
{
	class TemplateArgumentAPI::TemplateArgumentImpl final
	{
		private:
			/** Template parameter this argument is a value of. */
			TemplateParameterAPI const&	_boundParameter;
			
			/** Archetype used for a template argument. */
			//TODO: Change THIS
			Archetype const*			_archetype = nullptr;

		public:
			inline TemplateArgumentImpl(TemplateParameterAPI const& boundParameter) noexcept;

			/**
			*	@brief Getter for the field _boundParameter.
			* 
			*	@return _boundParameter.
			*/
			RFK_NODISCARD inline TemplateParameterAPI const& getBoundParameter()	const	noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgumentImpl.inl"
}