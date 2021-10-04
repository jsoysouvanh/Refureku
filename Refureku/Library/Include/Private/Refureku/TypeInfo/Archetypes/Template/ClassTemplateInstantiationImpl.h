/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <cassert>
#include <vector>

#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationAPI.h"
#include "Refureku/TypeInfo/Archetypes/StructImpl.h"
#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateAPI.h"
#include "Refureku/TypeInfo/Archetypes/Template/TemplateArgumentAPI.h"

namespace rfk
{
	class ClassTemplateInstantiationAPI::ClassTemplateInstantiationImpl final : public StructAPI::StructImpl
	{
		private:
			/** Class template this instance comes from. */
			ClassTemplateAPI const&				_classTemplate;

			/** List of all template arguments of this class template instance. */
			std::vector<TemplateArgumentAPI>	_templateArguments;

		public:
			inline ClassTemplateInstantiationImpl(char const*			name,
												  std::size_t			id,
												  std::size_t			memorySize,
												  bool					isClass,
												  ArchetypeAPI const&	classTemplate)	noexcept;

			/**
			*	@brief Getter for the field _classTemplate.
			* 
			*	@return _classTemplate.
			*/
			RFK_NODISCARD inline ClassTemplateAPI const&					getClassTemplate()		const	noexcept;

			/**
			*	@brief Getter for the field _templateArguments.
			* 
			*	@return _templateArguments.
			*/
			RFK_NODISCARD inline std::vector<TemplateArgumentAPI> const&	getTemplateArguments()	const	noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/Template/ClassTemplateInstantiationImpl.inl"
}