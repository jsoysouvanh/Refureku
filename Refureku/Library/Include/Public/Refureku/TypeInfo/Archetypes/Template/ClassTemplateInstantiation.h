/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Archetypes/Struct.h"

namespace rfk
{
	//Forward declarations
	class ClassTemplate;
	class TemplateArgument;
	class ClassTemplateInstantiation;

	/* A struct template instantiation and a class template instantiation contain exactly the same data. Alias for convenience. */
	using StructTemplateInstantiation = ClassTemplateInstantiation;

	class ClassTemplateInstantiation final : public Struct
	{
		public:
			REFUREKU_API ClassTemplateInstantiation(char const*			name,
													   std::size_t		id,
													   std::size_t		memorySize,
													   bool				isClass,
													   Archetype const&	classTemplate)	noexcept;
			REFUREKU_API ~ClassTemplateInstantiation()									noexcept;

			/**
			*	@brief Get the class template this instantiation is based on.
			* 
			*	@return The class template this instantiation is based on.
			*/
			RFK_NODISCARD REFUREKU_API ClassTemplate const&		getClassTemplate()											const	noexcept;

			/**
			*	@brief	Retrieve the template argument at the given index.
			*			If index is greater or equal to getTemplateArgumentsCount(), the behaviour is undefined.
			* 
			*	@param index Index of the template argument to retrieve.
			* 
			*	@return The template parameter at the given index.
			*/
			RFK_NODISCARD REFUREKU_API TemplateArgument const&	getTemplateArgumentAt(std::size_t index)					const	noexcept;

			/**
			*	@brief Get the total number of template arguments in this instantiation.
			* 
			*	@return The total number of template arguments in this instantiation..
			*/
			RFK_NODISCARD REFUREKU_API std::size_t				getTemplateArgumentsCount()									const	noexcept;

			/**
			*	@brief Execute the given visitor on all template arguments of this class.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_API bool									foreachTemplateArgument(Visitor<TemplateArgument> visitor,
																						void*					  userData)	const;

			/**
			*	@brief Add a template argument to this instantiation
			* 
			*	@param argument The template argument to add.
			*/
			REFUREKU_API void									addTemplateArgument(TemplateArgument const& argument)				noexcept;

		private:
			//Forward declaration
			class ClassTemplateInstantiationImpl;

			RFK_GEN_GET_PIMPL(ClassTemplateInstantiationImpl, Entity::getPimpl())
	};
}