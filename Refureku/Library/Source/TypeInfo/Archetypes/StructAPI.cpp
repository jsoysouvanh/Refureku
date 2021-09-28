#include "Refureku/TypeInfo/Archetypes/StructAPI.h"

#include "Refureku/TypeInfo/Archetypes/StructImpl.h"

using namespace rfk;

StructAPI::StructAPI(char const* name, std::size_t id, std::size_t memorySize, bool isClass, EClassKind classKind) noexcept:
	ArchetypeAPI(),
	_pimpl(name, id, memorySize, isClass, classKind)
{
	ArchetypeAPI::setImpl(_pimpl.get());
}

StructAPI::StructAPI(char const* name, std::size_t id, std::size_t memorySize, bool isClass) noexcept:
	StructAPI(name, id, memorySize, isClass, EClassKind::Standard)
{
}

StructAPI::StructAPI(StructAPI const& other) noexcept:
	_pimpl{other._pimpl}
{
	ArchetypeAPI::setImpl(_pimpl.get());
}

StructAPI::StructAPI(StructAPI&& other) noexcept:
	_pimpl{std::forward<Pimpl<StructImpl>>(other._pimpl)}
{
	ArchetypeAPI::setImpl(_pimpl.get());
}

StructAPI::~StructAPI() noexcept
{
	//Must be defined in cpp since _pimpl is an incomplete type in the header file
}

void StructAPI::setImpl(StructImpl* implementation) noexcept
{
	ArchetypeAPI::setImpl(implementation);

	_pimpl.set(implementation);
}