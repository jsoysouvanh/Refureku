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

bool CompilerHelpers::isSupportedCompiler(std::string const& compiler) noexcept
{
	std::string normalizedCompilerExecutable = normalizeCompilerExeName(compiler);

	return 
#if _WIN32
		//Check MSVC only on windows platform
		(isMSVC(normalizedCompilerExecutable) && isMSVCSupported()) ||
#endif
		(isClang(normalizedCompilerExecutable) && isClangSupported(normalizedCompilerExecutable)) ||
		(isGCC(normalizedCompilerExecutable) && isGCCSupported(normalizedCompilerExecutable));
}

bool CompilerHelpers::isGCCSupported(std::string const& gccExeName) noexcept
{
	std::stringstream cmdResult(System::executeCommand(gccExeName + " 2>&1"));

	std::string line;
	while (!cmdResult.eof())
	{
		std::getline(cmdResult, line);

		if (line.find("no input files") != std::string::npos)
		{
			return true;
		}
	}

	return false;
}

bool CompilerHelpers::isClangSupported(std::string const& clangExeName) noexcept
{
	std::stringstream cmdResult(System::executeCommand(clangExeName + " 2>&1"));

	std::string line;
	while (!cmdResult.eof())
	{
		std::getline(cmdResult, line);

		if (line.find("no input files") != std::string::npos)
		{
			return true;
		}
	}

	return false;
}

bool CompilerHelpers::isMSVCSupported() noexcept
{
#if _WIN32
	fs::path vswhere = getvswherePath();

	if (!vswhere.empty())
	{
		std::stringstream cmdResult(System::executeCommand(vswhere.string() + R"( -latest -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -find "VC\Tools\MSVC)"));

		std::string line;
		while (!cmdResult.eof())
		{
			std::getline(cmdResult, line);

			if (!line.empty())
			{
				return true;
			}
		}
	}
#endif

	return false;
}

bool CompilerHelpers::isMSVC(std::string const& normalizedCompilerExeName) noexcept
{
	return normalizedCompilerExeName == msvcCompilerName;
}

bool CompilerHelpers::isClang(std::string const& normalizedCompilerExeName) noexcept
{
	return normalizedCompilerExeName.substr(0, clangCompilerName.size()) == clangCompilerName;
}

bool CompilerHelpers::isGCC(std::string const& normalizedCompilerExeName) noexcept
{
	return	normalizedCompilerExeName.substr(0u, gccCompilerName.size()) == gccCompilerName ||
			normalizedCompilerExeName.substr(0u, gccCompilerName2.size()) == gccCompilerName2;
}

std::vector<fs::path> CompilerHelpers::getCompilerNativeIncludeDirectories(std::string const& compiler)
{
	std::vector<fs::path> result;
	
	//Don't do anything if the compiler is an empty string
	if (compiler.size() > 0)
	{
		std::string normalizedCompilerExeName = normalizeCompilerExeName(compiler);

#if _WIN32
		//Check MSVC on windows only
		if (isMSVC(normalizedCompilerExeName))
		{
			return getMSVCNativeIncludeDirectories();
		}
#endif

		//Check clang
		if (isClang(normalizedCompilerExeName))
		{
			return getClangNativeIncludeDirectories(normalizedCompilerExeName);
		}
		//Check GCC
		else if (isGCC(normalizedCompilerExeName))
		{
			return getGCCNativeIncludeDirectories(normalizedCompilerExeName);
		}
	}

	return result;
}

std::vector<fs::path> CompilerHelpers::getClangNativeIncludeDirectories(std::string const& clangExeName)
{
	//Make sure the compiler name actually starts by "clang"
	assert(isClang(clangExeName));

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
				//Strip the ' ' character
				line = line.substr(1);

				if (fs::exists(line) && fs::is_directory(line))
				{
					result.emplace_back(line);
				}
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
	assert(isGCC(gccExeName));

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
				//Strip the ' ' character
				line = line.substr(1);

				if (fs::exists(line) && fs::is_directory(line))
				{
					result.emplace_back(line);
				}
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

std::string CompilerHelpers::normalizeCompilerExeName(std::string const& compilerName) noexcept
{
	std::string result = compilerName;

	std::transform(result.begin(), result.end(), result.begin(), [](char c) -> char
				   {
					   return static_cast<char>(std::tolower((static_cast<int>(c))));
				   });

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