#pragma once

#include <clang-c/Index.h>

#include "InfoStructures/ParsingInfo.h"
#include "Parsing/EntityParser.h"

namespace kodgen
{
	class EnumValueParser final : public EntityParser
	{
		private:
			virtual opt::optional<PropertyGroup>	isEntityValid(CXCursor const& currentCursor, ParsingInfo& parsingInfo)					noexcept override final;
			virtual CXChildVisitResult				setAsCurrentEntityIfValid(CXCursor const& annotationCursor, ParsingInfo& parsingInfo)	noexcept override final;
			void									addToCurrentEnumValue(CXCursor enumValueCursor, PropertyGroup&& pg, ParsingInfo& parsingInfo)	noexcept;

		public:
			EnumValueParser()						= default;
			EnumValueParser(EnumValueParser const&)	= default;
			EnumValueParser(EnumValueParser&&)		= default;
			~EnumValueParser()						= default;

			virtual CXChildVisitResult	parse(CXCursor const& currentCursor, ParsingInfo& parsingInfo)			noexcept override final;
			virtual void				updateParsingState(CXCursor const& parent, ParsingInfo& parsingInfo)	noexcept override final;

			using EntityParser::startParsing;
	};
}