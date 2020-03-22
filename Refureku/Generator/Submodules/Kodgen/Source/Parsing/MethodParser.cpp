#include "Parsing/MethodParser.h"

#include <assert.h>

#include "Misc/Helpers.h"
#include "InfoStructures/MethodParamInfo.h"

using namespace kodgen;

CXChildVisitResult MethodParser::parse(CXCursor const& cursor, ParsingInfo& parsingInfo) noexcept
{
	//Check for any annotation attribute if the flag is raised
	if (_shouldCheckValidity)
	{
		return setAsCurrentEntityIfValid(cursor, parsingInfo);
	}

	if (!parsingInfo.currentStructOrClass.has_value())
	{
		return CXChildVisitResult::CXChildVisit_Continue;
	}

	switch (clang_getCursorKind(cursor))
	{
		case CXCursorKind::CXCursor_CXXFinalAttr:
			parsingInfo.currentStructOrClass->methods.at(parsingInfo.accessSpecifier).back().qualifiers.isFinal = true;
			break;

		case CXCursorKind::CXCursor_CXXOverrideAttr:
			parsingInfo.currentStructOrClass->methods.at(parsingInfo.accessSpecifier).back().qualifiers.isOverride = true;
			break;

		case CXCursorKind::CXCursor_ParmDecl:
			parsingInfo.currentStructOrClass->methods.at(parsingInfo.accessSpecifier).back().parameters.emplace_back(MethodParamInfo{ TypeInfo(clang_getCursorType(cursor)), Helpers::getString(clang_getCursorDisplayName(cursor)) });
			break;

		default:
			std::cout << "Unknown method sub cursor: " << Helpers::getString(clang_getCursorKindSpelling(clang_getCursorKind(cursor))) << std::endl;
			break;
	}

	return CXChildVisitResult::CXChildVisit_Recurse;
}

CXChildVisitResult MethodParser::setAsCurrentEntityIfValid(CXCursor const& methodAnnotationCursor, ParsingInfo& parsingInfo) noexcept
{
	if (opt::optional<PropertyGroup> propertyGroup = isEntityValid(methodAnnotationCursor, parsingInfo))
	{
		if (parsingInfo.currentStructOrClass.has_value())
		{
			MethodInfo& methodInfo = parsingInfo.currentStructOrClass->methods.at(parsingInfo.accessSpecifier).emplace_back(MethodInfo(Helpers::getString(clang_getCursorDisplayName(getCurrentCursor())), std::move(*propertyGroup)));
			setupMethod(getCurrentCursor(), methodInfo);

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
			parsingInfo.parsingResult.parsingErrors.emplace_back(ParsingError(parsingInfo.propertyParser.getParsingError(), clang_getCursorLocation(methodAnnotationCursor)));

			return parsingInfo.parsingSettings.shouldAbortParsingOnFirstError ? CXChildVisitResult::CXChildVisit_Break : CXChildVisitResult::CXChildVisit_Continue;
		}
	}
}

void MethodParser::setupMethod(CXCursor const& methodCursor, MethodInfo& methodInfo) noexcept
{
	CXType methodType = clang_getCursorType(methodCursor);

	assert(methodType.kind == CXTypeKind::CXType_FunctionProto);

	//Define return type
	methodInfo.returnType =	TypeInfo(clang_getResultType(methodType));

	//Define method qualifiers
	if (clang_CXXMethod_isDefaulted(methodCursor))
	{
		methodInfo.qualifiers.isDefault = true;
	}
	if (clang_CXXMethod_isStatic(methodCursor))
	{
		methodInfo.qualifiers.isStatic = true;
	}
	if (clang_CXXMethod_isVirtual(methodCursor))
	{
		methodInfo.qualifiers.isVirtual = true;
	}
	if (clang_CXXMethod_isPureVirtual(methodCursor))
	{
		methodInfo.qualifiers.isPureVirtual = true;
	}
	if (clang_CXXMethod_isConst(methodCursor))
	{
		methodInfo.qualifiers.isConst = true;
	}
	if (clang_Cursor_isFunctionInlined(methodCursor))
	{
		methodInfo.qualifiers.isInline = true;
	}
}

opt::optional<PropertyGroup> MethodParser::isEntityValid(CXCursor const& currentCursor, ParsingInfo& parsingInfo) noexcept
{
	_shouldCheckValidity = false;
	parsingInfo.propertyParser.clean();

	if (clang_getCursorKind(currentCursor) == CXCursorKind::CXCursor_AnnotateAttr)
	{
		return parsingInfo.propertyParser.getMethodProperties(Helpers::getString(clang_getCursorSpelling(currentCursor)));
	}

	return opt::nullopt;
}

void MethodParser::updateParsingState(CXCursor const& parent, ParsingInfo& parsingInfo) noexcept
{
	if (!clang_equalCursors(getCurrentCursor(), parent))
	{
		endParsing(parsingInfo);
	}
}