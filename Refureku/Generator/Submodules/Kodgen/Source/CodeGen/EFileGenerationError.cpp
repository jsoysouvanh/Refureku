#include "Kodgen/CodeGen/EFileGenerationError.h"

std::string kodgen::toString(EFileGenerationError error) noexcept
{
	std::string result;

	switch (error)
	{
		case EFileGenerationError::UnspecifiedOutputDirectory:
			result = "UnspecifiedOutputDirectory";
			break;

		case EFileGenerationError::InvalidOutputDirectory:
			result = "InvalidOutputDirectory";
			break;

		case EFileGenerationError::NoGeneratedCodeTemplateProvided:
			result = "NoGeneratedCodeTemplateProvided";
			break;

		case EFileGenerationError::TooManyGeneratedCodeTemplateProvided:
			result = "TooManyGeneratedCodeTemplateProvided";
			break;

		case EFileGenerationError::Count:
			result = "Count";
			break;
	}

	return result;
}