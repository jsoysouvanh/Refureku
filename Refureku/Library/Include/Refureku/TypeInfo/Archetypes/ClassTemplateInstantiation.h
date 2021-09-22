/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <vector>
#include <array>

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/Archetypes/Class.h"
#include "Refureku/TypeInfo/Archetypes/TemplateArgument.h"

namespace rfk
{
	//Forward declaration
	class ClassTemplate;

	class ClassTemplateInstantiation : public Class
	{
		private:
			/** Class template this instance comes from. */
			ClassTemplate const&			_instantiatedFrom;

		public:
			/** List of all template arguments of this class template instance. */
			std::vector<TemplateArgument>	templateArguments;

			REFUREKU_API ClassTemplateInstantiation(std::string&&		name,
													std::size_t			id,
													std::size_t			memorySize,
													bool				isClass,
													Archetype const&	instantiatedFrom)	noexcept;

			/**
			*	@brief Check whether the instance arguments have the same types as the provided ones.
			* 
			*	@tparam The types to check.
			* 
			*	@return true if the provided types are the same as this instance's, else false.
			*/
			template <typename... Types>
			bool hasSameTemplateArguments()																const	noexcept;

			/**
			*	@brief Check whether the instance arguments have the same types as the provided ones.
			* 
			*	@tparam Size Number of provided archetypes.
			*	
			*	@param archetypes Archetypes to check.
			* 
			*	@return true if the provided types are the same as this instance's, else false.
			*/
			//TODO: Remove the std::array dependency
			template <size_t ArraySize>
			bool hasSameTemplateArguments(std::array<Archetype const*, ArraySize> const& archetypes)	const	noexcept;	//TODO: prototype must change to be able to check with non-type parameters

			/**
			*	@brief Add a template argument to this instantiation
			* 
			*	@param parameter The template parameter bounded to this argument.
			*	@param archetype The archetype of the template argument. //TODO: Change this to be able to store values as well
			*/
			REFUREKU_API void						addTemplateArgument(TemplateParameter const& parameter,
																		Archetype const*		 archetype)		noexcept;

			/**
			*	@brief Get the class template this instantiation comes from.
			* 
			*	@return The class template this instantiation comes from.
			*/
			REFUREKU_API ClassTemplate const&		getInstantiatedFrom()								const	noexcept;

			/**
			*	@brief Get the template argument at the provided index.
			* 
			*	@return The template argument at the provided index.
			*
			*	@exception std::out_of_range if the provided index is greater or equal to the number of template arguments.
			*/
			REFUREKU_API TemplateArgument const&	getTemplateArgument(std::size_t argIndex)			const;

			/**
			*	@brief Get the total number of template arguments in this instantiation.
			* 
			*	@return The total number of template arguments in this instantiation..
			*/
			REFUREKU_API std::size_t				getTemplateArgumentsCount()							const	noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/ClassTemplateInstantiation.inl"
}