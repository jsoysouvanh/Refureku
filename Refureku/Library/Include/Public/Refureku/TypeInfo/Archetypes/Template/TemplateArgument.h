/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/Misc/Pimpl.h"
#include "Refureku/Misc/GetPimplMacro.h"

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
			RFK_NODISCARD REFUREKU_API TemplateParameter const&	getBoundParameter()		const	noexcept;

			/**
			*	@brief Check whether 2 TemplateArgument instances are equal or not.
			* 
			*	@param other The TemplateArgument to compare to.
			* 
			*	@return true if the 2 template arguments hold the same value, else false.
			*/
			RFK_NODISCARD REFUREKU_API bool	operator==(TemplateArgument const& other)	const	noexcept;
			RFK_NODISCARD REFUREKU_API bool	operator!=(TemplateArgument const& other)	const	noexcept;

		protected:
			//Forward declaration
			class TemplateArgumentImpl;

			REFUREKU_INTERNAL TemplateArgument(TemplateArgumentImpl* implementation)	noexcept;
			REFUREKU_INTERNAL ~TemplateArgument()										noexcept;

			GEN_GET_PIMPL(TemplateArgumentImpl, _pimpl.get())

		private:
			/** Pointer to the concrete TemplateParameter implementation. */
			Pimpl<TemplateArgumentImpl>	_pimpl;
	};
}