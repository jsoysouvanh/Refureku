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
#include "Refureku/TypeInfo/Archetypes/TemplateParameter.h"

namespace rfk
{
	//Forward declaration
	class ClassTemplateInstance;

	class ClassTemplate : public Class
	{
		public:
			/** List of all template parameters of this class template. */
			std::vector<TemplateParameter>						templateParameters;

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
			ClassTemplateInstance const* getInstance()	const	noexcept
			{
				//TODO: Move this to .inl file
				static bool computed = false;
				static ClassTemplateInstance const* result = nullptr;

				if (!computed)
				{
					computed = true;

					for (ClassTemplateInstance const* instance : instances)
					{
						if (instance->hasSameTemplateArguments<Types...>())
						{
							result = instance;
							break;
						}
					}
				}

				return result;
			}

			/**
			*	@brief Add a template parameter.
			* 
			*	@param templateParameter The template parameter to add.
			*/
			void addTemplateParameter(TemplateParameter&& templateParameter)	noexcept;

			/**
			*	@brief Register an instance generated from this class template.
			* 
			*	@param instance The instance to register.
			*/
			void registerClassTemplateInstance(ClassTemplateInstance& instance)	noexcept;
	};
}