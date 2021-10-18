/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgument.h"

namespace rfk
{
	//Forward declaration
	class Archetype;

	class TypeTemplateArgument : public TemplateArgument
	{
		public:
			REFUREKU_API TypeTemplateArgument(Archetype const*	archetype)	noexcept;
			REFUREKU_API ~TypeTemplateArgument()							noexcept;

			/**
			*	@brief Get the archetype of this argument. Can be nullptr if the type is not reflected.
			* 
			*	@return The archetype of this argument.
			*/
			RFK_NODISCARD REFUREKU_API Archetype const* getArchetype() const noexcept;

			/**
			*	@brief Check whether 2 TypeTemplateArgument instances are equal or not.
			* 
			*	@param other The TypeTemplateArgument to compare to.
			* 
			*	@return true if the 2 type template arguments have the same archetype, else false.
			*			Returns false if the archetype is nullptr, since the equality can't be guaranteed.
			*/
			RFK_NODISCARD REFUREKU_API bool	operator==(TypeTemplateArgument const& other)	const	noexcept;
			RFK_NODISCARD REFUREKU_API bool	operator!=(TypeTemplateArgument const& other)	const	noexcept;

		protected:
			//Forward declaration
			class TypeTemplateArgumentImpl;

			RFK_GEN_GET_PIMPL(TypeTemplateArgumentImpl, TemplateArgument::getPimpl())
	};
}