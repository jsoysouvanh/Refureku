#pragma once

#include <string>

#include "Misc/FundamentalTypes.h"

namespace kodgen
{
	enum class EFileGenerationError : uint16
	{
		/**
		*	FileGenerator::outputDirectory was not specified.
		*/
		UnspecifiedOutputDirectory,

		/**
		*	The output directory was specified but the system failed to create it.
		*/
		InvalidOutputDirectory,

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