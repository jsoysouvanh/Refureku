#pragma once

#include <clang-c/Index.h>

#include "InfoStructures/ParsingInfo.h"
#include "Parsing/EntityParser.h"

namespace kodgen
{
	class EnumValueParser final : public EntityParser
	{
		private:
			virtual opt::optional<PropertyGroup>	isEntityValid(CXCursor const& currentCursor)				noexcept override final;
			virtual CXChildVisitResult				setAsCurrentEntityIfValid(CXCursor const& annotationCursor)	noexcept override final;

		public:
			EnumValueParser()						= default;
			EnumValueParser(EnumValueParser const&)	= default;
			EnumValueParser(EnumValueParser&&)		= default;
			~EnumValueParser()						= default;

			virtual CXChildVisitResult	parse(CXCursor const& currentCursor)	noexcept override final;

			using EntityParser::startParsing;
	};
}