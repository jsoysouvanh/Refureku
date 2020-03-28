#include "Parsing/EnumParser.h"

#include "Misc/Helpers.h"

using namespace kodgen;

void EnumParser::reset() noexcept
{
	EntityParser::reset();

	_enumValueParser.reset();
}

CXChildVisitResult EnumParser::parse(CXCursor const& currentCursor, ParsingInfo& parsingInfo) noexcept
{
	if (_enumValueParser.getParsingLevel())
	{
		_enumValueParser.parse(currentCursor, parsingInfo);
	}
	else if (_shouldCheckValidity)	//Check for any annotation if the flag is raised
	{
		_shouldCheckValidity = false;

		return setAsCurrentEntityIfValid(currentCursor, parsingInfo);
	}

	switch (clang_getCursorKind(currentCursor))
	{
		case CXCursorKind::CXCursor_EnumConstantDecl:
			_enumValueParser.startParsing(currentCursor);
			break;

		default:
			return CXChildVisitResult::CXChildVisit_Continue;
	}

	return CXChildVisitResult::CXChildVisit_Recurse;
}

void EnumParser::updateParsingState(CXCursor const& parent, ParsingInfo& parsingInfo) noexcept
{
	//Check if we finished parsing an enum value
	if (_enumValueParser.getParsingLevel())
	{
		_enumValueParser.updateParsingState(parent, parsingInfo);
	}

	//Check if we finished parsing the enum
	if (clang_equalCursors(clang_getCursorSemanticParent(getCurrentCursor()), parent))
	{
		endParsing(parsingInfo);
	}
}

void EnumParser::endParsing(ParsingInfo& parsingInfo) noexcept
{
	EntityParser::endParsing(parsingInfo);

	parsingInfo.flushCurrentEnum();
}

opt::optional<PropertyGroup> EnumParser::isEntityValid(CXCursor const& currentCursor, ParsingInfo& parsingInfo) noexcept
{
	parsingInfo.propertyParser.clean();

	if (clang_getCursorKind(currentCursor) == CXCursorKind::CXCursor_AnnotateAttr)
	{
		return parsingInfo.propertyParser.getEnumProperties(Helpers::getString(clang_getCursorSpelling(currentCursor)));
	}

	return opt::nullopt;
}

CXChildVisitResult EnumParser::setAsCurrentEntityIfValid(CXCursor const& classAnnotationCursor, ParsingInfo& parsingInfo) noexcept
{
	if (opt::optional<PropertyGroup> propertyGroup = isEntityValid(classAnnotationCursor, parsingInfo))
	{
		EnumInfo& enumInfo = parsingInfo.currentEnum.emplace(EnumInfo(getCurrentCursor(), std::move(*propertyGroup)));

		CXType underlyingType				= clang_getEnumDeclIntegerType(getCurrentCursor());
		enumInfo.underlyingType				= Helpers::getString(clang_getTypeSpelling(underlyingType));
		enumInfo.canonicalUnderlyingType	= Helpers::getString(clang_getTypeSpelling(clang_getCanonicalType(underlyingType)));

		return CXChildVisitResult::CXChildVisit_Recurse;
	}
	else
	{
		if (parsingInfo.propertyParser.getParsingError() == EParsingError::Count)
		{
			endParsing(parsingInfo);
			return CXChildVisitResult::CXChildVisit_Continue;
		}
		else	//Fatal parsing error occured
		{
			parsingInfo.parsingResult.parsingErrors.emplace_back(ParsingError(parsingInfo.propertyParser.getParsingError(), clang_getCursorLocation(classAnnotationCursor)));

			return parsingInfo.parsingSettings.shouldAbortParsingOnFirstError ? CXChildVisitResult::CXChildVisit_Break : CXChildVisitResult::CXChildVisit_Continue;
		}
	}
}