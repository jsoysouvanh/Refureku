#include "Refureku/TypeInfo/Archetypes/ArchetypeAPI.h"

#include <utility>	//std::forward

#include "Refureku/TypeInfo/Archetypes/ArchetypeImpl.h"

using namespace rfk;

ArchetypeAPI::ArchetypeAPI() noexcept:
	_pimpl{static_cast<ArchetypeImpl*>(nullptr)}
{
}

ArchetypeAPI::ArchetypeAPI(char const* name, std::size_t id, EEntityKind kind, std::size_t memorySize, EntityAPI const* outerEntity) noexcept:
	_pimpl(name, id, kind, memorySize, outerEntity)
{
	//TODO: Delete this
	EntityAPI::setImpl(_pimpl.get());
}

ArchetypeAPI::ArchetypeAPI(ArchetypeAPI const& other) noexcept:
	_pimpl{other._pimpl}
{
}

ArchetypeAPI::ArchetypeAPI(ArchetypeAPI&& other) noexcept:
	_pimpl{std::forward<Pimpl<ArchetypeImpl>>(other._pimpl)}
{
}

ArchetypeAPI::~ArchetypeAPI() noexcept
{
	//Must be defined in cpp since _pimpl is an incomplete type in the header file
}

void ArchetypeAPI::setImpl(ArchetypeImpl* implementation) noexcept
{
	EntityAPI::setImpl(implementation);

	_pimpl.set(implementation);
}

EAccessSpecifier ArchetypeAPI::getAccessSpecifier() const noexcept
{
	return _pimpl->getAccessSpecifier();
}

void ArchetypeAPI::setAccessSpecifier(EAccessSpecifier accessSpecifier) noexcept
{
	_pimpl->setAccessSpecifier(accessSpecifier);
}

std::size_t ArchetypeAPI::getMemorySize() const noexcept
{
	return _pimpl->getMemorySize();
}