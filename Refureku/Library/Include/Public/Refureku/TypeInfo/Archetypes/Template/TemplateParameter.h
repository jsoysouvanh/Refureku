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
#include "Refureku/TypeInfo/Archetypes/Template/ETemplateParameterKind.h"

namespace rfk
{
	class TemplateParameter
	{
		public:
			TemplateParameter(TemplateParameter const&)	= delete;
			TemplateParameter(TemplateParameter&&)		= delete;

			/**
			*	@brief Get the name of the template parameter.
			* 
			*	@return The name of the template parameter.
			*/
			RFK_NODISCARD REFUREKU_API char const*				getName()	const	noexcept;
			
			/**
			*	@brief	Get the kind of this template parameter.
			*			Depending on the kind, the template parameter can safely be
			*			cast to a more concrete type to retrieve more information about
			*			the parameter.
			* 
			*	@return The kind of this template parameter.
			*/
			RFK_NODISCARD REFUREKU_API ETemplateParameterKind	getKind()	const	noexcept;

		protected:
			//Forward declaration
			class TemplateParameterImpl;

			REFUREKU_INTERNAL TemplateParameter(TemplateParameterImpl* implementation)	noexcept;
			REFUREKU_INTERNAL ~TemplateParameter()										noexcept;

			RFK_GEN_GET_PIMPL(TemplateParameterImpl, _pimpl.get())

		private:
			/** Pointer to the TemplateParameter concrete implementation. */
			Pimpl<TemplateParameterImpl> _pimpl;
	};
}