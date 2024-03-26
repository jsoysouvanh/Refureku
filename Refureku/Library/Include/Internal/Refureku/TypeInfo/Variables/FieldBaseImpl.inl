/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline FieldBase::FieldBaseImpl::FieldBaseImpl(char const* name, std::size_t id, char const* canonicalTypeName, Type const& type, EFieldFlags flags, Struct const* owner, Entity const* outerEntity) noexcept:
	VariableBaseImpl(name, id, EEntityKind::Field, canonicalTypeName, type, outerEntity),
	_flags{flags},
	_owner{owner}
{
}

inline EFieldFlags FieldBase::FieldBaseImpl::getFlags() const noexcept
{
	return _flags;
}

inline Struct const* FieldBase::FieldBaseImpl::getOwner() const noexcept
{
	return _owner;
}