#include "InfoStructures/ParsingInfo.h"

#include <cassert>

using namespace kodgen;

bool ParsingInfo::hasErrorOccured() const noexcept
{
	return !parsingResult.parsingErrors.empty();
}

bool ParsingInfo::flushCurrentStructOrClass() noexcept
{
	if (currentStructOrClass.has_value())
	{
		switch (currentStructOrClass->entityType)
		{
			case EntityInfo::EType::Class:
				parsingResult.classes.emplace_back(std::move(currentStructOrClass.value()));
				break;

			case EntityInfo::EType::Struct:
				parsingResult.structs.emplace_back(std::move(currentStructOrClass.value()));
				break;

			default:
				assert(false);	//Should never pass here
		}

		currentStructOrClass.reset();

		return true;
	}

	return false;
}

bool ParsingInfo::flushCurrentEnum() noexcept
{
	if (currentEnum.has_value())
	{
		parsingResult.enums.emplace_back(std::move(currentEnum.value()));
		currentEnum.reset();

		return true;
	}

	return false;
}

void ParsingInfo::reset() noexcept
{
	propertyParser.setup(&parsingSettings.propertyParsingSettings);

	accessSpecifier			= EAccessSpecifier::Private;

	currentStructOrClass	= std::nullopt;
	currentEnum				= std::nullopt;

	parsingResult.classes.clear();
	parsingResult.enums.clear();
	parsingResult.parsingErrors.clear();
}