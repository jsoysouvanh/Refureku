#include "Refureku/TypeInfo/Archetypes/Archetype.h"

#include <cassert>

#include "Refureku/TypeInfo/Functions/StaticMethod.h"

using namespace rfk;

Archetype::Archetype(std::string&& newName, std::size_t id, EEntityKind kind, std::size_t memorySize, Entity const*	outerEntity) noexcept:
	Entity(std::forward<std::string>(newName), id, kind, outerEntity),
	_memorySize{memorySize}
{
}

EAccessSpecifier Archetype::getAccessSpecifier() const noexcept
{
	return _accessSpecifier;
}

void Archetype::setAccessSpecifier(EAccessSpecifier accessSpecifier) noexcept
{
	_accessSpecifier = accessSpecifier;
}

std::size_t Archetype::getMemorySize() const noexcept
{
	return _memorySize;
}