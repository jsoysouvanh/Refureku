#include "Kodgen/Misc/CompilerHelpers.h"

#include <cassert>
#include <cctype>		//std::tolower
#include <sstream>		//std::stringstream
#include <algorithm>	//std::transform

#include "Kodgen/Misc/System.h"

using namespace kodgen;

std::vector<std::string> CompilerHelpers::getCompilerNativeIncludeDirectories(std::string compiler)
{
	std::vector<std::string> result;
	
	//Don't do anything if the compiler is an empty string
	if (compiler.size() > 0)
	{
		//lowercase compiler name to make checks easier
		std::transform(compiler.begin(), compiler.end(), compiler.begin(), [](unsigned char c)
					   {
						   return std::tolower(c);
					   });

#if _WIN32
		//Check MSVC on windows only
		if (compiler.substr(0u, msvcCompilerName.size()) == msvcCompilerName)
		{
			return getMSVCNativeIncludeDirectories(compiler);
		}
#endif

		//Check clang
		if (compiler.substr(0u, clangCompilerName.size()) == clangCompilerName)
		{
			return getClangNativeIncludeDirectories(compiler);
		}
		//Check GCC
		else if (compiler.substr(0u, gccCompilerName.size()) == gccCompilerName || compiler.substr(0u, gccCompilerName2.size()) == gccCompilerName2)
		{
			return getGCCNativeIncludeDirectories(compiler);
		}
	}

	return result;
}

std::vector<std::string> CompilerHelpers::getClangNativeIncludeDirectories(std::string const& clangExeName) noexcept
{
	assert(clangExeName.substr(0u, 5u) == clangCompilerName);

	std::vector<std::string> result;

	try
	{
#if _WIN32
		std::stringstream cmdResult(System::executeCommand(clangExeName + " -Wp,-v -xc++ nul 2>&1"));
#else
		std::stringstream cmdResult(System::executeCommand(clangExeName + " -Wp,-v -xc++ /dev/null 2>&1"));
#endif

		std::string line;
		bool		isParsingPaths = false;
		while (!cmdResult.eof())
		{
			std::getline(cmdResult, line);

			if (isParsingPaths)
			{
				//All paths start with a ' ' character
				if (line.size() > 0 && line[0] == ' ')
				{
					result.emplace_back(line.substr(1));
				}
				else
				{
					break;
				}
			}
			else
			{
				//Try to find the start of paths list
				if (line == "#include <...> search starts here:")
				{
					isParsingPaths = true;
				}
			}
		}
	}
	catch (...)
	{
	}

	return result;
}

std::vector<std::string> CompilerHelpers::getGCCNativeIncludeDirectories(std::string const& gccExeName) noexcept
{
	assert(gccExeName.substr(0u, 3u) == gccCompilerName || gccExeName.substr(0u, 3u) == gccCompilerName2);

	std::vector<std::string> result;

	try
	{
#if _WIN32
		std::stringstream cmdResult(System::executeCommand(gccExeName + " -Wp,-v -xc++ nul 2>&1"));
#else
		std::stringstream cmdResult(System::executeCommand(gccExeName + " -Wp,-v -xc++ /dev/null 2>&1"));
#endif

		std::string line;
		bool		isParsingPaths = false;
		while (!cmdResult.eof())
		{
			std::getline(cmdResult, line);

			if (isParsingPaths)
			{
				//All paths start with a ' ' character
				if (line.size() > 0 && line[0] == ' ')
				{
					result.emplace_back(line.substr(1));
				}
				else
				{
					break;
				}
			}
			else
			{
				//Try to find the start of paths list
				if (line == "#include <...> search starts here:")
				{
					isParsingPaths = true;
				}
			}
		}
	}
	catch (...)
	{
	}

	return result;
}

std::vector<std::string> CompilerHelpers::getMSVCNativeIncludeDirectories(std::string const& msvcExeName) noexcept
{
	std::vector<std::string> result;

	//TODO

	return result;
}