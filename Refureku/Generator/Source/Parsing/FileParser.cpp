#include "RefurekuGenerator/Parsing/FileParser.h"

using namespace rfk;

void FileParser::preParse(fs::path const& parseFile) noexcept
{
	if (logger != nullptr)
	{
		logger->log("Start parsing: " + parseFile.string(), kodgen::ILogger::ELogSeverity::Info);
	}
}

void FileParser::postParse(fs::path const&, kodgen::FileParsingResult const& result) noexcept
{
	if (logger != nullptr)
	{
		for (kodgen::ParsingError const& parsingError : result.errors)
		{
			logger->log(parsingError.toString(), kodgen::ILogger::ELogSeverity::Error);
		}

		logger->log("Found " + std::to_string(result.namespaces.size()) + " namespace(s), " +
					std::to_string(result.structs.size()) + " struct(s), " +
					std::to_string(result.classes.size()) + " classe(s) and " +
					std::to_string(result.enums.size()) + " enum(s).", kodgen::ILogger::ELogSeverity::Info);
	}
}