/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Parsing/ParsingResults/ParsingResultBase.h"
#include "InfoStructures/FieldInfo.h"
#include "Misc/Optional.h"

namespace kodgen
{
	struct FieldParsingResult : public ParsingResultBase
	{
		public:
			/** Information on the parsed field. */
			opt::optional<FieldInfo>	parsedField	= opt::nullopt;
	};
}