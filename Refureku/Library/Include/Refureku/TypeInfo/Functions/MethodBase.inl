/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline bool MethodBase::isStatic() const noexcept
{
	return static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::Static);
}

inline bool MethodBase::isInline() const noexcept
{
	return static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::Inline);
}

inline bool MethodBase::isVirtual() const noexcept
{
	return static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::Virtual);
}

inline bool MethodBase::isPureVirtual() const noexcept
{
	return static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::PureVirtual);
}

inline bool MethodBase::isOverride() const noexcept
{
	return static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::Override);
}

inline bool MethodBase::isFinal() const noexcept
{
	return static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::Final);
}

inline bool MethodBase::isConst() const noexcept
{
	return static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::Const);
}