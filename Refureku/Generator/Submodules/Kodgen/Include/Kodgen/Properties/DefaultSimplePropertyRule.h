/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <unordered_set>

#include "Kodgen/Properties/SimplePropertyRule.h"

namespace kodgen
{
	class DefaultSimplePropertyRule : public SimplePropertyRule
	{
		private:
			/** Description of this property rule. */
			std::string	_description;

		protected:
			/** Name the property should have to be considered valid. */
			std::string	mainPropName;

			/** EEntityType bitmask defining valid entities (bit it set for valid entities). */
			EEntityType	validEntityTypes;

			virtual std::string	getMacroDocumentation()	const noexcept override;

		public:
			DefaultSimplePropertyRule()									= delete;
			DefaultSimplePropertyRule(std::string	mainPropName,
									  EEntityType	validEntityTypes,
									  std::string	description = "")	noexcept;
			DefaultSimplePropertyRule(DefaultSimplePropertyRule const&)	= default;
			DefaultSimplePropertyRule(DefaultSimplePropertyRule&&)		= default;
			virtual ~DefaultSimplePropertyRule()						= default;

			virtual bool		isMainPropSyntaxValid(std::string const&	mainProperty,
													  EEntityType			entityType)	const noexcept override;

			virtual std::string	getMacroDefinition()									const noexcept override;
	};
}