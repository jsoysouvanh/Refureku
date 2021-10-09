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

		protected:
			//Forward declaration
			class NonTypeTemplateArgumentImpl;
	};

	#include "Refureku/TypeInfo/Archetypes/Template/NonTypeTemplateArgument.inl"
}