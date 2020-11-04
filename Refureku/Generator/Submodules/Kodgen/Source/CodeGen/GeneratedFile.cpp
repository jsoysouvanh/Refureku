#include "Kodgen/CodeGen/GeneratedFile.h"

using namespace kodgen;

GeneratedFile::GeneratedFile(fs::path&& generatedFilePath, fs::path const& sourceFilePath) noexcept:
	_path{std::forward<fs::path>(generatedFilePath)},
	_sourceFilePath{sourceFilePath},
	_streamToFile(_path.string(), std::ios::out | std::ios::trunc)
{
}

GeneratedFile::~GeneratedFile() noexcept
{
	_streamToFile.close();
}

void GeneratedFile::writeLine(std::string const& line) noexcept
{
	_streamToFile << line << std::endl;
}

void GeneratedFile::writeLine(std::string&& line) noexcept
{
	_streamToFile << std::forward<std::string>(line) << std::endl;
}

void GeneratedFile::writeLines(std::string const& line) noexcept
{
	writeLine(line);
}

void GeneratedFile::writeLines(std::string&& line) noexcept
{
	writeLine(std::forward<std::string>(line));
}

void GeneratedFile::expandWriteMacroLines(std::string&& line) noexcept
{
	writeLine("\t" + std::forward<std::string>(line));
	writeLine("");
}

void GeneratedFile::writeMacro(std::string&& macroName) noexcept
{
	writeLine("#define " + std::forward<std::string>(macroName));
}

void GeneratedFile::undefMacro(std::string macroName) noexcept
{
	writeLine("#ifdef " + macroName + "\n\t#undef " + std::move(macroName) + "\n#endif");
}

fs::path const& GeneratedFile::getPath() const noexcept
{
	return _path;
}

fs::path const& GeneratedFile::getSourceFilePath() const noexcept
{
	return _sourceFilePath;
}