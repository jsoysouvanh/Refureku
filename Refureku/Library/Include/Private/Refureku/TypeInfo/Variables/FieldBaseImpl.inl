/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline FieldBaseAPI::FieldBaseImpl::FieldBaseImpl(char const* name, std::size_t id, TypeAPI const& type, EFieldFlags flags, StructAPI const* owner, EntityAPI const* outerEntity) noexcept:
	VariableBaseImpl(name, id, EEntityKind::Field, type, outerEntity),
	_flags{flags},
	_owner{owner}
{
}

inline EFieldFlags FieldBaseAPI::FieldBaseImpl::getFlags() const noexcept
{
	return _flags;
}

inline StructAPI const* FieldBaseAPI::FieldBaseImpl::getOwner() const noexcept
{
	return _owner;
}