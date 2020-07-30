/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>

#include "Properties/DefaultComplexPropertyRule.h"
#include "Properties/ComplexPropertySubProperty.h"

namespace kodgen
{
	class FixedComplexPropertyRule : public DefaultComplexPropertyRule
	{
		protected:
			/** Vector of this property rule subproperties. */
			std::vector<ComplexPropertySubProperty>	subProperties;

			virtual std::string	getMacroDocumentation()	const noexcept override;

		public:
			FixedComplexPropertyRule()															= delete;
			FixedComplexPropertyRule(std::string							mainPropName,
									 std::unordered_set<EntityInfo::EType>	validEntityTypes,
									 std::string							description = "")	noexcept;
			FixedComplexPropertyRule(FixedComplexPropertyRule const&)							= default;
			FixedComplexPropertyRule(FixedComplexPropertyRule&&)								= default;
			virtual ~FixedComplexPropertyRule()													= default;

			virtual bool		isSubPropSyntaxValid(std::string const&	subProperty,
													 uint8					subPropIndex,
													 std::string&			out_errorDescription)			const noexcept override;

			virtual bool		isPropertyGroupValid(PropertyGroup const&	propertyGroup,
													 uint8					propertyIndex,
													 std::string&					out_errorDescription)	const noexcept override;

			virtual std::string	getMacroDefinition()														const noexcept override;
	};
}