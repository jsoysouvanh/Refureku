/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <Kodgen/Parsing/FileParser.h>

namespace rfk
{
	class FileParser : public kodgen::FileParser
	{
		protected:
			virtual void preParse(fs::path const& parseFile) noexcept override
			{
				if (logger != nullptr)
				{
					logger->log("Start parsing: " + parseFile.string(), kodgen::ILogger::ELogSeverity::Info);
				}
			}

			virtual void postParse(fs::path const& parseFile, kodgen::FileParsingResult const& result) noexcept override
			{
				if (logger != nullptr)
				{
					for (kodgen::ParsingError const& parsingError : result.errors)
					{
						logger->log(parsingError.toString(), kodgen::ILogger::ELogSeverity::Error);
					}

					logger->log(parseFile.string() + ": Found " + std::to_string(result.namespaces.size()) + " namespace(s), " +
								std::to_string(result.structs.size()) + " struct(s), " +
								std::to_string(result.classes.size()) + " classe(s) and " +
								std::to_string(result.enums.size()) + " enum(s).", kodgen::ILogger::ELogSeverity::Info);
				}
			}
	};
}