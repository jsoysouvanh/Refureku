#include "Kodgen/Misc/Filesystem.h"

using namespace kodgen;

fs::path FilesystemHelpers::sanitizePath(fs::path const& path) noexcept
{
	return (fs::exists(path)) ? fs::canonical(fs::path(path).make_preferred()) : fs::path();
}

bool FilesystemHelpers::isChildPath(fs::path const& child, fs::path const& other) noexcept
{
	//other can't be child base path if it is not a directory
	if (fs::is_directory(other))
	{
		fs::path checkedPath = child;

		while (checkedPath.has_parent_path() &&
			   checkedPath.has_root_path() &&
			   checkedPath != checkedPath.root_path())
		{
			checkedPath = checkedPath.parent_path();

			if (checkedPath == other)
			{
				return true;
			}
		}
	}

	return false;
}