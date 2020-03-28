#pragma once

#include <clang-c/Index.h>

#include "Misc/FundamentalTypes.h"
#include "Misc/EAccessSpecifier.h"
#include "InfoStructures/ParsingInfo.h"
#include "Parsing/EntityParser.h"
#include "Parsing/FieldParser.h"
#include "Parsing/MethodParser.h"

namespace kodgen
{
	class ClassParser final : public EntityParser
	{
		private:
			EntityInfo::EType		_structOrClass	= EntityInfo::EType::Count;

			FieldParser				_fieldParser;
			MethodParser			_methodParser;

			void									initClassInfos(StructClassInfo& toInit)														const	noexcept;

		protected:
			virtual opt::optional<PropertyGroup>	isEntityValid(CXCursor const& currentCursor, ParsingInfo& parsingInfo)								noexcept override final;
			virtual CXChildVisitResult				setAsCurrentEntityIfValid(CXCursor const& classAnnotationCursor, ParsingInfo& parsingInfo)			noexcept override final;
			virtual void							endParsing(ParsingInfo& parsingInfo)																noexcept override final;
			
			void									addToParents(CXCursor cursor, ParsingInfo& parsingInfo)										const	noexcept;	
			void									updateAccessSpecifier(CXCursor const& cursor, ParsingInfo& parsingInfo)						const	noexcept;

		public:
			ClassParser()					= default;
			ClassParser(ClassParser const&) = default;
			ClassParser(ClassParser&&)		= default;
			~ClassParser()					= default;

			virtual CXChildVisitResult	parse(CXCursor const& currentCursor, ParsingInfo& parsingInfo)							noexcept override final;
			virtual void				updateParsingState(CXCursor const& parent, ParsingInfo& parsingInfo)					noexcept override final;
			virtual void				reset()																					noexcept override final;

			void						startClassParsing(CXCursor const& currentCursor, ParsingInfo& parsingInfo)				noexcept;
			void						startStructParsing(CXCursor const& currentCursor, ParsingInfo& parsingInfo)				noexcept;
	};
}