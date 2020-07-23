#pragma once

#include <clang-c/Index.h>

#include "InfoStructures/EnumInfo.h"
#include "Misc/EAccessSpecifier.h"

namespace kodgen
{
	class NestedEnumInfo : public EnumInfo
	{
		public:
			/** Access specifier of this nested struct/class. */
			EAccessSpecifier	accessSpecifier;

			NestedEnumInfo()													= default;
			NestedEnumInfo(EnumInfo&& base, EAccessSpecifier accessSpecifier)	noexcept;
			NestedEnumInfo(NestedEnumInfo const&)								= default;
			NestedEnumInfo(NestedEnumInfo&&)									= default;
			~NestedEnumInfo()													= default;
	};
}