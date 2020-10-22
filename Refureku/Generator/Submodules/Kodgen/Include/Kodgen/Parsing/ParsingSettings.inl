/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline std::unordered_set<fs::path, PathHash> const& ParsingSettings::getProjectIncludeDirectories() const noexcept
{
	return _projectIncludeDirectories;
}

inline std::string const& ParsingSettings::getCompilerExeName() const noexcept
{
	return _compilerExeName;
}