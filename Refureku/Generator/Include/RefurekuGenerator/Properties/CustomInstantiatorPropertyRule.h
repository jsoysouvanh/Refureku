/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "RefurekuGenerator/Properties/DefaultSimplePropertyRule.h"

namespace rfk
{
	class CustomInstantiatorPropertyRule : public DefaultSimplePropertyRule
	{
		protected:
			virtual std::string generatePrePropertyAddCode(kodgen::EntityInfo const&		entity,
														   kodgen::Property const&			property,
														   PropertyCodeGenPropertyAddData&	data)		const noexcept override;

			virtual std::string generateClassFooterCode(kodgen::EntityInfo const&		entity,
														kodgen::Property const&			property,
														PropertyCodeGenClassFooterData&	data)			const noexcept override;

		public:
			CustomInstantiatorPropertyRule()										noexcept;
			CustomInstantiatorPropertyRule(CustomInstantiatorPropertyRule const&)	= default;
			CustomInstantiatorPropertyRule(CustomInstantiatorPropertyRule&&)		= default;
			virtual ~CustomInstantiatorPropertyRule()								= default;
	};
}