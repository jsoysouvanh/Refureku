
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
bool TomlUtility::updateSetting(toml::value const& table, std::string const& entryName, T& out_toUpdateSetting, ILogger* logger) noexcept
{
	T foundSetting;

	if (TomlUtility::getValueFromTable<T>(table, entryName, foundSetting, logger))
	{
		out_toUpdateSetting = foundSetting;

		return true;
	}

	return false;
}