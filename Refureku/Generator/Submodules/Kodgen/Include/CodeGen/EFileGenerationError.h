#pragma once

#include <string>

#include "Misc/FundamentalTypes.h"

namespace kodgen
{
	enum class EFileGenerationError : uint8
	{
		/**
		*	The GenTemplate (defined in FileGenerator::codeTemplateMainComplexPropertyName) main complex property is missing
		*	and no default class/enum generated code template was provided to the FileGenerator
		*/
		MissingGeneratedCodeTemplateComplexProperty,

		/**
		*	No generated code template was provided (GenTemplate sub property)
		*	One is expected
		*/
		NoGeneratedCodeTemplateProvided,

		/**
		*	Too many generated code template were provided (GenTemplate sub property)
		*	One is expected
		*/
		TooManyGeneratedCodeTemplateProvided,

		/**
		*	An unregistered generated code template were provided.
		*	Make sure it is not a syntax miss, or add it to the FileGenerator before
		*/
		UnregisteredGeneratedCodeTemplateProvided,

		/**
		*	Might be used in the future.
		*	Is also used as a no-error value
		*/
		Count
	};

	std::string toString(EFileGenerationError error) noexcept;
}