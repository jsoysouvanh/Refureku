/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline bool FieldBase::isStatic() const noexcept
{
	return static_cast<std::underlying_type_t<EFieldFlags>>(flags & EFieldFlags::Static);
}

inline bool FieldBase::isMutable() const noexcept
{
	return static_cast<std::underlying_type_t<EFieldFlags>>(flags & EFieldFlags::Mutable);
}