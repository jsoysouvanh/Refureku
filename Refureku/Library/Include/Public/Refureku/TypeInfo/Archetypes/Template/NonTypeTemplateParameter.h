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
	//Forward declaration
	class Archetype;

	class NonTypeTemplateParameter final : public TemplateParameter
	{
		public:
			REFUREKU_API NonTypeTemplateParameter(char const*		name,
												  Archetype const*	archetype)	noexcept;
			REFUREKU_API ~NonTypeTemplateParameter()							noexcept;

			/**
			*	@brief Get the archetype of this non-type template parameter.
			* 
			*	@return The archetype of this non-type template parameter.
			*/
			RFK_NODISCARD REFUREKU_API Archetype const* getArchetype()	const	noexcept;

		protected:
			//Forward declaration
			class NonTypeTemplateParameterImpl;

			RFK_GEN_GET_PIMPL(NonTypeTemplateParameterImpl, TemplateParameter::getPimpl())
	};
}