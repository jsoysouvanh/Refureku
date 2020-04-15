#pragma once

#if __has_include(<filesystem>)
	#include <filesystem>
	namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
	#include <experimental/filesystem>
	namespace fs = std::experimental::filesystem;
#else
	#error "No filesystem support"
#endif

#include <functional>

namespace kodgen
{
	struct PathHash
	{
		size_t operator()(fs::path const& path) const noexcept
		{
			return std::hash<std::string>()(path.string());
		}
	};
}