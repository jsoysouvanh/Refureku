#pragma once

#include <vector>

#include "Parsing/ParsingError.h"

namespace kodgen
{
	struct ParsingResultBase
	{
		public:
			/** List of errors that happened during parsing */
			std::vector<ParsingError>	errors;
	};
}