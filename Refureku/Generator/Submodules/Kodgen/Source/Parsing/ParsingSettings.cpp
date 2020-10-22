#include "Kodgen/Parsing/ParsingSettings.h"

#include "Kodgen/Misc/CompilerHelpers.h"

using namespace kodgen;

bool ParsingSettings::addProjectIncludeDirectory(fs::path const& directoryPath) noexcept
{
	fs::path sanitizedPath = FilesystemHelpers::sanitizePath(directoryPath);

	if (!sanitizedPath.empty() && fs::is_directory(sanitizedPath))
	{
		return _projectIncludeDirectories.emplace(std::move(sanitizedPath)).second;
	}

	return false;
}

void ParsingSettings::removeProjectIncludeDirectory(fs::path const& directoryPath) noexcept
{
	_projectIncludeDirectories.erase(FilesystemHelpers::sanitizePath(directoryPath));
}

bool ParsingSettings::setCompilerExeName(std::string const& compilerExeName) noexcept
{
	if (CompilerHelpers::isSupportedCompiler(compilerExeName))
	{
		_compilerExeName = compilerExeName;

		return true;
	}

	return false;
}