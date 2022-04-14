#include "Refureku/TypeInfo/Archetypes/ParentStruct.h"

#include "Refureku/TypeInfo/Archetypes/Struct.h"

using namespace rfk;

ParentStruct::ParentStruct(Struct const& archetype, EAccessSpecifier inheritanceAccessSpecifier) noexcept:
	_archetype{&archetype},
	_inheritanceAccessSpecifier{inheritanceAccessSpecifier}
{
}

ParentStruct::ParentStruct(ParentStruct&&) noexcept = default;

ParentStruct::~ParentStruct() noexcept = default;

Struct const& ParentStruct::getArchetype() const noexcept
{
	return *_archetype;
}

EAccessSpecifier ParentStruct::getInheritanceAccessSpecifier() const noexcept
{
	return _inheritanceAccessSpecifier;
}

ParentStruct& ParentStruct::operator=(ParentStruct&&) noexcept = default;