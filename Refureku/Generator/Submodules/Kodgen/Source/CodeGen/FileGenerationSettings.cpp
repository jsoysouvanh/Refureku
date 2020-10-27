#include "Kodgen/CodeGen/FileGenerationSettings.h"

using namespace kodgen;

bool FileGenerationSettings::setOutputDirectory(fs::path outputDirectory) noexcept
{
	if (!outputDirectory.empty())
	{
		outputDirectory.make_preferred();

		if (fs::exists(outputDirectory))
		{
			if (fs::is_directory(outputDirectory))
			{
				_outputDirectory = FilesystemHelpers::sanitizePath(outputDirectory);

				return true;
			}

			//the path points to a file
		}
		else //the provided path doesn't exist
		{
			//Make it absolute first
			std::error_code error;
			outputDirectory = fs::absolute(outputDirectory, error);

			if (!outputDirectory.empty())
			{
				_outputDirectory = outputDirectory;

				return true;
			}
		}
	}

	return false;
}

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

void FileGenerationSettings::clearToParseFiles() noexcept
{
	_toParseFiles.clear();
}

void FileGenerationSettings::clearToParseDirectories() noexcept
{
	_toParseDirectories.clear();
}

void FileGenerationSettings::clearIgnoredFiles() noexcept
{
	_ignoredFiles.clear();
}

void FileGenerationSettings::clearIgnoredDirectories() noexcept
{
	_ignoredDirectories.clear();
}