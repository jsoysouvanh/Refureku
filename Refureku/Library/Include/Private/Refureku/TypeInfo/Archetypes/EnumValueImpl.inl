/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline EnumValue::EnumValueImpl::EnumValueImpl(char const* name, std::size_t id, int64 value, Entity const* outerEntity) noexcept:
	EntityImpl(name, id, EEntityKind::EnumValue, outerEntity),
	_value{value}
{
}

inline int64 EnumValue::EnumValueImpl::getValue() const noexcept
{
	return _value;
}