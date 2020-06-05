/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline bool PropertyGroup::hasProperty(std::string const& prop) const noexcept
{
	return simpleProperties.find(prop) != simpleProperties.cend();
}

inline bool PropertyGroup::hasProperty(std::string const& main, std::string const& sub) const noexcept
{
	auto range = complexProperties.equal_range(main);

	return std::find_if(range.first, range.second, 
				[sub](std::pair<std::string, std::string> pair) noexcept { return pair.second == sub; }) != range.second;
}