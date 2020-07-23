#pragma once

#include "Parsing/ParsingResults/ParsingResultBase.h"
#include "InfoStructures/EnumValueInfo.h"
#include "Misc/Optional.h"

namespace kodgen
{
	struct EnumValueParsingResult : public ParsingResultBase
	{
		public:
			/** Information on the parsed enum value. */
			opt::optional<EnumValueInfo>	parsedEnumValue;
	};
}