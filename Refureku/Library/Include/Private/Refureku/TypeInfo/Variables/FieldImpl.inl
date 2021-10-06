/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline FieldAPI::FieldImpl::FieldImpl(char const* name, std::size_t id, TypeAPI const& type, EFieldFlags flags,
									  StructAPI const* owner, std::size_t memoryOffset, Entity const* outerEntity) noexcept:
	FieldBaseImpl(name, id, type, flags, owner, outerEntity),
	_memoryOffset{memoryOffset}
{
}

inline std::size_t FieldAPI::FieldImpl::getMemoryOffset() const noexcept
{
	return _memoryOffset;
}