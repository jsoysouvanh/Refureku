#include "InfoStructures/NestedEnumInfo.h"

using namespace kodgen;

NestedEnumInfo::NestedEnumInfo(EnumInfo&& base, EAccessSpecifier accessSpecifier) noexcept:
	accessSpecifier{accessSpecifier}
{
	entityType		= base.entityType;
	name			= std::move(base.name);
	id				= std::move(base.id);
	properties		= std::move(base.properties);

	type			= std::move(base.type);
	underlyingType	= std::move(base.underlyingType);
	enumValues		= std::move(base.enumValues);
}