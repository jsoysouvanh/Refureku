#pragma once

#include <clang-c/Index.h>

#include "Misc/Optional.h"
#include "InfoStructures/ParsingInfo.h"
#include "Properties/PropertyGroup.h"
#include "Parsing/EntityParser.h"

namespace kodgen
{
	class FieldParser : public kodgen::EntityParser
	{
		private:
			virtual CXChildVisitResult				setAsCurrentEntityIfValid(CXCursor const& fieldAnnotationCursor, ParsingInfo& parsingInfo)	noexcept override final;
			virtual	opt::optional<PropertyGroup>	isEntityValid(CXCursor const& currentCursor, ParsingInfo& parsingInfo)						noexcept override final;

		public:
			FieldParser()					= default;
			FieldParser(FieldParser const&) = default;
			FieldParser(FieldParser&&)		= default;
			virtual ~FieldParser()			= default;

			virtual CXChildVisitResult	parse(CXCursor const& cursor, ParsingInfo& parsingInfo)					noexcept override final;
			virtual void				updateParsingState(CXCursor const& parent, ParsingInfo& parsingInfo)	noexcept override final;

			using EntityParser::startParsing;
	};
}