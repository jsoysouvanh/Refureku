#include "Refureku/TypeInfo/Archetypes/ParentStruct.h"

#include "Refureku/TypeInfo/Archetypes/StructAPI.h"

using namespace rfk;

ParentStruct::ParentStruct(StructAPI const& archetype, EAccessSpecifier inheritanceAccessSpecifier) noexcept:
	_archetype{archetype},
	_inheritanceAccessSpecifier{inheritanceAccessSpecifier}
{
}

ParentStruct::ParentStruct(ParentStruct&&) noexcept = default;

ParentStruct::~ParentStruct() noexcept = default;

StructAPI const& ParentStruct::getArchetype() const noexcept
{
	return _archetype;
}

EAccessSpecifier ParentStruct::getInheritanceAccessSpecifier() const noexcept
{
	return _inheritanceAccessSpecifier;
}