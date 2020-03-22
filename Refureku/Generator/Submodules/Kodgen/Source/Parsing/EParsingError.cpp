#include "Parsing/EParsingError.h"

using namespace kodgen;

std::string kodgen::toString(EParsingError error) noexcept
{
	std::string result;

	switch (error)
	{
		case EParsingError::WrongPropertyMacroUsed:
			result = "WrongPropertyMacroUsed";
			break;

		case EParsingError::SubPropertyEndEncloserMissing:
			result = "SubPropertyEndEncloserMissing";
			break;

		case EParsingError::PropertySeparatorMissing:
			result = "PropertySeparatorMissing";
			break;

		case EParsingError::InvalidSimpleProperty:
			result = "InvalidSimpleProperty";
			break;

		case EParsingError::InvalidComplexMainProperty:
			result = "InvalidComplexMainProperty";
			break;

		case EParsingError::InvalidComplexSubProperty:
			result = "InvalidComplexSubProperty";
			break;

		case EParsingError::InexistantFile:
			result = "InexistantFile";
			break;

		case EParsingError::TranslationUnitInitFailed:
			result = "TranslationUnitInitFailed";
			break;

		case EParsingError::Count:
			result = "Count";
			break;
	}

	return result;
}