/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgument.h"
#include "Refureku/TypeInfo/Archetypes/Template/ETemplateParameterKind.h"

namespace rfk
{
	class TemplateArgument::TemplateArgumentImpl
	{
		private:
			/** Template parameter this argument is a value of. */
			ETemplateParameterKind	_templateKind;
			
		public:
			inline	TemplateArgumentImpl(ETemplateParameterKind templateKind)	noexcept;
			virtual ~TemplateArgumentImpl()										= default;

			/**
			*	@brief Getter for the field _boundParameter.
			* 
			*	@return _boundParameter.
			*/
			RFK_NODISCARD inline ETemplateParameterKind getKind()	const	noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgumentImpl.inl"
}