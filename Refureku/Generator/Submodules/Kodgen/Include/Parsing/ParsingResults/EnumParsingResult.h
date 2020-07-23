#pragma once

#include "Parsing/ParsingResults/ParsingResultBase.h"
#include "InfoStructures/EnumInfo.h"
#include "Misc/Optional.h"

namespace kodgen
{
	struct EnumParsingResult : public ParsingResultBase
	{
		public:
			/** Information on the parsed enum. */
			opt::optional<EnumInfo>	parsedEnum	= opt::nullopt;
	};
}