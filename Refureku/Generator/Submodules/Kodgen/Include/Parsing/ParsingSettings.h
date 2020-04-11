#pragma once

#include <string>
#include <unordered_set>

#include "Properties/PropertyParsingSettings.h"

namespace kodgen
{
	struct ParsingSettings
	{
		PropertyParsingSettings			propertyParsingSettings;

		/**
		*	Should the parsing be aborted when an error is encountered or not
		*	If set to false, errors will be collected for the whole parsing
		*/
		bool							shouldAbortParsingOnFirstError = true;

		/**
		*	Include directories of the project which must be known for accurate parsing.
		*	It basically corresponds to the list of paths specified with the -I argument
		*	when compiling.
		*/
		std::unordered_set<std::string>	projectIncludeDirectories;
	};
}