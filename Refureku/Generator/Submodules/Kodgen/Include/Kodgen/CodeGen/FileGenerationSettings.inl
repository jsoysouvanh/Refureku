/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline std::unordered_set<fs::path, PathHash> const& FileGenerationSettings::getToParseFiles() const noexcept
{
	return _toParseFiles;
}

inline std::unordered_set<fs::path, PathHash> const& FileGenerationSettings::getToParseDirectories() const noexcept
{
	return _toParseDirectories;
}

inline std::unordered_set<fs::path, PathHash> const& FileGenerationSettings::getIgnoredFiles() const noexcept
{
	return _ignoredFiles;
}

inline std::unordered_set<fs::path, PathHash> const& FileGenerationSettings::getIgnoredDirectories() const noexcept
{
	return _ignoredDirectories;
}