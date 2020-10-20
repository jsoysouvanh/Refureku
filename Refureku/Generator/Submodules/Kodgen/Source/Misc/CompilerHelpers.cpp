#include "Kodgen/Misc/CompilerHelpers.h"

#include <cassert>
#include <cctype>		//std::tolower
#include <sstream>		//std::stringstream
#include <algorithm>	//std::transform

#if _WIN32
#include <Windows.h>	//GetModuleFileNameA, GetLastError, ERROR_INSUFFICIENT_BUFFER
#endif

#include "Kodgen/Misc/System.h"

using namespace kodgen;

std::vector<fs::path> CompilerHelpers::getCompilerNativeIncludeDirectories(std::string compiler)
{
	std::vector<fs::path> result;
	
	//Don't do anything if the compiler is an empty string
	if (compiler.size() > 0)
	{
		//lowercase compiler name to make checks easier
		std::transform(compiler.begin(), compiler.end(), compiler.begin(), [](char c) -> char
					   {
						   return static_cast<char>(std::tolower((static_cast<int>(c))));
					   });

#if _WIN32
		//Check MSVC on windows only
		if (compiler == msvcCompilerName)
		{
			return getMSVCNativeIncludeDirectories();
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

std::vector<fs::path> CompilerHelpers::getClangNativeIncludeDirectories(std::string const& clangExeName)
{
	//Make sure the compiler name actually starts by "clang"
	assert(clangExeName.substr(0u, clangCompilerName.size()) == clangCompilerName);

	std::vector<fs::path> result;

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
			if (!line.empty() && line[0] == ' ')
			{
				result.emplace_back(line.substr(1));

				assert(fs::exists(result.back()) && fs::is_directory(result.back()));
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

	//Throw an exception if we've not found the "#include <...> search starts here:" part
	if (!isParsingPaths)
	{
		throw std::runtime_error("Could not run the " + clangExeName + " command on this computer.");
	}

	return result;
}

std::vector<fs::path> CompilerHelpers::getGCCNativeIncludeDirectories(std::string const& gccExeName)
{
	//Make sure the compiler name actually starts by "gcc" or "g++"
	assert(gccExeName.substr(0u, gccCompilerName.size()) == gccCompilerName || gccExeName.substr(0u, gccCompilerName2.size()) == gccCompilerName2);

	std::vector<fs::path> result;

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
			if (!line.empty() && line[0] == ' ')
			{
				result.emplace_back(line.substr(1));

				assert(fs::exists(result.back()) && fs::is_directory(result.back()));
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

	//Throw an exception if we've not found the "#include <...> search starts here:" part
	if (!isParsingPaths)
	{
		throw std::runtime_error("Could not run the " + gccExeName + " command on this computer.");
	}

	return result;
}

#if _WIN32

fs::path CompilerHelpers::getvswherePath() noexcept
{
	std::wstring	exePath(256, ' ');	//Base allocation
	fs::path		vswherePath;

	//Find the current executable path
	while (GetModuleFileNameW(nullptr, exePath.data(), static_cast<DWORD>(exePath.capacity())) == 0 && GetLastError() == ERROR_INSUFFICIENT_BUFFER)
	{
		//exePath is too long, retry with a bigger string capacity
		exePath.reserve(exePath.capacity() * 2u);
	}

	//parent_path to remove executable name from the path (get executable directory path)
	vswherePath = fs::path(exePath.data()).parent_path() / "vswhere.exe";

	return fs::exists(vswherePath) ? vswherePath : fs::path();
}

std::vector<fs::path> CompilerHelpers::getMSVCNativeIncludeDirectories()
{
	std::vector<fs::path>	result;
	fs::path				vswhere = getvswherePath();

	if (vswhere.empty())
	{
		throw std::runtime_error("Could not locate vswhere.exe next to the executable.");
	}
	else
	{
		std::stringstream cmdResult(System::executeCommand(vswhere.string() + R"( -latest -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -find "VC\Tools\MSVC\**\include)"));

		std::string line;
		while (!cmdResult.eof())
		{
			std::getline(cmdResult, line);

			if (!line.empty())
			{
				result.emplace_back(std::move(line));
			}
		}
	}
	
	return result;
}
#endif