/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
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
			REFUREKU_API TemplateTemplateArgument(ClassTemplate const* value)	noexcept;
			REFUREKU_API ~TemplateTemplateArgument()							noexcept;

			/**
			*	@brief	Get the class template provided as argument.
			*			It can be nullptr if the class template is not a reflected type.
			* 
			*	@return The class template provided as argument.
			*/
			RFK_NODISCARD REFUREKU_API ClassTemplate const*	getClassTemplate()	const	noexcept;

			/**
			*	@brief Check whether 2 TemplateTemplateArgument instances are equal or not.
			* 
			*	@param other The TemplateTemplateArgument to compare to.
			* 
			*	@return true if the 2 type template arguments have the same class template.
			*			Returns false if the class template archetype is nullptr, since the equality can't be guaranteed.
			*/
			RFK_NODISCARD REFUREKU_API bool	operator==(TemplateTemplateArgument const& other)	const	noexcept;
			RFK_NODISCARD REFUREKU_API bool	operator!=(TemplateTemplateArgument const& other)	const	noexcept;

		protected:
			//Forward declaration
			class TemplateTemplateArgumentImpl;

			RFK_GEN_GET_PIMPL(TemplateTemplateArgumentImpl, TemplateArgument::getPimpl())
	};
}