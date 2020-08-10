#include "Kodgen/Parsing/EnumParser.h"

#include <cassert>

#include "Kodgen/Parsing/ParsingSettings.h"
#include "Kodgen/Parsing/PropertyParser.h"
#include "Kodgen/Misc/Helpers.h"

using namespace kodgen;

CXChildVisitResult EnumParser::parse(CXCursor const& enumCursor, ParsingContext const& parentContext, EnumParsingResult& out_result) noexcept
{
	//Make sure the cursor is compatible for the enum parser
	assert(enumCursor.kind == CXCursorKind::CXCursor_EnumDecl);

	//Init context
	ParsingContext& context = pushContext(enumCursor, parentContext, out_result);

	if (!clang_visitChildren(enumCursor, &EnumParser::parseNestedEntity, this) && context.shouldCheckProperties)
	{
		//If we reach this point, the cursor had no child (no annotation)
		//Check if the parent has the shouldParseAllNested flag set
		if (shouldParseCurrentEntity())
		{
			getParsingResult()->parsedEnum.emplace(enumCursor, PropertyGroup());
		}
	}

	//Check properties validy one last time
	if (out_result.parsedEnum.has_value())
	{
		performFinalPropertiesCheck(*out_result.parsedEnum);
	}

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

		if (parser->shouldParseCurrentEntity() && cursor.kind != CXCursorKind::CXCursor_AnnotateAttr)
		{
			//Make it valid right away so init the result
			parser->getParsingResult()->parsedEnum.emplace(context.rootCursor, PropertyGroup());
		}
		else
		{
			//Set parsed enum in result if it is valid
			return parser->setParsedEntity(cursor);
		}
	}
	
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

EnumValueParsingResult EnumParser::parseEnumValue(CXCursor const& enumValueCursor, CXChildVisitResult& out_visitResult) noexcept
{
	EnumValueParsingResult enumValueResult;

	out_visitResult	= _enumValueParser.parse(enumValueCursor, getContext(), enumValueResult);

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
		//Set the parsing entity in the result and update the shouldParseAllNested flag in the context
		updateShouldParseAllNested(getParsingResult()->parsedEnum.emplace(context.rootCursor, std::move(*propertyGroup)));

		return CXChildVisitResult::CXChildVisit_Recurse;
	}
	else
	{
		if (!context.propertyParser->getParsingErrorDescription().empty())
		{
			context.parsingResult->errors.emplace_back(ParsingError(context.propertyParser->getParsingErrorDescription(), clang_getCursorLocation(annotationCursor)));
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

	getParsingResult()->appendResultErrors(result);
}

ParsingContext& EnumParser::pushContext(CXCursor const& enumCursor, ParsingContext const& parentContext, EnumParsingResult& out_result) noexcept
{
	ParsingContext newContext;

	newContext.parentContext			= &parentContext;
	newContext.rootCursor				= enumCursor;
	newContext.shouldCheckProperties	= true;
	newContext.propertyParser			= parentContext.propertyParser;
	newContext.parsingSettings			= parentContext.parsingSettings;
	newContext.parsingResult			= &out_result;

	contextsStack.push(std::move(newContext));

	return contextsStack.top();
}