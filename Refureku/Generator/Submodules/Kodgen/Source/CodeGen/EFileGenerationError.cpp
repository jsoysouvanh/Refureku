#include "CodeGen/EFileGenerationError.h"

std::string kodgen::toString(EFileGenerationError error) noexcept
{
	std::string result;

	switch (error)
	{
		case EFileGenerationError::MissingGeneratedCodeTemplateComplexProperty:
			result = "MissingGeneratedCodeTemplateComplexProperty";
			break;

		case EFileGenerationError::NoGeneratedCodeTemplateProvided:
			result = "NoGeneratedCodeTemplateProvided";
			break;

		case EFileGenerationError::TooManyGeneratedCodeTemplateProvided:
			result = "TooManyGeneratedCodeTemplateProvided";
			break;

		case EFileGenerationError::UnregisteredGeneratedCodeTemplateProvided:
			result = "UnregisteredGeneratedCodeTemplateProvided";
			break;

		case EFileGenerationError::Count:
			result = "Count";
			break;
	}

	return result;
}