/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <Kodgen/Properties/DefaultComplexPropertyRule.h>

namespace rfk
{
	class PropertySettingsPropertyRule : public kodgen::DefaultComplexPropertyRule
	{
		public:
			PropertySettingsPropertyRule()										noexcept;
			PropertySettingsPropertyRule(PropertySettingsPropertyRule const&)	= default;
			PropertySettingsPropertyRule(PropertySettingsPropertyRule&&)		= default;
			virtual ~PropertySettingsPropertyRule()								= default;

			virtual std::string	generateCode(kodgen::EntityInfo const&	entity,
											 kodgen::Property const&	property,
											 void*						userData)	const noexcept override;
	};
}