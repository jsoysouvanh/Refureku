/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <vector>

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/Archetypes/ETemplateParameterKind.h"
#include "Refureku/TypeInfo/Archetypes/Archetype.h"

namespace rfk
{
	class TemplateParameter
	{
		private:
			/** Name of the template parameter. */
			std::string				_name;

			/** Kind of template parameter. */
			ETemplateParameterKind	_kind;

		public:
			REFUREKU_API TemplateParameter(std::string&&			name,
										   ETemplateParameterKind	kind)	noexcept;

			/**
			*	@brief Getter for the field _name.
			* 
			*	@return _name.
			*/
			REFUREKU_API std::string const&		getName()			const	noexcept;

			/**
			*	@brief Getter for the field _kind.
			* 
			*	@return _kind.
			*/
			REFUREKU_API ETemplateParameterKind	getKind()			const	noexcept;
	};

	class TypeTemplateParameter : public TemplateParameter
	{
		public:
			REFUREKU_API TypeTemplateParameter(std::string&& name) noexcept;
	};

	class NonTypeTemplateParameter : public TemplateParameter
	{
		public:
			/** Archetype of the non-type template parameter. */
			Archetype const* archetype = nullptr;

			REFUREKU_API NonTypeTemplateParameter(std::string&&		name,
												  Archetype const*	archetype)	noexcept;
	};

	class TemplateTemplateParameter : public TemplateParameter
	{
		public:
			/** List of template parameters. */
			std::vector<TemplateParameter> templateParameters;

			REFUREKU_API TemplateTemplateParameter(std::string&& name) noexcept;

			/**
			*	@brief Add a template parameter to the list.
			* 
			*	@param templateParameter Template parameter to add.
			*/
			REFUREKU_API TemplateTemplateParameter& addTemplateParameter(TemplateParameter&& templateParameter) noexcept;
	};
}