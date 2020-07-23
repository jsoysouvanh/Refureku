#pragma once

#include <vector>

#include "Parsing/ParsingError.h"
#include "Parsing/ParsingSettings.h"
#include "Parsing/ParsingResults/ParsingResultBase.h"
#include "Misc/Filesystem.h"

#include "InfoStructures/NamespaceInfo.h"
#include "InfoStructures/StructClassInfo.h"
#include "InfoStructures/EnumInfo.h"

namespace kodgen
{
	struct FileParsingResult : public ParsingResultBase
	{
		/** Path to the parsed file. */
		fs::path						parsedFile;

		/** All parsed entities contained in this file. */
		std::vector<NamespaceInfo>		namespaces;
		std::vector<StructClassInfo>	classes;
		std::vector<StructClassInfo>	structs;
		std::vector<EnumInfo>			enums;

		//TODO: Global functions
		//TODO: Global fields
	};
}