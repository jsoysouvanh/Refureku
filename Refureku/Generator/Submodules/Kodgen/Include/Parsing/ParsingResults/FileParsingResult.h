/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>

#include "Parsing/ParsingError.h"
#include "Parsing/ParsingSettings.h"
#include "Parsing/ParsingResults/ParsingResultBase.h"
#include "InfoStructures/NamespaceInfo.h"
#include "InfoStructures/StructClassInfo.h"
#include "InfoStructures/EnumInfo.h"
#include "Misc/Filesystem.h"

namespace kodgen
{
	struct FileParsingResult : public ParsingResultBase
	{
		/** Path to the parsed file. */
		fs::path						parsedFile;

		/** All namespaces contained directly under file level. */
		std::vector<NamespaceInfo>		namespaces;

		/** All classes contained directly under file level. */
		std::vector<StructClassInfo>	classes;

		/** All structs contained directly under file level. */
		std::vector<StructClassInfo>	structs;

		/** All enums contained directly under file level. */
		std::vector<EnumInfo>			enums;

		//TODO: Global functions
		//TODO: Global fields
	};
}