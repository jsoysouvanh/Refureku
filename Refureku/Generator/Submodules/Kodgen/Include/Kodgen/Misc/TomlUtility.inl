
template <typename T>
bool TomlUtility::getValueFromTable(toml::value const& table, std::string const& entryName, T& out_value, ILogger* logger) noexcept
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
			if (logger != nullptr)
			{
				logger->log("TOML " + entryName + " value is of incorrect type. " + e.what(), ILogger::ELogSeverity::Error);
			}
		}
	}

	return false;
}

template <typename T>
void TomlUtility::updateSetting(toml::value const& table, std::string const& entryName, T& out_toUpdateSetting, ILogger* logger) noexcept
{
	T foundSetting;

	if (TomlUtility::getValueFromTable<T>(table, entryName, foundSetting, logger))
	{
		out_toUpdateSetting = foundSetting;
	}
}

template <>
inline void TomlUtility::updateSetting<fs::path>(toml::value const& table, std::string const& entryName, fs::path& out_toUpdateSetting, ILogger* logger) noexcept
{
	std::string foundSetting;

	if (TomlUtility::getValueFromTable<std::string>(table, entryName, foundSetting, logger))
	{
		out_toUpdateSetting = fs::path(foundSetting).make_preferred();
	}
}

template <>
inline void TomlUtility::updateSetting<char>(toml::value const& table, std::string const& entryName, char& out_toUpdateSetting, ILogger* logger) noexcept
{
	std::string foundSetting;

	if (TomlUtility::getValueFromTable<std::string>(table, entryName, foundSetting, logger))
	{
		if (foundSetting.size() == 1)
		{
			out_toUpdateSetting = foundSetting[0];
		}
		else
		{
			logger->log("TOML " + entryName + " -> " + foundSetting + " is of incorrect type. Should be a single char.", ILogger::ELogSeverity::Error);
		}
	}
}

template <>
inline void TomlUtility::updateSetting<std::unordered_set<std::string>>(toml::value const& table, std::string const& entryName, std::unordered_set<std::string>& out_toUpdateSetting, ILogger* logger) noexcept
{
	std::vector<std::string> foundStringVector;

	if (TomlUtility::getValueFromTable<std::vector<std::string>>(table, entryName, foundStringVector, logger))
	{
		out_toUpdateSetting.insert(std::make_move_iterator(foundStringVector.begin()), std::make_move_iterator(foundStringVector.end()));
	}
}

template <>
inline void TomlUtility::updateSetting<std::unordered_set<fs::path, PathHash>>(toml::value const& table, std::string const& entryName, std::unordered_set<fs::path, PathHash>& out_toUpdateSetting, ILogger* logger) noexcept
{
	std::vector<std::string> foundStringVector;

	if (TomlUtility::getValueFromTable<std::vector<std::string>>(table, entryName, foundStringVector, logger))
	{
		for (std::string value : foundStringVector)
		{
			out_toUpdateSetting.emplace(fs::path(value).make_preferred());
		}
	}
}

template <>
inline void TomlUtility::updateSetting<std::unordered_set<char>>(toml::value const& table, std::string const& entryName, std::unordered_set<char>& out_toUpdateSetting, ILogger* logger) noexcept
{
	std::vector<std::string> foundStringVector;

	if (TomlUtility::getValueFromTable<std::vector<std::string>>(table, entryName, foundStringVector, logger))
	{
		for (std::string value : foundStringVector)
		{
			if (value.size() == 1)
			{
				out_toUpdateSetting.emplace(value[0]);
			}
			else
			{
				logger->log("TOML " + entryName + " -> " + value + " is of incorrect type. Should be a single char.", ILogger::ELogSeverity::Error);
			}
		}
	}
}