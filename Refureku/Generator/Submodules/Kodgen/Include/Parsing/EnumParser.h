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

			virtual opt::optional<PropertyGroup>	isEntityValid(CXCursor const& currentCursor, ParsingInfo& parsingInfo)						noexcept override final;
			virtual CXChildVisitResult				setAsCurrentEntityIfValid(CXCursor const& classAnnotationCursor, ParsingInfo& parsingInfo)	noexcept override final;
			virtual void							endParsing(ParsingInfo& parsingInfo)														noexcept override final;

		public:
			EnumParser()					= default;
			EnumParser(EnumParser const&)	= default;
			EnumParser(EnumParser&&)		= default;
			~EnumParser()					= default;

			virtual CXChildVisitResult	parse(CXCursor const& currentCursor, ParsingInfo& parsingInfo)			noexcept override final;
			virtual void				updateParsingState(CXCursor const& parent, ParsingInfo& parsingInfo)	noexcept override final;
			virtual void				reset()																	noexcept override final;

			using EntityParser::startParsing;
	};
}