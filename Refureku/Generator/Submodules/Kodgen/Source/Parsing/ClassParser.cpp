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

void ClassParser::setParsingInfo(ParsingInfo* info) noexcept
{
	EntityParser::setParsingInfo(info);

	_fieldParser.setParsingInfo(info);
	_methodParser.setParsingInfo(info);
}

CXChildVisitResult ClassParser::parse(CXCursor const& cursor) noexcept
{
	if (_shouldCheckValidity)	//Check for any annotation attribute if the flag is raised
	{
		_shouldCheckValidity = false;
		return setAsCurrentEntityIfValid(cursor);
	}

	//Check for class field or method
	switch (cursor.kind)
	{
		case CXCursorKind::CXCursor_CXXFinalAttr:
			if (_parsingInfo->currentStructOrClass.has_value())
			{
				_parsingInfo->currentStructOrClass->qualifiers.isFinal = true;
			}
			break;

		case CXCursorKind::CXCursor_CXXAccessSpecifier:
			updateAccessSpecifier(cursor);
			break;

		case CXCursorKind::CXCursor_CXXBaseSpecifier:
			addToParents(cursor, *_parsingInfo);
			break;

		case CXCursorKind::CXCursor_Constructor:
			//TODO
			break;

		case CXCursorKind::CXCursor_VarDecl:	//For static fields
			[[fallthrough]];
		case CXCursorKind::CXCursor_FieldDecl:
			return parseField(cursor);

		case CXCursorKind::CXCursor_CXXMethod:
			return parseMethod(cursor);

		default:
			break;
	}

	return CXChildVisitResult::CXChildVisit_Continue;
}

CXChildVisitResult ClassParser::parseField(CXCursor fieldCursor) noexcept
{
	assert(fieldCursor.kind == CXCursorKind::CXCursor_FieldDecl || fieldCursor.kind == CXCursorKind::CXCursor_VarDecl);

	_fieldParser.startParsing(fieldCursor);

	clang_visitChildren(fieldCursor, [](CXCursor c, CXCursor, CXClientData clientData)
						{
							return reinterpret_cast<FieldParser*>(clientData)->parse(c);

						}, &_fieldParser);

	return _fieldParser.endParsing();
}

CXChildVisitResult ClassParser::parseMethod(CXCursor methodCursor) noexcept
{
	assert(methodCursor.kind == CXCursorKind::CXCursor_CXXMethod);

	_methodParser.startParsing(methodCursor);

	clang_visitChildren(methodCursor, [](CXCursor c, CXCursor, CXClientData clientData)
						{
							return reinterpret_cast<MethodParser*>(clientData)->parse(c);

						}, &_methodParser);

	return _methodParser.endParsing();
}

CXChildVisitResult ClassParser::setAsCurrentEntityIfValid(CXCursor const& classAnnotationCursor) noexcept
{
	if (opt::optional<PropertyGroup> propertyGroup = isEntityValid(classAnnotationCursor))
	{
		_parsingInfo->currentStructOrClass.emplace(StructClassInfo(getCurrentCursor(), std::move(*propertyGroup), std::move(_structOrClass)));
		initClassInfos(_parsingInfo->currentStructOrClass.value());

		return CXChildVisitResult::CXChildVisit_Recurse;
	}
	else
	{
		if (_parsingInfo->propertyParser.getParsingError() != EParsingError::Count)
		{
			_parsingInfo->parsingResult.parsingErrors.emplace_back(ParsingError(_parsingInfo->propertyParser.getParsingError(), clang_getCursorLocation(classAnnotationCursor)));
		}

		return CXChildVisitResult::CXChildVisit_Break;
	}
}

void ClassParser::initClassInfos(StructClassInfo& toInit) const noexcept
{
	CXType		classType	= clang_getCursorType(getCurrentCursor());
	std::string fullName	= Helpers::getString(clang_getTypeSpelling(classType));

	size_t namespacePos = fullName.find_last_of("::");

	if (namespacePos != std::string::npos)
		toInit.nameSpace = std::string(fullName.cbegin(), fullName.cbegin() + namespacePos - 1);
}

opt::optional<PropertyGroup> ClassParser::isEntityValid(CXCursor const& currentCursor) noexcept
{
	_parsingInfo->propertyParser.clean();

	if (clang_getCursorKind(currentCursor) == CXCursorKind::CXCursor_AnnotateAttr)
	{
		switch (_structOrClass)
		{
			case EntityInfo::EType::Class:
				return _parsingInfo->propertyParser.getClassProperties(Helpers::getString(clang_getCursorSpelling(currentCursor)));
				break;

			case EntityInfo::EType::Struct:
				return _parsingInfo->propertyParser.getStructProperties(Helpers::getString(clang_getCursorSpelling(currentCursor)));
				break;

			default:
				assert(false);	//Should never pass here
		}
	}

	return opt::nullopt;
}

void ClassParser::startClassParsing(CXCursor const& currentCursor)	noexcept
{
	EntityParser::startParsing(currentCursor);

	_parsingInfo->accessSpecifier	= EAccessSpecifier::Private;
	_structOrClass					= EntityInfo::EType::Class;
}

void ClassParser::startStructParsing(CXCursor const& currentCursor)	noexcept
{
	EntityParser::startParsing(currentCursor);

	_parsingInfo->accessSpecifier	= EAccessSpecifier::Public;
	_structOrClass					= EntityInfo::EType::Struct;
}

CXChildVisitResult ClassParser::endParsing()	noexcept
{
	_parsingInfo->accessSpecifier	= EAccessSpecifier::Invalid;
	_structOrClass					= EntityInfo::EType::Count;

	_parsingInfo->flushCurrentStructOrClass();

	return EntityParser::endParsing();
}

void ClassParser::updateAccessSpecifier(CXCursor const& cursor) const noexcept
{
	_parsingInfo->accessSpecifier = static_cast<EAccessSpecifier>(clang_getCXXAccessSpecifier(cursor));
}

void ClassParser::addToParents(CXCursor cursor, ParsingInfo& parsingInfo) const noexcept
{
	assert(clang_getCursorKind(cursor) == CXCursorKind::CXCursor_CXXBaseSpecifier);

	if (parsingInfo.currentStructOrClass.has_value())
	{
		parsingInfo.currentStructOrClass->parents.emplace_back(StructClassInfo::ParentInfo{ static_cast<EAccessSpecifier>(clang_getCXXAccessSpecifier(cursor)), TypeInfo(clang_getCursorType(cursor)) });
	}
}