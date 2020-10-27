/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

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

	class FilesystemHelpers
	{
		public:
			FilesystemHelpers()							= delete;
			FilesystemHelpers(FilesystemHelpers const&) = delete;
			FilesystemHelpers(FilesystemHelpers&&)		= delete;
			~FilesystemHelpers()						= delete;

			/**
			*	@brief Make a canonical path from the provided path.
			*
			*	@param path The path to sanitize.
			*	
			*	@return A canonical path if the provided path was valid, else an empty path.
			*/
			static fs::path sanitizePath(fs::path const& path)	noexcept;
	};
}