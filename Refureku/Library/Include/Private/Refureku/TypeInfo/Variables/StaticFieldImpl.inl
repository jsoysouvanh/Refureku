/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/


inline StaticField::StaticFieldImpl::StaticFieldImpl(char const* name, std::size_t id, Type const& type, EFieldFlags flags,
														StructAPI const* owner, void* ptr, Entity const* outerEntity) noexcept:
	FieldBaseImpl(name, id, type, flags, owner, outerEntity),
	_ptr{ptr}
{
}

inline StaticField::StaticFieldImpl::StaticFieldImpl(char const* name, std::size_t id, Type const& type, EFieldFlags flags,
														StructAPI const* owner, void const* constPtr, Entity const* outerEntity) noexcept:
	FieldBaseImpl(name, id, type, flags, owner, outerEntity),
	_constPtr{constPtr}
{
}

inline void* StaticField::StaticFieldImpl::getPtr() const noexcept
{
	return _ptr;
}

inline void const* StaticField::StaticFieldImpl::getConstPtr() const noexcept
{
	return _constPtr;
}