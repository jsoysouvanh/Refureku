#include "Refureku/TypeInfo/Archetypes/StructAPI.h"

#include "Refureku/TypeInfo/Archetypes/StructImpl.h"

using namespace rfk;

StructAPI::StructAPI(char const* name, std::size_t id, std::size_t memorySize, bool isClass, EClassKind classKind) noexcept:
	ArchetypeAPI(new StructImpl(name, id, memorySize, isClass, classKind))
{
}

StructAPI::StructAPI(char const* name, std::size_t id, std::size_t memorySize, bool isClass) noexcept:
	StructAPI(name, id, memorySize, isClass, EClassKind::Standard)
{
}

//StructAPI::StructAPI(StructAPI const& other) noexcept:
//	ArchetypeAPI(new StructImpl(*reinterpret_cast<StructImpl const*>(other.getPimpl())))
//{
//}
//
//StructAPI::StructAPI(StructAPI&&) noexcept = default;

StructAPI::~StructAPI() noexcept = default;