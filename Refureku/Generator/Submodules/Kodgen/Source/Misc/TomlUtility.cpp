#include "Kodgen/Misc/TomlUtility.h"

using namespace kodgen;

bool TomlUtility::updateSetting(toml::value const& table, std::string const& entryName, fs::path& out_toUpdateSetting, ILogger* logger) noexcept
{
	std::string foundSetting;

	if (TomlUtility::getValueFromTable<std::string>(table, entryName, foundSetting, logger))
	{
		out_toUpdateSetting = fs::path(foundSetting).make_preferred();

		return true;
	}

	return false;
}

bool TomlUtility::updateSetting(toml::value const& table, std::string const& entryName, char& out_toUpdateSetting, ILogger* logger) noexcept
{
	std::string foundSetting;

	if (TomlUtility::getValueFromTable<std::string>(table, entryName, foundSetting, logger))
	{
		if (foundSetting.size() == 1)
		{
			out_toUpdateSetting = foundSetting[0];

			return true;
		}
		else
		{
			logger->log("TOML " + entryName + " -> " + foundSetting + " is of incorrect type. Should be a single char.", ILogger::ELogSeverity::Error);
		}
	}

	return false;
}

bool TomlUtility::updateSetting(toml::value const& table, std::string const& entryName, std::unordered_set<std::string>& out_toUpdateSetting, ILogger* logger) noexcept
{
	std::vector<std::string> foundStringVector;

	if (TomlUtility::getValueFromTable<std::vector<std::string>>(table, entryName, foundStringVector, logger))
	{
		out_toUpdateSetting.insert(std::make_move_iterator(foundStringVector.begin()), std::make_move_iterator(foundStringVector.end()));

		return true;
	}

	return false;
}

bool TomlUtility::updateSetting(toml::value const& table, std::string const& entryName, std::unordered_set<fs::path, PathHash>& out_toUpdateSetting, ILogger* logger) noexcept
{
	std::vector<std::string> foundStringVector;

	if (TomlUtility::getValueFromTable<std::vector<std::string>>(table, entryName, foundStringVector, logger))
	{
		out_toUpdateSetting.insert(std::make_move_iterator(foundStringVector.begin()), std::make_move_iterator(foundStringVector.end()));

		return true;
	}

	return false;
}

bool TomlUtility::updateSetting(toml::value const& table, std::string const& entryName, std::unordered_set<char>& out_toUpdateSetting, ILogger* logger) noexcept
{
	std::vector<std::string> foundStringVector;

	if (TomlUtility::getValueFromTable<std::vector<std::string>>(table, entryName, foundStringVector, logger))
	{
		for (std::string value : foundStringVector)
		{
			if (value.size() == 1)
			{
				out_toUpdateSetting.emplace(value[0]);

				return true;
			}
			else
			{
				logger->log("TOML " + entryName + " -> " + value + " is of incorrect type. Should be a single char.", ILogger::ELogSeverity::Error);
			}
		}
	}

	return false;
}