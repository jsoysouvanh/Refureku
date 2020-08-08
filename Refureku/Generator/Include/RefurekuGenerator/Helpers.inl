
constexpr kodgen::uint8 Helpers::convertToEntityKind(kodgen::EEntityType entityType) noexcept
{
	switch (entityType)
	{
		case kodgen::EEntityType::Namespace:
			return 1 << 0;

		case kodgen::EEntityType::Class:
			[[fallthrough]];
		case kodgen::EEntityType::Struct:
			[[fallthrough]];
		case kodgen::EEntityType::Enum:
			return 1 << 1;

		case kodgen::EEntityType::Field:
			return 1 << 2;

		case kodgen::EEntityType::Method:
			return 1 << 3;

		case kodgen::EEntityType::EnumValue:
			return 1 << 4;

		case kodgen::EEntityType::Undefined:
			[[fallthrough]];
		default:
			assert(false);
	}

	return 0u;
}

constexpr kodgen::uint8 Helpers::convertToArchetypeCategory(kodgen::EEntityType entityType) noexcept
{
	switch (entityType)
	{
		case kodgen::EEntityType::Class:
			return 1 << 0;

		case kodgen::EEntityType::Struct:
			return 1 << 1;
		
		case kodgen::EEntityType::Enum:
			return 1 << 2;

		default:
			assert(false);
	}

	return 0u;
}