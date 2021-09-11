/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>
#include <unordered_set>
#include <array>

#include "Refureku/TypeInfo/Archetypes/Class.h"
#include "Refureku/TypeInfo/Archetypes/ClassTemplateInstance.h"

namespace rfk
{
	//Forward declaration
	struct TemplateParameter;

	class ClassTemplate : public Class
	{
		public:
			/** List of all template parameters of this class template. */
			std::vector<TemplateParameter const*>				templateParameters;

			/** All instances of this class template in the program. */
			std::unordered_set<ClassTemplateInstance const*>	instances;

			ClassTemplate(std::string&&	name,
						  uint64		id,
						  bool			isClass)	noexcept;

			/**
			*	@brief Get the instance corresponding to the provided template arguments if it exists in the program.
			* 
			*	@return The instance if any, else nullptr.
			*/
			template <typename... Types>
			ClassTemplateInstance const* getInstance()															const	noexcept;

			/**
			*	@brief Get the instance corresponding to the provided template arguments if it exists in the program.
			* 
			*	@return The instance if any, else nullptr.
			*/
			template <size_t ArraySize>
			ClassTemplateInstance const* getInstance(std::array<Archetype const*, ArraySize> const& archetypes)	const	noexcept;	//TODO: Should be an array of TemplateArgument instead

			/**
			*	@brief Add a template parameter.
			* 
			*	@param templateParameter The template parameter to add.
			*/
			void addTemplateParameter(TemplateParameter const& templateParameter)	noexcept;

			/**
			*	@brief Register an instance generated from this class template.
			* 
			*	@param instance The instance to register.
			*/
			void registerClassTemplateInstance(ClassTemplateInstance& instance)		noexcept;
	};

	#include "Refureku/TypeInfo/Archetypes/ClassTemplate.inl"
}