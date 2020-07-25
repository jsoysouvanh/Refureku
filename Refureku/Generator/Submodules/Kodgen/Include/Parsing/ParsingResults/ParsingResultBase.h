/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

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