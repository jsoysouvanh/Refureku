#include "Parsing/EnumParser.h"

#include <cassert>

#include "Parsing/ParsingSettings.h"
#include "Parsing/PropertyParser.h"
#include "Misc/Helpers.h"

using namespace kodgen;

CXChildVisitResult EnumParser::parse(CXCursor const& enumCursor, ParsingContext const& parentContext, EnumParsingResult& out_result) noexcept
{
	//Make sure the cursor is compatible for the enum parser
	assert(enumCursor.kind == CXCursorKind::CXCursor_EnumDecl);

	//Init context
	pushContext(enumCursor, parentContext, out_result);

	clang_visitChildren(enumCursor, &EnumParser::parseNestedEntity, this);

	popContext();

	DISABLE_WARNING_PUSH
	DISABLE_WARNING_UNSCOPED_ENUM

	return (parentContext.parsingSettings->shouldAbortParsingOnFirstError && !out_result.errors.empty()) ? CXChildVisitResult::CXChildVisit_Break : CXChildVisitResult::CXChildVisit_Continue;

	DISABLE_WARNING_POP
}

CXChildVisitResult EnumParser::parseNestedEntity(CXCursor cursor, CXCursor /* parentCursor */, CXClientData clientData) noexcept
{
	EnumParser*		parser	= reinterpret_cast<EnumParser*>(clientData);
	ParsingContext&	context = parser->getContext();

	if (context.shouldCheckProperties)
	{
		context.shouldCheckProperties = false;

		//Set parsed enum in result if it is valid
		return parser->setParsedEntity(cursor);
	}
	else
	{
		CXChildVisitResult visitResult = CXChildVisitResult::CXChildVisit_Continue;

		switch (cursor.kind)
		{
			case CXCursorKind::CXCursor_EnumConstantDecl:
				parser->addEnumValueResult(parser->parseEnumValue(cursor, visitResult));
				break;
	
			default:
				break;
		}
	
		return visitResult;
	}
}

EnumValueParsingResult EnumParser::parseEnumValue(CXCursor const& enumValueCursor, CXChildVisitResult& out_visitResult) noexcept
{
	EnumValueParsingResult enumValueResult;

	out_visitResult	= enumValueParser.parse(enumValueCursor, getContext(), enumValueResult);

	return enumValueResult;
}

opt::optional<PropertyGroup> EnumParser::getProperties(CXCursor const& cursor) noexcept
{
	ParsingContext& context = getContext();

	context.propertyParser->clean();

	if (clang_getCursorKind(cursor) == CXCursorKind::CXCursor_AnnotateAttr)
	{
		return context.propertyParser->getEnumProperties(Helpers::getString(clang_getCursorSpelling(cursor)));
	}

	return opt::nullopt;
}

CXChildVisitResult EnumParser::setParsedEntity(CXCursor const& annotationCursor) noexcept
{
	ParsingContext& context = getContext();

	if (opt::optional<PropertyGroup> propertyGroup = getProperties(annotationCursor))
	{
		getParsingResult()->parsedEnum.emplace(EnumInfo(context.rootCursor, std::move(*propertyGroup)));

		return CXChildVisitResult::CXChildVisit_Recurse;
	}
	else
	{
		if (context.propertyParser->getParsingError() != EParsingError::Count)
		{
			context.parsingResult->errors.emplace_back(ParsingError(context.propertyParser->getParsingError(), clang_getCursorLocation(annotationCursor)));
		}

		return CXChildVisitResult::CXChildVisit_Break;
	}
}

void EnumParser::addEnumValueResult(EnumValueParsingResult&& result) noexcept
{
	ParsingContext& context = getContext();

	if (result.parsedEnumValue.has_value() && getParsingResult()->parsedEnum.has_value())
	{
		getParsingResult()->parsedEnum->enumValues.emplace_back(std::move(result.parsedEnumValue).value());
	}

	//Append errors if any
	if (!result.errors.empty())
	{
		context.parsingResult->errors.insert(getParsingResult()->errors.cend(), std::make_move_iterator(result.errors.cbegin()), std::make_move_iterator(result.errors.cend()));
	}
}

void EnumParser::pushContext(CXCursor const& enumCursor, ParsingContext const& parentContext, EnumParsingResult& out_result) noexcept
{
	ParsingContext newContext;

	newContext.parentContext			= &parentContext;
	newContext.rootCursor				= enumCursor;
	newContext.shouldCheckProperties	= true;
	newContext.propertyParser			= parentContext.propertyParser;
	newContext.parsingSettings			= parentContext.parsingSettings;
	newContext.parsingResult			= &out_result;

	contextsStack.push(std::move(newContext));
}