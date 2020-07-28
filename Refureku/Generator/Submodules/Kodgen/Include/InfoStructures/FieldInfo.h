/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <clang-c/Index.h>

#include "InfoStructures/EntityInfo.h"
#include "InfoStructures/TypeInfo.h"
#include "Misc/EAccessSpecifier.h"

namespace kodgen
{
	class FieldInfo : public EntityInfo
	{
		public:
			struct FieldQualifiers
			{
				bool isStatic	: 1;
				bool isMutable	: 1;
			}					qualifiers;

			/** Type of this field. */
			TypeInfo			type;

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

	std::ostream& operator<<(std::ostream& out_stream, FieldInfo const& fieldInfo) noexcept;
}