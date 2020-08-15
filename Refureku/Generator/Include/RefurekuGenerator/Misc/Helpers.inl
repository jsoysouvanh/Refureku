
constexpr kodgen::uint16 Helpers::convertToEntityKind(kodgen::EEntityType entityType) noexcept
{
	switch (entityType)
	{
		case kodgen::EEntityType::Namespace:
			return 1 << 0;

		case kodgen::EEntityType::Class:
			return 1 << 1;

		case kodgen::EEntityType::Struct:
			return 1 << 2;

		case kodgen::EEntityType::Enum:
			return 1 << 3;

		case kodgen::EEntityType::Variable:
			return 1 << 5;

		case kodgen::EEntityType::Field:
			return 1 << 6;

		case kodgen::EEntityType::Function:
			return 1 << 7;

		case kodgen::EEntityType::Method:
			return 1 << 8;

		case kodgen::EEntityType::EnumValue:
			return 1 << 9;

		case kodgen::EEntityType::Undefined:
			[[fallthrough]];
		default:
			assert(false);
	}

	return 0u;
}