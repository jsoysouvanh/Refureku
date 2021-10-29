/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <cassert>
#include <vector>

#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiation.h"
#include "Refureku/TypeInfo/Archetypes/StructImpl.h"
#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplate.h"

namespace rfk
{
	class ClassTemplateInstantiation::ClassTemplateInstantiationImpl final : public Struct::StructImpl
	{
		private:
			/** Class template this instance comes from. */
			ClassTemplate const&					_classTemplate;

			/** List of all template arguments of this class template instance. */
			std::vector<TemplateArgument const*>	_templateArguments;

		public:
			inline ClassTemplateInstantiationImpl(char const*		name,
												  std::size_t		id,
												  std::size_t		memorySize,
												  bool				isClass,
												  Archetype const&	classTemplate)	noexcept;

			/**
			*	@brief Add an argument to the list of template arguments.
			* 
			*	@param arg The template argument to add to this instantiation.
			*/
			inline void															addTemplateArgument(TemplateArgument const& arg)	noexcept;

			/**
			*	@brief Getter for the field _classTemplate.
			* 
			*	@return _classTemplate.
			*/
			RFK_NODISCARD inline ClassTemplate const&							getClassTemplate()							const	noexcept;

			/**
			*	@brief Getter for the field _templateArguments.
			* 
			*	@return _templateArguments.
			*/
			RFK_NODISCARD inline std::vector<TemplateArgument const*> const&	getTemplateArguments()						const	noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationImpl.inl"
}