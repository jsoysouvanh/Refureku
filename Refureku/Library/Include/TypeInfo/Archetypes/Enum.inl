
inline EnumValue const* Enum::getEnumValue(std::string enumValueName)  const noexcept
{
	decltype(values)::const_iterator it = values.find(EnumValue(std::move(enumValueName)));

	return (it != values.cend()) ? &*it : nullptr;
}

inline EnumValue const* Enum::getEnumValue(int64 value) const noexcept
{
	decltype(values)::const_iterator it = std::find_if(values.cbegin(), values.cend(), [value](EnumValue const& v)
													   { return v.value == value; });

	return (it != values.cend()) ? &*it : nullptr;
}

inline std::vector<EnumValue const*> Enum::getEnumValues(int64 value) const noexcept
{
	std::vector<EnumValue const*> result;

	for (EnumValue const& ev : values)
	{
		if (ev.value == value)
		{
			result.push_back(&ev);
		}
	}

	return result;
}