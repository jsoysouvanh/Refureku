/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

namespace third_party_namespace
{
	namespace nested_third_party_namespace
	{
		void thirdPartyFunc();
	}

	enum class ThirdPartyEnum {};
}

#include <Refureku/TypeInfo/Archetypes/Enum.h>

namespace rfk
{
	template <>
	rfk::Enum const* getEnum<third_party_namespace::ThirdPartyEnum>() noexcept;
}