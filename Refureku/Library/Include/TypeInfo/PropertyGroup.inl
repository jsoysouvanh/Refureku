
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