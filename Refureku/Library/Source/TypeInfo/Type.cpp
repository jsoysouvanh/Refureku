#include "TypeInfo/Type.h"

#include <cstring>

using namespace rfk;

bool Type::operator==(Type const& type) const noexcept
{
	return	archetype == type.archetype &&
			parts.size() == type.parts.size() &&
			std::memcmp(parts.data(), type.parts.data(), parts.size() * sizeof(TypePart)) == 0;
}

std::ostream& rfk::operator<<(std::ostream& stream, Type const& type) noexcept
{
	if (type.archetype != nullptr)
	{
		std::cout << "Archetype: " << type.archetype->name << std::endl;
	}
	else
	{
		std::cout << "Archetype: Unknown" << std::endl;
	}

	for (rfk::TypePart part : type.parts)
	{
		stream << "\t- ";

		if (part.isConst())
		{
			stream << "Const ";
		}
		if (part.isVolatile())
		{
			stream << "Volatile ";
		}

		if (part.isValue())
		{
			stream << "Value";
		}
		else if (part.isPointer())
		{
			stream << "Ptr";
		}
		else if (part.isLValueReference())
		{
			stream << "LVRef";
		}
		else if (part.isRValueReference())
		{
			stream << "RVRef";
		}
		else if (part.isCArray())
		{
			stream << "CArray[" << part.getArraySize() << "]";
		}

		stream << std::endl;
	}

	return stream;
}