/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <vector>

#include "Refureku/TypeInfo/Archetypes/Template/TemplateTemplateParameter.h"
#include "Refureku/TypeInfo/Archetypes/Template/TemplateParameterImpl.h"

namespace rfk
{
	class TemplateTemplateParameter::TemplateTemplateParameterImpl final : public TemplateParameter::TemplateParameterImpl
	{
		private:
			/** Collection of all template parameters. */
			std::vector<TemplateParameter const*>	_templateParams;

		public:
			inline TemplateTemplateParameterImpl(char const* name)	noexcept;

			/**
			*	@brief Add a parameter to _templateParams.
			* 
			*	@param param Template parameter to add.
			*/
			inline void											addTemplateParameter(TemplateParameter const& param)	noexcept;

			/**
			*	@brief Getter for the field _templateParams.
			* 
			*	@return _templateParams.
			*/
			inline std::vector<TemplateParameter const*> const&	getTemplateParameters()							const	noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/Template/TemplateTemplateParameterImpl.inl"
}