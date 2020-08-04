/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "Kodgen/Misc/FundamentalTypes.h"
#include "Kodgen/InfoStructures/TypeInfo.h"

namespace kodgen
{
	struct MethodParamInfo
	{
		public:
			/** Parameter type */
			TypeInfo	type;

			/** Parameter name. Can be empty if no name. */
			std::string	name;
	};
}