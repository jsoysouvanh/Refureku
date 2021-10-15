/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Template/TypeTemplateParameter.h"
#include "Refureku/TypeInfo/Archetypes/Template/TemplateParameterImpl.h"

namespace rfk
{
	class TypeTemplateParameter::TypeTemplateParameterImpl final : public TemplateParameter::TemplateParameterImpl
	{
		private:
				

		public:
			inline TypeTemplateParameterImpl(char const* name) noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/Template/TypeTemplateParameterImpl.inl"
}