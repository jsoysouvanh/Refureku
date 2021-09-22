/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename Predicate, typename>
EnumValue const* Enum::getEnumValue(Predicate predicate) const noexcept
{
	for (std::size_t i = 0; i < getEnumValuesCount(); i++)
	{
		EnumValue const& enumValue = getEnumValueAt(i);

		if (predicate(enumValue))
		{
			return &enumValue;
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
std::vector<EnumValue const*> Enum::getEnumValues(Predicate predicate) const noexcept
{
	std::vector<EnumValue const*> result;

	for (std::size_t i = 0; i < getEnumValuesCount(); i++)
	{
		EnumValue const& enumValue = getEnumValueAt(i);

		if (predicate(enumValue))
		{
			result.push_back(&enumValue);
		}
	}

	return result;
}

template <typename T, typename>
rfk::Enum const* getEnum() noexcept
{
	return nullptr;
}