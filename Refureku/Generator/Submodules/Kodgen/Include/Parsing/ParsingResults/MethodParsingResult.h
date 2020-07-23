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