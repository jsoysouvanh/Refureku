#include "Parsing/EnumValueParser.h"

#include "Parsing/ParsingSettings.h"
#include "Parsing/PropertyParser.h"
#include "Misc/DisableWarningMacros.h"
#include "Misc/Helpers.h"

using namespace kodgen;

CXChildVisitResult EnumValueParser::parse(CXCursor const& enumValueCursor, ParsingContext const& parentContext, EnumValueParsingResult& out_result) noexcept
{
	//Make sure the cursor is compatible for the enum value parser
	assert(enumValueCursor.kind == CXCursorKind::CXCursor_EnumConstantDecl);

	//Init context
	pushContext(enumValueCursor, parentContext, out_result);

	//An enum value is always valid regardless it has properties attached or not
	out_result.parsedEnumValue.emplace(EnumValueInfo(enumValueCursor));

	clang_visitChildren(enumValueCursor, &EnumValueParser::parseNestedEntity, this);

	//Check properties validy one last time
	if (out_result.parsedEnumValue.has_value())
	{
		performFinalPropertiesCheck(*out_result.parsedEnumValue);
	}

	popContext();

	DISABLE_WARNING_PUSH
	DISABLE_WARNING_UNSCOPED_ENUM

	return (parentContext.parsingSettings->shouldAbortParsingOnFirstError && !out_result.errors.empty()) ? CXChildVisitResult::CXChildVisit_Break : CXChildVisitResult::CXChildVisit_Continue;

	DISABLE_WARNING_POP
}

CXChildVisitResult EnumValueParser::parseNestedEntity(CXCursor cursor, CXCursor /* parentCursor */, CXClientData clientData) noexcept
{
	reinterpret_cast<EnumValueParser*>(clientData)->setProperties(cursor);

	return CXChildVisitResult::CXChildVisit_Break;
}

opt::optional<PropertyGroup> EnumValueParser::getProperties(CXCursor const& cursor) noexcept
{
	ParsingContext& context = getContext();

	context.propertyParser->clean();

	if (clang_getCursorKind(cursor) == CXCursorKind::CXCursor_AnnotateAttr)
	{
		return context.propertyParser->getEnumProperties(Helpers::getString(clang_getCursorSpelling(cursor)));
	}

	return opt::nullopt;
}

void EnumValueParser::setProperties(CXCursor const& annotationCursor) noexcept
{
	ParsingContext& context = getContext();

	if (opt::optional<PropertyGroup> propertyGroup = getProperties(annotationCursor))
	{
		getParsingResult()->parsedEnumValue->properties = std::move(*propertyGroup);
	}
	else if (!context.propertyParser->getParsingErrorDescription().empty())
	{
		//Fatal parsing error occured
		context.parsingResult->errors.emplace_back(context.propertyParser->getParsingErrorDescription(), clang_getCursorLocation(annotationCursor));
	}
}

void EnumValueParser::pushContext(CXCursor const& enumValueCursor, ParsingContext const& parentContext, EnumValueParsingResult& out_result) noexcept
{
	ParsingContext newContext;

	newContext.parentContext			= &parentContext;
	newContext.rootCursor				= enumValueCursor;
	newContext.shouldCheckProperties	= true;
	newContext.propertyParser			= parentContext.propertyParser;
	newContext.parsingSettings			= parentContext.parsingSettings;
	newContext.parsingResult			= &out_result;

	contextsStack.push(std::move(newContext));
}