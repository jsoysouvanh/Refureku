#include "Parsing/ClassParser.h"

#include <cassert>

#include "Misc/Helpers.h"

using namespace kodgen;

void ClassParser::reset() noexcept
{
	EntityParser::reset();

	_fieldParser.reset();
	_methodParser.reset();

	_structOrClass = EntityInfo::EType::Count;
}

CXChildVisitResult ClassParser::parse(CXCursor const& cursor, ParsingInfo& parsingInfo) noexcept
{
	if (_fieldParser.getParsingLevel())
	{
		return _fieldParser.parse(cursor, parsingInfo);
	}
	else if (_methodParser.getParsingLevel())
	{
		return _methodParser.parse(cursor, parsingInfo);
	}
	else if (_shouldCheckValidity)	//Check for any annotation attribute if the flag is raised
	{
		_shouldCheckValidity = false;
		return setAsCurrentEntityIfValid(cursor, parsingInfo);
	}

	//Check for class field or method
	switch (clang_getCursorKind(cursor))
	{
		case CXCursorKind::CXCursor_CXXFinalAttr:
			if (parsingInfo.currentStructOrClass.has_value())
			{
				parsingInfo.currentStructOrClass->qualifiers.isFinal = true;
			}
			break;

		case CXCursorKind::CXCursor_CXXAccessSpecifier:
			updateAccessSpecifier(cursor, parsingInfo);
			break;

		case CXCursorKind::CXCursor_CXXBaseSpecifier:
			addToParents(cursor, parsingInfo);
			break;

		case CXCursorKind::CXCursor_VarDecl:	//For static fields
			[[fallthrough]];
		case CXCursorKind::CXCursor_FieldDecl:
			_fieldParser.startParsing(cursor);
			break;

		case CXCursorKind::CXCursor_CXXMethod:
			_methodParser.startParsing(cursor);
			break;

		default:
			return CXChildVisitResult::CXChildVisit_Continue;
	}

	return CXChildVisitResult::CXChildVisit_Recurse;
}

CXChildVisitResult ClassParser::setAsCurrentEntityIfValid(CXCursor const& classAnnotationCursor, ParsingInfo& parsingInfo) noexcept
{
	if (opt::optional<PropertyGroup> propertyGroup = isEntityValid(classAnnotationCursor, parsingInfo))
	{
		parsingInfo.currentStructOrClass.emplace(StructClassInfo(Helpers::getString(clang_getCursorDisplayName(getCurrentCursor())), std::move(*propertyGroup), std::move(_structOrClass)));

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

opt::optional<PropertyGroup> ClassParser::isEntityValid(CXCursor const& currentCursor, ParsingInfo& parsingInfo) noexcept
{
	parsingInfo.propertyParser.clean();

	if (clang_getCursorKind(currentCursor) == CXCursorKind::CXCursor_AnnotateAttr)
	{
		switch (_structOrClass)
		{
			case EntityInfo::EType::Class:
				return parsingInfo.propertyParser.getClassProperties(Helpers::getString(clang_getCursorSpelling(currentCursor)));
				break;

			case EntityInfo::EType::Struct:
				return parsingInfo.propertyParser.getStructProperties(Helpers::getString(clang_getCursorSpelling(currentCursor)));
				break;

			default:
				assert(false);	//Should never pass here
		}
	}

	return opt::nullopt;
}

void ClassParser::startClassParsing(CXCursor const& currentCursor, ParsingInfo& parsingInfo)	noexcept
{
	EntityParser::startParsing(currentCursor);

	parsingInfo.accessSpecifier		= EAccessSpecifier::Private;
	_structOrClass					= EntityInfo::EType::Class;
}

void ClassParser::startStructParsing(CXCursor const& currentCursor, ParsingInfo& parsingInfo)	noexcept
{
	EntityParser::startParsing(currentCursor);

	parsingInfo.accessSpecifier		= EAccessSpecifier::Public;
	_structOrClass					= EntityInfo::EType::Struct;
}

void ClassParser::endParsing(ParsingInfo& parsingInfo)	noexcept
{
	EntityParser::endParsing(parsingInfo);

	parsingInfo.accessSpecifier		= EAccessSpecifier::Invalid;
	_structOrClass					= EntityInfo::EType::Count;

	parsingInfo.flushCurrentStructOrClass();
}

void ClassParser::updateParsingState(CXCursor const& parent, ParsingInfo& parsingInfo) noexcept
{
	//Check if we're not parsing a field anymore
	if (_fieldParser.getParsingLevel())
	{
		_fieldParser.updateParsingState(parent, parsingInfo);
	}
	//Check if we're not parsing a method anymore
	else if (_methodParser.getParsingLevel())
	{
		_methodParser.updateParsingState(parent, parsingInfo);
	}

	/**
	*	Check if we're finishing parsing a class
	*/
	if (clang_equalCursors(clang_getCursorSemanticParent(getCurrentCursor()), parent))
	{
		endParsing(parsingInfo);
	}
}

void ClassParser::updateAccessSpecifier(CXCursor const& cursor, ParsingInfo& parsingInfo) const noexcept
{
	parsingInfo.accessSpecifier = static_cast<EAccessSpecifier>(clang_getCXXAccessSpecifier(cursor));
}

void ClassParser::addToParents(CXCursor cursor, ParsingInfo& parsingInfo) const noexcept
{
	assert(clang_getCursorKind(cursor) == CXCursorKind::CXCursor_CXXBaseSpecifier);

	if (parsingInfo.currentStructOrClass.has_value())
	{
		parsingInfo.currentStructOrClass->parents.emplace_back(StructClassInfo::ParentInfo{ static_cast<EAccessSpecifier>(1 << clang_getCXXAccessSpecifier(cursor)), TypeInfo(clang_getCursorType(cursor)) });
	}
}