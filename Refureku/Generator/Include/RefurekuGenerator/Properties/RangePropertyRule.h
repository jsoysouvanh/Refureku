/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <Kodgen/Properties/FixedComplexPropertyRule.h>

namespace rfk
{
	class RangePropertyRule : public kodgen::FixedComplexPropertyRule
	{
		public:
			RangePropertyRule()							noexcept;
			RangePropertyRule(RangePropertyRule const&) = default;
			RangePropertyRule(RangePropertyRule&&)		= default;
			virtual ~RangePropertyRule()				= default;

			virtual bool isPropertyGroupValid(kodgen::PropertyGroup const&	propertyGroup,
											  kodgen::uint8					propertyIndex,
											  std::string&					out_errorDescription)	const noexcept override;

			virtual bool isEntityValid(kodgen::EntityInfo const&	entity,
									   kodgen::uint8				propertyIndex,
									   std::string&					out_errorDescription)			const noexcept override;
	};
}