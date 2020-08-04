#pragma once

#include <Kodgen/Parsing/FileParser.h>

#include "GetPropertyRule.h"
#include "SetPropertyRule.h"

class CppPropsParser : public kodgen::FileParser
{
	private:
		/** Property rules used by this parser. */
		GetPropertyRule	_getPropertyRule;
		SetPropertyRule	_setPropertyRule;


	protected:
		virtual void preParse(fs::path const& parseFile)											noexcept override;
		virtual void postParse(fs::path const& parseFile, kodgen::FileParsingResult const& result)	noexcept override;

		public:
			CppPropsParser()						noexcept;
			CppPropsParser(CppPropsParser const&)	= default;
			CppPropsParser(CppPropsParser&&)		= default;
			~CppPropsParser()						= default;
};