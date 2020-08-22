#include "CppPropsParser.h"

void CppPropsParser::preParse(fs::path const& parseFile) noexcept
{
	if (logger != nullptr)
	{
		logger->log("Start parsing: " + parseFile.string(), kodgen::ILogger::ELogSeverity::Info);
	}
}

void CppPropsParser::postParse(fs::path const&, kodgen::FileParsingResult const& result) noexcept
{
	if (logger != nullptr)
	{
		for (kodgen::ParsingError const& parsingError : result.errors)
		{
			logger->log(parsingError.toString(), kodgen::ILogger::ELogSeverity::Error);
		}

		logger->log("Found " + std::to_string(result.namespaces.size()) + " namespaces, " + std::to_string(result.classes.size()) + " classes and " + std::to_string(result.enums.size()) + " enums.", kodgen::ILogger::ELogSeverity::Info);
	}
}