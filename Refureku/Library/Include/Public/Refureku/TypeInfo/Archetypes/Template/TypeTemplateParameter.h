/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Template/TemplateParameter.h"

namespace rfk
{
	class TypeTemplateParameter : public TemplateParameter
	{
		public:
			REFUREKU_API TypeTemplateParameter(char const* name)	noexcept;
			REFUREKU_API ~TypeTemplateParameter()					noexcept;

		protected:
			//Forward declaration
			class TypeTemplateParameterImpl;
	};
}