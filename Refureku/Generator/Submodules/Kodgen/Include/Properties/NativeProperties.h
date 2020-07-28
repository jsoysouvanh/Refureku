/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

namespace kodgen
{
	class NativeProperties
	{
		public:
			/** Property used to automatically parse all nested entities without having to annotate them. */
			inline static std::string const	parseAllNestedProperty = "ParseAllNested";

			NativeProperties()							= delete;
			NativeProperties(NativeProperties const&)	= delete;
			NativeProperties(NativeProperties&&)		= delete;
			~NativeProperties()							= delete;
	};
}