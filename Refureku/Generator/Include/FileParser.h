#pragma once

#include <Parsing/FileParser.h>

namespace rfk
{
	class FileParser : public kodgen::FileParser
	{
		protected:
			virtual void preParse(fs::path const& parseFile)										noexcept override;
			virtual void postParse(fs::path const& parseFile, kodgen::ParsingResult const& result)	noexcept override;

		public:
			FileParser()					noexcept;
			FileParser(FileParser const&)	= default;
			FileParser(FileParser&&)		= default;
			~FileParser()					= default;
	};
}