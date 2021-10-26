/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/Config.h"
#include "Refureku/Misc/Pimpl.h"
#include "Refureku/Misc/GetPimplMacro.h"

namespace rfk
{
	enum class ETemplateParameterKind;

	class TemplateArgument
	{
		public:
			TemplateArgument(TemplateArgument const&)	= delete;
			TemplateArgument(TemplateArgument&&)		= delete;

			/**
			*	@brief Get the kind of template parameter this argument is based on.
			* 
			*	@return The kind of template parameter this argument is based on.
			*/
			RFK_NODISCARD REFUREKU_API ETemplateParameterKind	getKind()	const	noexcept;

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

			RFK_GEN_GET_PIMPL(TemplateArgumentImpl, _pimpl.get())

		private:
			/** Pointer to the concrete TemplateParameter implementation. */
			Pimpl<TemplateArgumentImpl>	_pimpl;
	};
}