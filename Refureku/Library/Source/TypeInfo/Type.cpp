#include "Refureku/TypeInfo/Type.h"

#include <cstring>	//std::memcmp

using namespace rfk;

bool Type::match(Type const& other) const noexcept
{
	return	(this == &other) ||																	//Types have the same address, don't need any further check
			(*this == other) ||																	//Strictly the same type
			((isPointer() && other.getArchetype() == rfk::getArchetype<std::nullptr_t>()) ||	//Pointer - nullptr_t correspondance
			(getArchetype() == rfk::getArchetype<std::nullptr_t>() && other.isPointer()));
}

std::string Type::toString() const noexcept
{
	std::string result;

	if (getArchetype() != nullptr)
	{
		result += "Archetype: " + getArchetype()->getName() + "\n";
	}
	else
	{
		result += "Archetype: Unknown\n";
	}

	for (rfk::TypePart const& part : _parts)
	{
		result += "  - ";

		if (part.isConst())
		{
			result += "Const ";
		}
		if (part.isVolatile())
		{
			result += "Volatile ";
		}

		if (part.isValue())
		{
			result += "Value";
		}
		else if (part.isPointer())
		{
			result += "Ptr";
		}
		else if (part.isLValueReference())
		{
			result += "LVRef";
		}
		else if (part.isRValueReference())
		{
			result += "RVRef";
		}
		else if (part.isCArray())
		{
			result += "CArray[" + std::to_string(part.getArraySize()) + "]";
		}

		result += "\n";
	}

	return result;
}

Archetype const* Type::getArchetype() const noexcept
{
	return _archetype;
}

std::vector<TypePart>& Type::getParts() noexcept
{
	return _parts;
}

std::vector<TypePart> const& Type::getParts() const noexcept
{
	return _parts;
}

bool Type::operator==(Type const& type) const noexcept
{
	return	getArchetype() == type.getArchetype() &&
			_parts.size() == type._parts.size() &&
			std::memcmp(_parts.data(), type._parts.data(), _parts.size() * sizeof(TypePart)) == 0;
}

bool Type::operator!=(Type const& type) const noexcept
{
	return !(*this == type);
}