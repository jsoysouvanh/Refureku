#pragma once

#include <clang-c/Index.h>

#include "Misc/FundamentalTypes.h"
#include "InfoStructures/ParsingInfo.h"
#include "Parsing/EnumValueParser.h"
#include "Parsing/EntityParser.h"

namespace kodgen
{
	class EnumParser final : public EntityParser
	{
		private:
			EnumValueParser	_enumValueParser;

			virtual opt::optional<PropertyGroup>	isEntityValid(CXCursor const& currentCursor)						noexcept override final;
			virtual CXChildVisitResult				setAsCurrentEntityIfValid(CXCursor const& classAnnotationCursor)	noexcept override final;

			CXChildVisitResult						parseEnumValue(CXCursor enumCursor)									noexcept;

		public:
			EnumParser()					= default;
			EnumParser(EnumParser const&)	= default;
			EnumParser(EnumParser&&)		= default;
			~EnumParser()					= default;

			virtual CXChildVisitResult	endParsing()							noexcept override final;
			virtual CXChildVisitResult	parse(CXCursor const& currentCursor)	noexcept override final;
			virtual void				reset()									noexcept override final;
			virtual void				setParsingInfo(ParsingInfo* info)		noexcept override final;

			using EntityParser::startParsing;
	};
}