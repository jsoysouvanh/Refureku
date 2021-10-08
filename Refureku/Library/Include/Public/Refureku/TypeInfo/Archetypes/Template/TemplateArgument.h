/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/Utility/Pimpl.h"

namespace rfk
{
	//Forward declaration
	class TemplateParameter;

	class TemplateArgument
	{
		public:
			TemplateArgument(TemplateArgument const&)	= delete;
			TemplateArgument(TemplateArgument&&)		= delete;

			/**
			*	@brief Getter for the field _boundParameter.
			* 
			*	@return _boundParameter.
			*/
			RFK_NODISCARD REFUREKU_API TemplateParameter const&	getBoundParameter()	const	noexcept;

		protected:
			//Forward declaration
			class TemplateArgumentImpl;

			REFUREKU_INTERNAL TemplateArgument(TemplateArgumentImpl* implementation)	noexcept;
			REFUREKU_INTERNAL ~TemplateArgument()										noexcept;

			/**
			*	@brief Get the _pimpl internal pointer.
			* 
			*	@return The _pimpl internal pointer.
			*/
			RFK_NODISCARD REFUREKU_INTERNAL TemplateArgumentImpl*		getPimpl()			noexcept;
			RFK_NODISCARD REFUREKU_INTERNAL TemplateArgumentImpl const*	getPimpl()	const	noexcept;

			/** Pointer to the concrete TemplateParameter implementation. */
			Pimpl<TemplateArgumentImpl>	_pimpl;
	};
}