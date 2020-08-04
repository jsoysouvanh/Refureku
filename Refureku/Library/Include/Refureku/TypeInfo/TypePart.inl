/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline bool TypePart::isPointer() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(descriptor & ETypePartDescriptor::Ptr) != 0u;
}

inline bool TypePart::isLValueReference() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(descriptor & ETypePartDescriptor::LRef) != 0u;
}

inline bool TypePart::isRValueReference() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(descriptor & ETypePartDescriptor::RRef) != 0u;
}

inline bool TypePart::isCArray() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(descriptor & ETypePartDescriptor::CArray) != 0u;
}

inline bool TypePart::isValue() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(descriptor & ETypePartDescriptor::Value) != 0u;
}

inline bool TypePart::isConst() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(descriptor & ETypePartDescriptor::Const) != 0u;
}

inline bool TypePart::isVolatile() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(descriptor & ETypePartDescriptor::Volatile) != 0u;
}

inline uint32 TypePart::getArraySize() const noexcept
{
	return (isCArray()) ? additionalData : 0u;
}