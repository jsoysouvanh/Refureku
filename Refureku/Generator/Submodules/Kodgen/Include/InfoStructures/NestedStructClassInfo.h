#pragma once

#include <clang-c/Index.h>

#include "InfoStructures/StructClassInfo.h"
#include "Misc/EAccessSpecifier.h"

namespace kodgen
{
	class NestedStructClassInfo : public StructClassInfo
	{
		public:
			/** Access specifier of this nested struct/class. */
			EAccessSpecifier	accessSpecifier;

			NestedStructClassInfo()															= default;
			NestedStructClassInfo(StructClassInfo&& base, EAccessSpecifier accessSpecifier)	noexcept;
			NestedStructClassInfo(NestedStructClassInfo const&)								= default;
			NestedStructClassInfo(NestedStructClassInfo&&)									= default;
			~NestedStructClassInfo()														= default;
	};
}