/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <unordered_set>

#include "Kodgen/Properties/PropertyParsingSettings.h"
#include "Kodgen/Misc/Filesystem.h"

namespace kodgen
{
	struct ParsingSettings
	{
		public:
			/** Settings used when parsing C++ entities. */
			PropertyParsingSettings					propertyParsingSettings;

			/** If set to true, will parse all C++ entities, whether they are annotated or not. */
			bool									shouldParseAllEntities			= false;

			/**
			*	Should the parsing be aborted when an error is encountered or not
			*	If set to false, errors will be collected for the whole parsing
			*/
			bool									shouldAbortParsingOnFirstError	= true;

			/**
			*	Include directories of the project which must be known for accurate parsing.
			*	It basically corresponds to the list of paths specified with the -I argument
			*	when compiling.
			*/
			std::unordered_set<fs::path, PathHash>	projectIncludeDirectories;
	};
}