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
	class Type;

	class TypeTemplateArgument : public TemplateArgument
	{
		public:
			REFUREKU_API TypeTemplateArgument(Type const&	archetype)	noexcept;
			REFUREKU_API ~TypeTemplateArgument()						noexcept;

			/**
			*	@brief Get the type of this argument.
			* 
			*	@return The type of this argument.
			*/
			RFK_NODISCARD REFUREKU_API Type const& getType() const noexcept;

			/**
			*	@brief Check whether 2 TypeTemplateArgument instances are equal or not.
			* 
			*	@param other The TypeTemplateArgument to compare to.
			* 
			*	@return true if the 2 type template arguments have the same type, else false.
			*/
			RFK_NODISCARD REFUREKU_API bool	operator==(TypeTemplateArgument const& other)	const	noexcept;
			RFK_NODISCARD REFUREKU_API bool	operator!=(TypeTemplateArgument const& other)	const	noexcept;

		protected:
			//Forward declaration
			class TypeTemplateArgumentImpl;

			RFK_GEN_GET_PIMPL(TypeTemplateArgumentImpl, TemplateArgument::getPimpl())
	};
}