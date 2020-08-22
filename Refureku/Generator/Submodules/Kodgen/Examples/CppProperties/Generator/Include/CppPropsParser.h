#pragma once

#include <Kodgen/Parsing/FileParser.h>

class CppPropsParser : public kodgen::FileParser
{
	protected:
		virtual void preParse(fs::path const& parseFile)											noexcept override;
		virtual void postParse(fs::path const& parseFile, kodgen::FileParsingResult const& result)	noexcept override;

		public:
			CppPropsParser()						= default;
			CppPropsParser(CppPropsParser const&)	= default;
			CppPropsParser(CppPropsParser&&)		= default;
			~CppPropsParser()						= default;
};