#include "Refureku/TypeInfo/Archetypes/FundamentalArchetypeAPI.h"

#include "Refureku/TypeInfo/Archetypes/FundamentalArchetypeImpl.h"

using namespace rfk;

FundamentalArchetypeAPI::FundamentalArchetypeAPI(char const* name, std::size_t id, std::size_t memorySize) noexcept:
	ArchetypeAPI(new FundamentalArchetypeImpl(name, id, memorySize))
{
}

FundamentalArchetypeAPI::~FundamentalArchetypeAPI() noexcept = default;