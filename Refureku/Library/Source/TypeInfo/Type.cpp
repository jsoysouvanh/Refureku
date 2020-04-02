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
		switch (part.part)
		{
			stream << "\t- ";

			case rfk::ETypePart::Const:
				stream << "Const ";
				[[fallthrough]];
			case rfk::ETypePart::Volatile:
				stream << "Volatile ";
				[[fallthrough]];
			case rfk::ETypePart::Restrict:
				stream << "Restrict ";
				[[fallthrough]];
			case rfk::ETypePart::Value:
				stream << "Value";
				break;
			case rfk::ETypePart::Ptr:
				stream << "Ptr";
				break;
			case rfk::ETypePart::LRef:
				stream << "LRef";
				break;
			case rfk::ETypePart::RRef:
				stream << "RRef";
				break;
			case rfk::ETypePart::CArray:
				stream << "CArray " << part.additionalData;
				break;
		}

		stream << std::endl;
	}

	return stream;
}