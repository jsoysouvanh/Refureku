/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Kodgen/Parsing/ParsingResults/ParsingResultBase.h"
#include "Kodgen/InfoStructures/StructClassInfo.h"
#include "Kodgen/Misc/Optional.h"

namespace kodgen
{
	struct ClassParsingResult : public ParsingResultBase
	{
		public:
			/** Information on the parsed struct/class. */
			opt::optional<StructClassInfo>	parsedClass	= opt::nullopt;
	};
}