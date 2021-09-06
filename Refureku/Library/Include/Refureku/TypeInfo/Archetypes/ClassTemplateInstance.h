/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <vector>

#include "Refureku/TypeInfo/Archetypes/Class.h"
#include "Refureku/TypeInfo/Archetypes/TemplateArgument.h"

namespace rfk
{
	//Forward declaration
	class ClassTemplate;

	class ClassTemplateInstance : public Class
	{
		public:
			/** Class template this instance comes from. */
			ClassTemplate const*			instantiatedFrom;

			/** List of all template arguments of this class template instance. */
			std::vector<TemplateArgument>	templateArguments;

			ClassTemplateInstance(std::string&&		name,
								  uint64			id,
								  uint64			memorySize,
								  bool				isClass,
								  Archetype const*	instantiatedFrom)	noexcept;

			/**
			*	TODO
			*/
			template <typename... Types>
			bool hasSameTemplateArguments() const noexcept
			{
				//TODO: Move in .inl file
				static std::array<Archetype const*, sizeof...(Types)> archetypes = { { rfk::getArchetype<Types>()... } };
				static bool computed = false;
				static bool result = false;

				if (!computed)
				{
					computed = true;

					if (templateArguments.size() == archetypes.size())
					{
						for (int i = 0; i < templateArguments.size(); i++)
						{
							if (archetypes[i] != templateArguments[i].archetype)
							{
								result = false;
								break;
							}
						}

						result = true;
					}
				}

				return result;
			}
	};
}