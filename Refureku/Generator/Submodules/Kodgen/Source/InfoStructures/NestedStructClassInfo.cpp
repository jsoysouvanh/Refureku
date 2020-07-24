#include "InfoStructures/NestedStructClassInfo.h"

using namespace kodgen;

NestedStructClassInfo::NestedStructClassInfo(StructClassInfo&& base, EAccessSpecifier accessSpecifier) noexcept:
	accessSpecifier{accessSpecifier}
{
	entityType		= base.entityType;
	name			= std::move(base.name);
	id				= std::move(base.id);
	properties		= std::move(base.properties);

	qualifiers		= base.qualifiers;
	type			= std::move(base.type);
	parents			= std::move(base.parents);
	nestedStructs	= std::move(base.nestedStructs);
	nestedClasses	= std::move(base.nestedClasses);
	nestedEnums		= std::move(base.nestedEnums);
	fields			= std::move(base.fields);
	methods			= std::move(base.methods);
}