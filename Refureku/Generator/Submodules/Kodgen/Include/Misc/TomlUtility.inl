
template <typename T>
bool TomlUtility::getValueFromTable(toml::value const& table, std::string const& entryName, T& out_value) noexcept
{
	if (table.contains(entryName))
	{
		try
		{
			out_value = toml::find<T>(table, entryName);
			return true;
		}
		catch (toml::type_error const& e)
		{
			std::cerr << entryName << " value is of incorrect type." << std::endl
				<< e.what() << std::endl;
		}
	}

	return false;
}

template <typename T>
void TomlUtility::updateSetting(toml::value const& table, std::string const& entryName, T& toUpdateSetting) noexcept
{
	T foundSetting;

	if (TomlUtility::getValueFromTable<T>(table, entryName, foundSetting))
	{
		toUpdateSetting = foundSetting;
	}
}

template <>
inline void TomlUtility::updateSetting<fs::path>(toml::value const& table, std::string const& entryName, fs::path& toUpdateSetting) noexcept
{
	std::string foundSetting;

	if (TomlUtility::getValueFromTable<std::string>(table, entryName, foundSetting))
	{
		toUpdateSetting = fs::path(foundSetting).make_preferred().string();
	}
}

template <>
inline void TomlUtility::updateSetting<char>(toml::value const& table, std::string const& entryName, char& toUpdateSetting) noexcept
{
	std::string foundSetting;

	if (TomlUtility::getValueFromTable<std::string>(table, entryName, foundSetting))
	{
		if (foundSetting.size() == 1)
		{
			toUpdateSetting = foundSetting[0];
		}
		else
		{
			std::cerr << foundSetting << " is of incorrect type, should be a char." << std::endl;
		}
	}
}

template <>
inline void TomlUtility::updateSetting<std::unordered_set<std::string>>(toml::value const& table, std::string const& entryName, std::unordered_set<std::string>& toUpdateUS) noexcept
{
	std::vector<std::string> foundStringVector;

	if (TomlUtility::getValueFromTable<std::vector<std::string>>(table, entryName, foundStringVector))
	{
		for (std::string value : foundStringVector)
		{
			toUpdateUS.emplace(std::move(value));
		}
	}
}

template <>
inline void TomlUtility::updateSetting<std::unordered_set<fs::path, PathHash>>(toml::value const& table, std::string const& entryName, std::unordered_set<fs::path, PathHash>& toUpdateUS) noexcept
{
	std::vector<std::string> foundStringVector;

	if (TomlUtility::getValueFromTable<std::vector<std::string>>(table, entryName, foundStringVector))
	{
		for (std::string value : foundStringVector)
		{
			toUpdateUS.emplace(fs::path(value).make_preferred());
		}
	}
}

template <>
inline void TomlUtility::updateSetting<std::unordered_set<char>>(toml::value const& table, std::string const& entryName, std::unordered_set<char>& toUpdateUS) noexcept
{
	std::vector<std::string> foundStringVector;

	if (TomlUtility::getValueFromTable<std::vector<std::string>>(table, entryName, foundStringVector))
	{
		for (std::string value : foundStringVector)
		{
			if (value.size() == 1)
			{
				toUpdateUS.emplace(value[0]);
			}
			else
			{
				std::cerr << entryName << "." << value << " is of incorrect type, should be a char." << std::endl;
			}
		}
	}
}