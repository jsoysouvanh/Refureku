#pragma once

#include <clang-c/Index.h>

#include "InfoStructures/ParsingInfo.h"
#include "Parsing/EntityParser.h"

namespace kodgen
{
	class MethodParser : public EntityParser
	{
		private:
			virtual CXChildVisitResult				setAsCurrentEntityIfValid(CXCursor const& methodAnnotationCursor)	noexcept override final;
			virtual opt::optional<PropertyGroup>	isEntityValid(CXCursor const& currentCursor)						noexcept override final;
			void									setupMethod(CXCursor const& methodCursor, MethodInfo& methodInfo)	noexcept;

		public:
			MethodParser()						= default;
			MethodParser(MethodParser const&)	= default;
			MethodParser(MethodParser&&)		= default;
			~MethodParser()						= default;

			virtual CXChildVisitResult	parse(CXCursor const& cursor)											noexcept override final;

			using EntityParser::startParsing;
	};
}