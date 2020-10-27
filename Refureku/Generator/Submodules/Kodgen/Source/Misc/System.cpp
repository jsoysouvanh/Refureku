#include "Kodgen/Misc/System.h"

#include <iostream>
#include <array>
#include <memory>	//std::unique_ptr
#include <cstdio>	//std::fgets

using namespace kodgen;

std::string System::executeCommand(std::string const& cmd)
{
	constexpr int const bufferSize = 128;

	std::array<char, bufferSize>	buffer;
	std::string						result;

#if _WIN32
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd.data(), "r"), _pclose);
#else
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.data(), "r"), pclose);
#endif

	if (pipe.get() == nullptr)
	{
		throw std::runtime_error("Failed to create a pipe to execute the command.");
	}

	while (std::fgets(buffer.data(), bufferSize, pipe.get()) != nullptr)
	{
		result += buffer.data();
	}

	return result;
}