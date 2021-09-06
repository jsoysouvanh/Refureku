/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <vector>

#include "Refureku/TypeInfo/Archetypes/ETemplateParameterKind.h"
#include "Refureku/TypeInfo/Archetypes/Archetype.h"

namespace rfk
{
	struct TemplateParameter
	{
		/** Name of the template parameter. */
		std::string				name;

		/** Kind of template parameter. */
		ETemplateParameterKind	kind;
	};

	struct TypeTemplateParameter : public TemplateParameter
	{
		TypeTemplateParameter(std::string&& name) noexcept;
	};

	struct NonTypeTemplateParameter : public TemplateParameter
	{
		/** Archetype of the non-type template parameter. */
		Archetype const* archetype = nullptr;

		NonTypeTemplateParameter(std::string&&		name,
								 Archetype const*	archetype)	noexcept;
	};

	struct TemplateTemplateParameter : public TemplateParameter
	{
		std::vector<TemplateParameter> templateParameters;

		TemplateTemplateParameter(std::string&&	name) noexcept;

		/**
		*	@brief Add a template parameter to the list.
		* 
		*	@param templateParameter Template parameter to add.
		*/
		TemplateTemplateParameter& addTemplateParameter(TemplateParameter&& templateParameter) noexcept;
	};
}