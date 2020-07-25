/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Parsing/ParsingResults/ParsingResultBase.h"
#include "InfoStructures/MethodInfo.h"
#include "Misc/Optional.h"

namespace kodgen
{
	struct MethodParsingResult : public ParsingResultBase
	{
		public:
			/** Information on the parsed method. */
			opt::optional<MethodInfo>	parsedMethod	= opt::nullopt;
	};
}