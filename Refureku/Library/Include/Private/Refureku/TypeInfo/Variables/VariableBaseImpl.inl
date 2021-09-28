/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

VariableBaseAPI::VariableBaseImpl::VariableBaseImpl(char const* name, std::size_t id, EEntityKind kind, Type const& type, EntityAPI const* outerEntity) noexcept:
	EntityImpl(name, id, kind, outerEntity),
	_type{type}
{
}

inline Type const& VariableBaseAPI::VariableBaseImpl::getType() const noexcept
{
	return _type;
}