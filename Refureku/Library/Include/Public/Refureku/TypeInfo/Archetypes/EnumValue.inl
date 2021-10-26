/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename T>
T EnumValue::getValue() const noexcept
{
	static_assert(std::is_integral_v<T> || std::is_enum_v<T>, "EnumValue::getValue<T> can only be called with integral / enum types.");

	return static_cast<T>(getValue());
}