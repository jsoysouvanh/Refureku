#include "TypeInfo/Type.h"

#include <cstring>

#include "TypeInfo/Archetypes/Archetype.h"

using namespace rfk;

bool Type::match(Type const& type) const noexcept
{
	return (*this == type) ||																	//Strictly the same type

			((isPointer() && type.archetype == &FundamentalArchetypes::getNullptrArchetype()) ||	//Pointer - nullptr_t correspondance
			(archetype == &FundamentalArchetypes::getNullptrArchetype() && type.isPointer()));
}

std::string Type::toString() const noexcept
{
	std::string result;

	if (archetype != nullptr)
	{
		result += "Archetype: " + archetype->name + "\n";
	}
	else
	{
		result += "Archetype: Unknown\n";
	}

	for (rfk::TypePart part : parts)
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

bool Type::operator==(Type const& type) const noexcept
{
	return	archetype == type.archetype &&
			parts.size() == type.parts.size() &&
			std::memcmp(parts.data(), type.parts.data(), parts.size() * sizeof(TypePart)) == 0;
}

bool Type::operator!=(Type const& type) const noexcept
{
	return !(*this == type);
}

std::ostream& rfk::operator<<(std::ostream& stream, Type const& type) noexcept
{
	stream << type.toString();

	return stream;
}