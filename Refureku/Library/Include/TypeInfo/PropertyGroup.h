#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>

namespace rfk
{
	class PropertyGroup
	{
		public:
			std::unordered_set<std::string>						simpleProperties;
			std::unordered_multimap<std::string, std::string>	complexProperties;

			/** Return true if the property group contains the provided simple property */
			bool	hasProperty(std::string const& prop)							const	noexcept;

			/** Return true if the property group contains the provided complex property */
			bool	hasProperty(std::string const& main, std::string const& sub)	const	noexcept;
	};
}