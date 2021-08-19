/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <clang-c/Index.h>

#include "Kodgen/InfoStructures/VariableInfo.h"
#include "Kodgen/Misc/EAccessSpecifier.h"

namespace kodgen
{
	class FieldInfo final : public VariableInfo
	{
		public:
			/** Is this field mutable qualified? */
			bool isMutable : 1;

			/** Access of this field in its outer struct/class. */
			EAccessSpecifier	accessSpecifier;

			/** Memory offset in bytes. */
			int64				memoryOffset;

			FieldInfo()									= default;
			FieldInfo(CXCursor const& cursor,
					  PropertyGroup&& propertyGroup)	noexcept;
			FieldInfo(FieldInfo const&)					= default;
			FieldInfo(FieldInfo&&)						= default;
			~FieldInfo()								= default;
	};
}