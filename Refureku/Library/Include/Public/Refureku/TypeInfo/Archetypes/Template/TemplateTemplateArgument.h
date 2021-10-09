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
	//Forward declaration
	class ClassTemplate;

	class TemplateTemplateArgument : public TemplateArgument
	{
		public:
			REFUREKU_API TemplateTemplateArgument(TemplateParameter const&	boundParameter,
												  ClassTemplate const*		value)			noexcept;
			REFUREKU_API ~TemplateTemplateArgument()										noexcept;

			/**
			*	@brief Get the value of the argument.
			* 
			*	@return The value of the argument.
			*/
			RFK_NODISCARD REFUREKU_API ClassTemplate const*	getValue()	const	noexcept;

		protected:
			//Forward declaration
			class TemplateTemplateArgumentImpl;
	};
}