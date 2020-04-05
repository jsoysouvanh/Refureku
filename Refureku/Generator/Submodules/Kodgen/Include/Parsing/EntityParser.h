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
			bool			_shouldCheckValidity	= false;
			ParsingInfo*	_parsingInfo			= nullptr;

			virtual opt::optional<PropertyGroup>	isEntityValid(CXCursor const& currentCursor)						noexcept = 0;
			virtual CXChildVisitResult				setAsCurrentEntityIfValid(CXCursor const& classAnnotationCursor)	noexcept = 0;

			CXCursor const&							getCurrentCursor()											const	noexcept;

		public:
			EntityParser()						= default;
			EntityParser(EntityParser const&)	= default;
			EntityParser(EntityParser&&)		= default;
			virtual ~EntityParser()				= default;

			virtual void				startParsing(CXCursor const& currentCursor)	noexcept;
			virtual CXChildVisitResult	endParsing()								noexcept;

			virtual CXChildVisitResult	parse(CXCursor const& currentCursor)		noexcept = 0;

			virtual void				reset()										noexcept;
			virtual void				setParsingInfo(ParsingInfo* info)			noexcept;
			
			uint8						getParsingLevel()					const	noexcept;
	};
}