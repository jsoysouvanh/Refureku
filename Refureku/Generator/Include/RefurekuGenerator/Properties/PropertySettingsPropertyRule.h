/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "RefurekuGenerator/Properties/DefaultComplexPropertyRule.h"

namespace rfk
{
	class PropertySettingsPropertyRule : public DefaultComplexPropertyRule
	{
		protected:
			virtual std::string generatePrePropertyAddCode(kodgen::EntityInfo const&		entity,
														   kodgen::ComplexProperty const&	property,
														   PropertyCodeGenPropertyAddData&	data)		const noexcept override;

			virtual std::string generateClassFooterCode(kodgen::EntityInfo const&		entity,
														kodgen::ComplexProperty const&	property,
														PropertyCodeGenClassFooterData&	data)			const noexcept override;

		public:
			PropertySettingsPropertyRule()										noexcept;
			PropertySettingsPropertyRule(PropertySettingsPropertyRule const&)	= default;
			PropertySettingsPropertyRule(PropertySettingsPropertyRule&&)		= default;
			virtual ~PropertySettingsPropertyRule()								= default;
	};
}