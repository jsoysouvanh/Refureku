/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/


inline StaticFieldAPI::StaticFieldImpl::StaticFieldImpl(char const* name, std::size_t id, TypeAPI const& type, EFieldFlags flags,
														StructAPI const* owner, void* ptr, EntityAPI const* outerEntity) noexcept:
	FieldBaseImpl(name, id, type, flags, owner, outerEntity),
	_ptr{ptr}
{
}

inline StaticFieldAPI::StaticFieldImpl::StaticFieldImpl(char const* name, std::size_t id, TypeAPI const& type, EFieldFlags flags,
														StructAPI const* owner, void const* constPtr, EntityAPI const* outerEntity) noexcept:
	FieldBaseImpl(name, id, type, flags, owner, outerEntity),
	_constPtr{constPtr}
{
}

inline void* StaticFieldAPI::StaticFieldImpl::getPtr() const noexcept
{
	return _ptr;
}

inline void const* StaticFieldAPI::StaticFieldImpl::getConstPtr() const noexcept
{
	return _constPtr;
}