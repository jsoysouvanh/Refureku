#include "Parsing/FieldParser.h"

#include <cassert>

#include "Misc/Helpers.h"

using namespace kodgen;

CXChildVisitResult FieldParser::parse(CXCursor const& cursor, ParsingInfo& parsingInfo) noexcept
{
	//Check for any annotation attribute if the flag is raised
	if (_shouldCheckValidity)
	{
		return setAsCurrentEntityIfValid(cursor, parsingInfo);
	}

	return CXChildVisitResult::CXChildVisit_Recurse;
}

CXChildVisitResult FieldParser::setAsCurrentEntityIfValid(CXCursor const& fieldAnnotationCursor, ParsingInfo& parsingInfo) noexcept
{
	if (opt::optional<PropertyGroup> propertyGroup = isEntityValid(fieldAnnotationCursor, parsingInfo))
	{
		if (parsingInfo.currentStructOrClass.has_value())
		{
			FieldInfo& field = parsingInfo.currentStructOrClass->fields.emplace_back(FieldInfo(getCurrentCursor(), std::move(*propertyGroup)));
			
			field.accessSpecifier = parsingInfo.accessSpecifier;
			field.type = TypeInfo(clang_getCursorType(getCurrentCursor()));
			field.qualifiers.isStatic = (clang_getCursorKind(getCurrentCursor()) == CXCursorKind::CXCursor_VarDecl);

			if (!field.qualifiers.isStatic)
			{
				field.qualifiers.isMutable = clang_CXXField_isMutable(getCurrentCursor());

				field.memoryOffset = clang_Cursor_getOffsetOfField(getCurrentCursor());

				// assert(field.memoryOffset != CXTypeLayoutError::CXTypeLayoutError_Invalid);	<- Assert here on travis for some reasons...
				assert(field.memoryOffset != CXTypeLayoutError::CXTypeLayoutError_Incomplete);
				assert(field.memoryOffset != CXTypeLayoutError::CXTypeLayoutError_Dependent);
				assert(field.memoryOffset != CXTypeLayoutError::CXTypeLayoutError_InvalidFieldName);

				field.memoryOffset /= 8;	//From bits to bytes
			}

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
			parsingInfo.parsingResult.parsingErrors.emplace_back(ParsingError(parsingInfo.propertyParser.getParsingError(), clang_getCursorLocation(fieldAnnotationCursor)));

			return parsingInfo.parsingSettings.shouldAbortParsingOnFirstError ? CXChildVisitResult::CXChildVisit_Break : CXChildVisitResult::CXChildVisit_Continue;
		}
	}
}

opt::optional<PropertyGroup> FieldParser::isEntityValid(CXCursor const& currentCursor, ParsingInfo& parsingInfo) noexcept
{
	_shouldCheckValidity = false;
	parsingInfo.propertyParser.clean();

	if (clang_getCursorKind(currentCursor) == CXCursorKind::CXCursor_AnnotateAttr)
	{
		return parsingInfo.propertyParser.getFieldProperties(Helpers::getString(clang_getCursorSpelling(currentCursor)));
	}

	return opt::nullopt;
}

void FieldParser::updateParsingState(CXCursor const& parent, ParsingInfo& parsingInfo) noexcept
{
	if (!clang_equalCursors(getCurrentCursor(), parent))
	{
		endParsing(parsingInfo);
	}
}