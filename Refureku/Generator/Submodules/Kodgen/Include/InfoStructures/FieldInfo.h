#pragma once

#include "Misc/EAccessSpecifier.h"
#include "InfoStructures/EntityInfo.h"
#include "InfoStructures/TypeInfo.h"

namespace kodgen
{
	class FieldInfo : public EntityInfo
	{
		public:
			struct FieldQualifiers
			{
				bool isStatic	: 1;
				bool isMutable	: 1;

			}			qualifiers;

			TypeInfo			type;
			EAccessSpecifier	accessSpecifier;
			int64				memoryOffset;

			FieldInfo()															= default;
			FieldInfo(CXCursor const& cursor, PropertyGroup&& propertyGroup)	noexcept;
			FieldInfo(FieldInfo const&)											= default;
			FieldInfo(FieldInfo&&)												= default;
			~FieldInfo()														= default;
	};

	std::ostream& operator<<(std::ostream& out_stream, FieldInfo const& fieldInfo) noexcept;
}