/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Struct.h"

namespace rfk
{
	//Forward declarations
	class ClassTemplateAPI;
	class TemplateParameterAPI;
	class TemplateArgumentAPI;

	class ClassTemplateInstantiationAPI final : public Struct
	{
		public:
			REFUREKU_API ClassTemplateInstantiationAPI(char const*			name,
													   std::size_t			id,
													   std::size_t			memorySize,
													   bool					isClass,
													   Archetype const&	classTemplate)	noexcept;
			REFUREKU_API ~ClassTemplateInstantiationAPI()									noexcept;

			/**
			*	@brief Get the class template this instantiation is based on.
			* 
			*	@return The class template this instantiation is based on.
			*/
			RFK_NODISCARD REFUREKU_API ClassTemplateAPI const&		getClassTemplate()									const	noexcept;

			/**
			*	@brief	Retrieve the template argument at the given index.
			*			If index is greater or equal to getTemplateArgumentsCount(), the behaviour is undefined.
			* 
			*	@param index Index of the template argument to retrieve.
			* 
			*	@return The template parameter at the given index.
			*/
			RFK_NODISCARD REFUREKU_API TemplateArgumentAPI const&	getTemplateArgument(std::size_t index)				const	noexcept;

			/**
			*	@brief Get the total number of template arguments in this instantiation.
			* 
			*	@return The total number of template arguments in this instantiation..
			*/
			RFK_NODISCARD REFUREKU_API std::size_t					getTemplateArgumentsCount()							const	noexcept;

			/**
			*	@brief Add a template argument to this instantiation
			* 
			*	@param parameter The template parameter bounded to this argument.
			*	@param archetype The archetype of the template argument. //TODO: Change this to be able to store values as well
			*/
			REFUREKU_API void										addTemplateArgument(TemplateParameterAPI const&	parameter,
																						Archetype const*			archetype)	noexcept;

		private:
			//Forward declaration
			class ClassTemplateInstantiationImpl;
	};
}