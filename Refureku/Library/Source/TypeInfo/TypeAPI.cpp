#include "Refureku/TypeInfo/TypeAPI.h"

#include <cstring>	//std::memcmp

#include "Refureku/TypeInfo/TypeImpl.h"

using namespace rfk;

TypeAPI::TypeAPI() noexcept:
	_pimpl{new TypeImpl()}
{
}

TypeAPI::TypeAPI(TypeAPI const& other) noexcept:
	_pimpl{other._pimpl}
{
}

TypeAPI::TypeAPI(TypeAPI&& other) noexcept:
	_pimpl{std::forward<Pimpl<TypeImpl>>(other._pimpl)}
{
}

TypeAPI::~TypeAPI() noexcept = default;

void TypeAPI::optimizeMemory() noexcept
{
	_pimpl->optimizeMemory();
}

TypePartAPI& TypeAPI::addTypePart() noexcept
{
	return _pimpl->addTypePart();
}

TypePartAPI const& TypeAPI::getTypePartAt(std::size_t index) const noexcept
{
	return _pimpl->getParts()[index];
}

std::size_t TypeAPI::getTypePartsCount() const noexcept
{
	return _pimpl->getParts().size();
}

bool TypeAPI::isPointer() const noexcept
{
	return _pimpl->getParts().front().isPointer();
}

bool TypeAPI::isLValueReference() const	noexcept
{
	return _pimpl->getParts().front().isLValueReference();
}

bool TypeAPI::isRValueReference() const	noexcept
{
	return _pimpl->getParts().front().isRValueReference();
}

bool TypeAPI::isCArray() const noexcept
{
	return _pimpl->getParts().front().isCArray();
}

bool TypeAPI::isValue() const noexcept
{
	return _pimpl->getParts().front().isValue();
}

bool TypeAPI::isConst() const noexcept
{
	return _pimpl->getParts().front().isConst();
}

bool TypeAPI::isVolatile() const noexcept
{
	return _pimpl->getParts().front().isVolatile();
}

uint32 TypeAPI::getCArraySize() const noexcept
{
	return _pimpl->getParts().front().getCArraySize();
}

bool TypeAPI::match(TypeAPI const& other) const noexcept
{
	return	(this == &other) ||																	//Types have the same address, don't need any further check
			(*this == other) ||																	//Strictly the same type
			((isPointer() && other.getArchetype() == rfk::getArchetypeAPI<std::nullptr_t>()) ||	//Pointer - nullptr_t correspondance
			(getArchetype() == rfk::getArchetypeAPI<std::nullptr_t>() && other.isPointer()));
}

ArchetypeAPI const* TypeAPI::getArchetype() const noexcept
{
	return _pimpl->getArchetype();
}

void TypeAPI::setArchetype(ArchetypeAPI const* archetype) noexcept
{
	_pimpl->setArchetype(archetype);
}

bool TypeAPI::operator==(TypeAPI const& type) const noexcept
{
	return	(this == &type) ||
			(_pimpl->getArchetype() == type.getArchetype() &&
			_pimpl->getParts().size() == type._pimpl->getParts().size() &&
			std::memcmp(_pimpl->getParts().data(), type._pimpl->getParts().data(), _pimpl->getParts().size() * sizeof(TypePartAPI)) == 0);
}

bool TypeAPI::operator!=(TypeAPI const& type) const noexcept
{
	return !(*this == type);
}