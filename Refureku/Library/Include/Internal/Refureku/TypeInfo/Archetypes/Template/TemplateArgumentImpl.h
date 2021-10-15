/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgument.h"

namespace rfk
{
	class TemplateArgument::TemplateArgumentImpl
	{
		private:
			/** Template parameter this argument is a value of. */
			TemplateParameter const&	_boundParameter;
			
		public:
			inline TemplateArgumentImpl(TemplateParameter const& boundParameter) noexcept;

			/**
			*	@brief Getter for the field _boundParameter.
			* 
			*	@return _boundParameter.
			*/
			RFK_NODISCARD inline TemplateParameter const& getBoundParameter()	const	noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgumentImpl.inl"
}