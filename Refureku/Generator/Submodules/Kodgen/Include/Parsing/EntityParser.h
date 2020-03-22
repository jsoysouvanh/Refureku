#pragma once

#include <clang-c/Index.h>

#include "Misc/FundamentalTypes.h"
#include "InfoStructures/ParsingInfo.h"

namespace kodgen
{
	class EntityParser
	{
		private:
			uint8		_parsingLevel	= 0u;
			CXCursor	_currentCursor	= clang_getNullCursor();

		protected:
			bool		_shouldCheckValidity	= false;

			virtual opt::optional<PropertyGroup>	isEntityValid(CXCursor const& currentCursor, ParsingInfo& parsingInfo)							noexcept = 0;
			virtual CXChildVisitResult				setAsCurrentEntityIfValid(CXCursor const& classAnnotationCursor, ParsingInfo& parsingInfo)		noexcept = 0;

			virtual void							startParsing(CXCursor const& currentCursor)														noexcept;
			virtual void							endParsing(ParsingInfo& parsingInfo)															noexcept;

			CXCursor const&							getCurrentCursor()																		const	noexcept;

		public:
			EntityParser()						= default;
			EntityParser(EntityParser const&)	= default;
			EntityParser(EntityParser&&)		= default;
			virtual ~EntityParser()				= default;

			virtual CXChildVisitResult	parse(CXCursor const& currentCursor, ParsingInfo& parsingInfo)			noexcept = 0;
			virtual void				updateParsingState(CXCursor const& parent, ParsingInfo& parsingInfo)	noexcept = 0;

			virtual void				reset()																	noexcept;

			uint8						getParsingLevel()												const	noexcept;
	};
}