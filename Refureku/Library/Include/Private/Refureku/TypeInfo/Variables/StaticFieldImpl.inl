/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/


inline StaticFieldAPI::StaticFieldImpl::StaticFieldImpl(char const* name, std::size_t id, TypeAPI const& type, EFieldFlags flags,
														StructAPI const* owner, void* dataPtr, EntityAPI const* outerEntity) noexcept:
	FieldBaseImpl(name, id, type, flags, owner, outerEntity),
	_dataPtr{dataPtr}
{
}

inline StaticFieldAPI::StaticFieldImpl::StaticFieldImpl(char const* name, std::size_t id, TypeAPI const& type, EFieldFlags flags,
														StructAPI const* owner, void const* constDataPtr, EntityAPI const* outerEntity) noexcept:
	FieldBaseImpl(name, id, type, flags, owner, outerEntity),
	_constDataPtr{constDataPtr}
{
}

inline void* StaticFieldAPI::StaticFieldImpl::getDataPtr() const noexcept
{
	return _dataPtr;
}

inline void const* StaticFieldAPI::StaticFieldImpl::getConstDataPtr() const noexcept
{
	return _constDataPtr;
}