#include "Kodgen/CodeGen/FileGenerationSettings.h"

using namespace kodgen;

bool FileGenerationSettings::addToParseFile(fs::path const& path) noexcept
{
	fs::path sanitizedPath = FilesystemHelpers::sanitizePath(path);

	if (!sanitizedPath.empty() && !fs::is_directory(sanitizedPath))
	{
		return _toParseFiles.emplace(std::move(sanitizedPath)).second;
	}

	return false;
}

bool FileGenerationSettings::addToParseDirectory(fs::path const& path) noexcept
{
	fs::path sanitizedPath = FilesystemHelpers::sanitizePath(path);

	if (!sanitizedPath.empty() && fs::is_directory(sanitizedPath))
	{
		return _toParseDirectories.emplace(std::move(sanitizedPath)).second;
	}

	return false;
}

bool FileGenerationSettings::addIgnoredFile(fs::path const& path) noexcept
{
	fs::path sanitizedPath = FilesystemHelpers::sanitizePath(path);

	if (!sanitizedPath.empty() && !fs::is_directory(sanitizedPath))
	{
		return _ignoredFiles.emplace(std::move(sanitizedPath)).second;
	}

	return false;
}

bool FileGenerationSettings::addIgnoredDirectory(fs::path const& path) noexcept
{
	fs::path sanitizedPath = FilesystemHelpers::sanitizePath(path);

	if (!sanitizedPath.empty() && fs::is_directory(sanitizedPath))
	{
		return _ignoredDirectories.emplace(std::move(sanitizedPath)).second;
	}

	return false;
}

void FileGenerationSettings::removeToParseFile(fs::path const& path) noexcept
{
	_toParseFiles.erase(FilesystemHelpers::sanitizePath(path));
}

void FileGenerationSettings::removeToParseDirectory(fs::path const& path) noexcept
{
	_toParseDirectories.erase(FilesystemHelpers::sanitizePath(path));
}

void FileGenerationSettings::removeIgnoredFile(fs::path const& path) noexcept
{
	_ignoredFiles.erase(FilesystemHelpers::sanitizePath(path));
}

void FileGenerationSettings::removeIgnoredDirectory(fs::path const& path) noexcept
{
	_ignoredDirectories.erase(FilesystemHelpers::sanitizePath(path));
}