/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline VariableBase::VariableBaseImpl::VariableBaseImpl(char const* name, std::size_t id, EEntityKind kind, char const* canonicalTypeName, Type const& type, Entity const* outerEntity) noexcept:
	EntityImpl(name, id, kind, outerEntity),
	_type{type},
	_canonicalTypeName{canonicalTypeName}
{
}

inline Type const& VariableBase::VariableBaseImpl::getType() const noexcept
{
	return _type;
}

inline char const* VariableBase::VariableBaseImpl::getCanonicalTypeName() const noexcept
{
	return _canonicalTypeName.data();
}