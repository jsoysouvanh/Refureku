/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Template/TemplateParameter.h"
#include "Refureku/Misc/Visitor.h"

namespace rfk
{
	class TemplateTemplateParameter final : public TemplateParameter
	{
		public:
			REFUREKU_API TemplateTemplateParameter(char const* name)	noexcept;
			REFUREKU_API ~TemplateTemplateParameter()					noexcept;

			/**
			*	@brief Get the number of template parameters of this template template parameter.
			* 
			*	@return The number of template parameters.
			*/
			RFK_NODISCARD REFUREKU_API std::size_t				getTemplateParametersCount()									const	noexcept;

			/**
			*	@brief	Get the template parameter at the specified index.
			*			If index is >= getTemplateParametersCount(), the behaviour is undefined.
			* 
			*	@param index Index of the template parameter to get.
			* 
			*	@return The template parameter at the specified index.
			*/
			RFK_NODISCARD REFUREKU_API TemplateParameter const*	getTemplateParameterAt(std::size_t index)						const	noexcept;

			/**
			*	@brief Execute the given visitor on all template parameters.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool									foreachTemplateParameter(Visitor<TemplateParameter> visitor,
																						 void*						userData)	const;

			/**
			*	@brief Add a template parameter to this template template parameter.
			* 
			*	@param param The template parameter to add.
			*/
			REFUREKU_API void									addTemplateParameter(TemplateParameter const& param)					noexcept;

		private:
			//Forward declaration
			class TemplateTemplateParameterImpl;

			RFK_GEN_GET_PIMPL(TemplateTemplateParameterImpl, TemplateParameter::getPimpl())
	};
}