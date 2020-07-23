#pragma once

#include "Parsing/ParsingResults/ParsingResultBase.h"
#include "InfoStructures/StructClassInfo.h"
#include "Misc/Optional.h"

namespace kodgen
{
	struct ClassParsingResult : public ParsingResultBase
	{
		public:
			/** Information on the parsed struct/class. */
			opt::optional<StructClassInfo>	parsedClass	= opt::nullopt;
	};
}