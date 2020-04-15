#pragma once

#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

#include "Misc/Filesystem.h"
#include "Misc/Toml11.h"

namespace kodgen
{
	class TomlUtility
	{
		public:
			TomlUtility() = delete;
			~TomlUtility() = delete;

			template <typename T>
			static bool getValueFromTable(toml::value const& table, std::string const& entryName, T& out_value)		noexcept;

			template <typename T>
			static void updateSetting(toml::value const& table, std::string const& entryName, T& toUpdateSetting)	noexcept;
	};

	#include "Misc/TomlUtility.inl"
}