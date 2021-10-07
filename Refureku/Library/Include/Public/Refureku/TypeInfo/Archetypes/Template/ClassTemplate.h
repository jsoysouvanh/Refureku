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
	class TemplateParameter;
	class ClassTemplateInstantiation;

	class ClassTemplate final : public Struct
	{
		public:
			REFUREKU_API ClassTemplate(char const*	name,
									   std::size_t	id,
									   bool			isClass)	noexcept;
			REFUREKU_API ~ClassTemplate()						noexcept;

			/**
			*	@brief	Retrieve the template parameter at the given index.
			*			If index is greater or equal to getTemplateParametersCount(), the behaviour is undefined.
			* 
			*	@param index Index of the template parameter to retrieve.
			* 
			*	@return The template parameter at the given index.
			*/
			RFK_NODISCARD REFUREKU_API TemplateParameter const&	getTemplateParameterAt(std::size_t index)				const	noexcept;

			/**
			*	@brief Get the number of template parameters for this class template.
			*
			*	@return The number of template parameters for this class template.
			*/
			RFK_NODISCARD REFUREKU_API std::size_t				getTemplateParametersCount()							const	noexcept;

			/**
			*	@brief Execute the given visitor on all template instantiations of this class.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool									foreachTemplateInstantiation(/* TODO */)				const	noexcept;

			/**
			*	@brief Get the number of instantiations (with different template parameters) of this class template within the program.
			* 
			*	@return The number of instantiations of this class template within the program.
			*/
			RFK_NODISCARD REFUREKU_API std::size_t				getTemplateInstantiationsCount()						const	noexcept;

			/**
			*	@brief Append a template parameter the list of template parameters.
			* 
			*	//TODO
			*/
			REFUREKU_API void									addTemplateParameter(TemplateParameter const& param)			noexcept;

		private:
			//Forward declaration
			class ClassTemplateImpl;

		friend ClassTemplateInstantiation;
	};
}