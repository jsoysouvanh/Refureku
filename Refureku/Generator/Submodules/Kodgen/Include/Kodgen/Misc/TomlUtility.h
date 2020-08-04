/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

#include "Kodgen/Misc/Filesystem.h"
#include "Kodgen/Misc/Toml11.h"

namespace kodgen
{
	class TomlUtility
	{
		public:
			/** Static class, disallow construction. */
			TomlUtility()	= delete;
			~TomlUtility()	= delete;

			/**
			*	@brief Retrieve a value from a toml table if possible.
			*
			*	@tparam T Type of the value to retrieve from the toml file.
			*
			*	@param table		Toml file we look into.
			*	@param entryName	Name of the value we are looking for.
			*	@param out_value	Value which should contain the result on success.
			*
			*	@return true if the specified value was found and consequently out_value updated, else false.
			*/
			template <typename T>
			static bool getValueFromTable(toml::value const&	table,
										  std::string const&	entryName,
										  T&					out_value)			noexcept;

			/**
			*	@brief Retrieve a value from a toml table if possible.
			*
			*	@note This is only a wrapper method around TomlUtility::getValueFromTable() to allow better control with template specialization.
			*	
			*	@tparam T Type of the value to retrieve from the toml file.
			*
			*	@param table				Toml file we look into.
			*	@param entryName			Name of the value we are looking for.
			*	@param out_toUpdateSetting	Value which should contain the result on success.
			*
			*	@return true if the specified value was found and consequently out_value updated, else false.
			*/
			template <typename T>
			static void updateSetting(toml::value const&	table,
									  std::string const&	entryName,
									  T&					out_toUpdateSetting)	noexcept;
	};

	#include "Kodgen/Misc/TomlUtility.inl"
}