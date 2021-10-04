/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/Utility/Pimpl.h"
#include "Refureku/TypeInfo/Archetypes/Template/ETemplateParameterKind.h"

namespace rfk
{
	class TemplateParameterAPI final
	{
		public:
			REFUREKU_API TemplateParameterAPI(char const*				name,
											  ETemplateParameterKind	kind)	noexcept;
			REFUREKU_API ~TemplateParameterAPI()								noexcept;

		private:
			//Forward declaration
			class TemplateParameterImpl;

			/** Pointer to the TemplateParameter concrete implementation. */
			Pimpl<TemplateParameterImpl>	_pimpl;
	};
}