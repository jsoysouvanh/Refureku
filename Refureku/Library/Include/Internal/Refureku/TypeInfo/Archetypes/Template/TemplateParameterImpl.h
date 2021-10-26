/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <string>

#include "Refureku/TypeInfo/Archetypes/Template/TemplateParameter.h"

namespace rfk
{
	class TemplateParameter::TemplateParameterImpl
	{
		private:
			/** Name of the template parameter. */
			std::string				_name;

			/** Kind of template parameter. */
			ETemplateParameterKind	_kind;

		public:
			inline TemplateParameterImpl(char const*			name,
										 ETemplateParameterKind	kind)	noexcept;
			virtual ~TemplateParameterImpl()							= default;

			/**
			*	@brief Getter for the field _name.
			* 
			*	@return _name.
			*/
			RFK_NODISCARD inline std::string const&		getName()	const	noexcept;

			/**
			*	@brief Getter for the field _kind.
			* 
			*	@return _kind.
			*/
			RFK_NODISCARD inline ETemplateParameterKind	getKind()	const	noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/Template/TemplateParameterImpl.inl"
}