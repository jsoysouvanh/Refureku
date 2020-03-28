#include "Parsing/EnumValueParser.h"

#include "Misc/Helpers.h"

using namespace kodgen;

CXChildVisitResult EnumValueParser::parse(CXCursor const& currentCursor, ParsingInfo& parsingInfo) noexcept
{
	if (_shouldCheckValidity)
	{
		_shouldCheckValidity = false;

		switch (clang_getCursorKind(currentCursor))
		{
			case CXCursorKind::CXCursor_AnnotateAttr:
				return setAsCurrentEntityIfValid(currentCursor, parsingInfo);

			case CXCursorKind::CXCursor_IntegerLiteral:
				[[fallthrough]];
			case CXCursorKind::CXCursor_BinaryOperator:
				[[fallthrough]];
			case CXCursorKind::CXCursor_UnexposedExpr:
				addToCurrentEnumValue(getCurrentCursor(), PropertyGroup(), parsingInfo);
				break;

			default:
				return CXChildVisitResult::CXChildVisit_Continue;
		}

		return CXChildVisitResult::CXChildVisit_Recurse;
	}

	return CXChildVisitResult::CXChildVisit_Continue;
}

void EnumValueParser::addToCurrentEnumValue(CXCursor enumValueCursor, PropertyGroup&& pg, ParsingInfo& parsingInfo) noexcept
{
	EnumValueInfo& enumValueInfo = parsingInfo.currentEnum->enumValues.emplace_back(EnumValueInfo(enumValueCursor, std::forward<PropertyGroup>(pg)));

	enumValueInfo.defaultValue = clang_getEnumConstantDeclValue(enumValueCursor);
}

void EnumValueParser::updateParsingState(CXCursor const& parent, ParsingInfo& parsingInfo) noexcept
{
	if (!clang_equalCursors(getCurrentCursor(), parent))
	{
		//If the checkValidity flag is set, the current cursor is necessary true
		if (_shouldCheckValidity)
		{
			addToCurrentEnumValue(getCurrentCursor(), PropertyGroup(), parsingInfo);
		}

		endParsing(parsingInfo);
	}
}

opt::optional<PropertyGroup> EnumValueParser::isEntityValid(CXCursor const& currentCursor, ParsingInfo& parsingInfo) noexcept
{
	parsingInfo.propertyParser.clean();

	if (clang_getCursorKind(currentCursor) == CXCursorKind::CXCursor_AnnotateAttr)
	{
		return parsingInfo.propertyParser.getEnumValueProperties(Helpers::getString(clang_getCursorSpelling(currentCursor)));
	}

	return opt::nullopt;
}

CXChildVisitResult EnumValueParser::setAsCurrentEntityIfValid(CXCursor const& annotationCursor, ParsingInfo& parsingInfo) noexcept
{
	if (opt::optional<PropertyGroup> propertyGroup = isEntityValid(annotationCursor, parsingInfo))
	{
		if (parsingInfo.currentEnum.has_value())
		{
			addToCurrentEnumValue(getCurrentCursor(), std::move(*propertyGroup), parsingInfo);

			return CXChildVisitResult::CXChildVisit_Recurse;
		}
		else
		{
			return CXChildVisitResult::CXChildVisit_Continue;
		}
	}
	else
	{
		if (parsingInfo.propertyParser.getParsingError() == EParsingError::Count)
		{
			return CXChildVisitResult::CXChildVisit_Continue;
		}
		else	//Fatal parsing error occured
		{
			parsingInfo.parsingResult.parsingErrors.emplace_back(ParsingError(parsingInfo.propertyParser.getParsingError(), clang_getCursorLocation(annotationCursor)));

			return parsingInfo.parsingSettings.shouldAbortParsingOnFirstError ? CXChildVisitResult::CXChildVisit_Break : CXChildVisitResult::CXChildVisit_Continue;
		}
	}
}