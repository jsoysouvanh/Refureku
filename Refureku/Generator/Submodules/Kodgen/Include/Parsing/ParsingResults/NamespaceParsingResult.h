#pragma once

#include "Parsing/ParsingResults/ParsingResultBase.h"
#include "InfoStructures/NamespaceInfo.h"
#include "Misc/Optional.h"

namespace kodgen
{
	struct NamespaceParsingResult : public ParsingResultBase
	{
		public:
			/** Information on the parsed namespace. */
			opt::optional<NamespaceInfo> parsedNamespace = opt::nullopt;
	};
}