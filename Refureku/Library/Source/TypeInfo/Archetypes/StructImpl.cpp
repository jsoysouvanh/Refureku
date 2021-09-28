#include "Refureku/TypeInfo/Archetypes/StructImpl.h"

using namespace rfk;

StructAPI::StructImpl::StructImpl(char const* name, std::size_t	id, std::size_t memorySize, bool isClass, EClassKind classKind) noexcept:
	ArchetypeImpl(name, id, isClass ? EEntityKind::Class : EEntityKind::Struct, memorySize, nullptr)
//	_classKind{classKind}
{
}