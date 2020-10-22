#include "Kodgen/Misc/Filesystem.h"

using namespace kodgen;

fs::path FilesystemHelpers::sanitizePath(fs::path const& path) noexcept
{
	return (fs::exists(path)) ? fs::canonical(fs::path(path).make_preferred()) : fs::path();
}