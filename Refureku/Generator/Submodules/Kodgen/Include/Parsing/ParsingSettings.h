#pragma once

#include "Properties/PropertyParsingSettings.h"

namespace kodgen
{
	struct ParsingSettings
	{
		PropertyParsingSettings	propertyParsingSettings;

		/**
		*	Should the parsing be aborted when an error is encountered or not
		*	If set to false, errors will be collected for the whole parsing
		*/
		bool					shouldAbortParsingOnFirstError = true;
	};
}