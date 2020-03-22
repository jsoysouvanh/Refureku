#pragma once

#include <vector>

#include "Parsing/ParsingError.h"
#include "Parsing/ParsingSettings.h"

#include "InfoStructures/StructClassInfo.h"
#include "InfoStructures/EnumInfo.h"

namespace kodgen
{
	struct ParsingResult
	{
		/**
		*	All parsed entities
		*/
		std::vector<StructClassInfo>	classes;
		std::vector<StructClassInfo>	structs;
		std::vector<EnumInfo>			enums;
		
		/**
		*	Errors encountered during parsing
		*/
		std::vector<ParsingError>		parsingErrors;
	};
}