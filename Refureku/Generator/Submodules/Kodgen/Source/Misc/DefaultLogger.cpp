#include "Kodgen/Misc/DefaultLogger.h"

#include <iostream>

using namespace kodgen;

void DefaultLogger::logInfo(std::string const& message) noexcept
{
	std::cout << "[Info] " << message << std::endl;
}

void DefaultLogger::logWarning(std::string const& message) noexcept
{
	std::cout << "[Warning] " << message << std::endl;
}

void DefaultLogger::logError(std::string const& message) noexcept
{
	std::cerr << "[Error] " << message << std::endl;
}

void DefaultLogger::log(std::string const& message, ELogSeverity logSeverity) noexcept
{
	switch (logSeverity)
	{
		case ELogSeverity::Info:
			logInfo(message);
			break;

		case ELogSeverity::Warning:
			logWarning(message);
			break;

		case ELogSeverity::Error:
			logError(message);
			break;
	}
}