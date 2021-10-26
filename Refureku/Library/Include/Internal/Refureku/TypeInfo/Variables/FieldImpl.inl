/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline Field::FieldImpl::FieldImpl(char const* name, std::size_t id, Type const& type, EFieldFlags flags,
									  Struct const* owner, std::size_t memoryOffset, Entity const* outerEntity) noexcept:
	FieldBaseImpl(name, id, type, flags, owner, outerEntity),
	_memoryOffset{memoryOffset}
{
}

inline std::size_t Field::FieldImpl::getMemoryOffset() const noexcept
{
	return _memoryOffset;
}