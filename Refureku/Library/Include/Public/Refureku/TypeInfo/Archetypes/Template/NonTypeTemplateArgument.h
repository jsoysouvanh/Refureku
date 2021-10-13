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
	class NonTypeTemplateArgument : public TemplateArgument
	{
		public:
			REFUREKU_API NonTypeTemplateArgument(TemplateParameter const&	boundParameter, 
												 void const*				valuePtr)		noexcept;
			REFUREKU_API ~NonTypeTemplateArgument()											noexcept;

			/**
			*	@brief	Get the value of the non-type template argument.
			*			If the provided type is not the original type of the non-type template argument,
			*			the behaviour is undefined.
			* 
			*	@tparam Type of the non-type argument value.
			* 
			*	@return The argument value.
			*/
			template <typename T>
			RFK_NODISCARD T							getValue()		const	noexcept;

			/**
			*	@brief Get a pointer to the argument value.
			* 
			*	@return A pointer to the argument value.
			*/
			RFK_NODISCARD REFUREKU_API void const* getValuePtr()	const	noexcept;

			/**
			*	@brief Check whether 2 NonTypeTemplateArgument instances are equal or not.
			* 
			*	@param other The NonTypeTemplateArgument to compare to.
			* 
			*	@return true if the 2 type template arguments have the same archetype, and values.
			*			Returns false if the bound parameter archetype is nullptr, since the equality can't be guaranteed.
			*/
			RFK_NODISCARD REFUREKU_API bool	operator==(NonTypeTemplateArgument const& other)	const	noexcept;
			RFK_NODISCARD REFUREKU_API bool	operator!=(NonTypeTemplateArgument const& other)	const	noexcept;

		protected:
			//Forward declaration
			class NonTypeTemplateArgumentImpl;

			GEN_GET_PIMPL(NonTypeTemplateArgumentImpl, TemplateArgument::getPimpl())
	};

	#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateArgument.inl"
}