#include "Refureku/TypeInfo/Type.h"

#include <cstring>	//std::memcmp

#include "Refureku/TypeInfo/TypeImpl.h"

using namespace rfk;

Type::Type() noexcept:
	_pimpl{new TypeImpl()}
{
}

Type::Type(Type const& other) noexcept:
	_pimpl{other._pimpl}
{
}

Type::Type(Type&& other) noexcept:
	_pimpl{std::forward<Pimpl<TypeImpl>>(other._pimpl)}
{
}

Type::~Type() noexcept = default;

void Type::optimizeMemory() noexcept
{
	_pimpl->optimizeMemory();
}

TypePart& Type::addTypePart() noexcept
{
	return _pimpl->addTypePart();
}

TypePart const& Type::getTypePartAt(std::size_t index) const noexcept
{
	return _pimpl->getParts()[index];
}

std::size_t Type::getTypePartsCount() const noexcept
{
	return _pimpl->getParts().size();
}

bool Type::isPointer() const noexcept
{
	return _pimpl->getParts().front().isPointer();
}

bool Type::isLValueReference() const	noexcept
{
	return _pimpl->getParts().front().isLValueReference();
}

bool Type::isRValueReference() const	noexcept
{
	return _pimpl->getParts().front().isRValueReference();
}

bool Type::isCArray() const noexcept
{
	return _pimpl->getParts().front().isCArray();
}

bool Type::isValue() const noexcept
{
	return _pimpl->getParts().front().isValue();
}

bool Type::isConst() const noexcept
{
	return _pimpl->getParts().front().isConst();
}

bool Type::isVolatile() const noexcept
{
	return _pimpl->getParts().front().isVolatile();
}

uint32 Type::getCArraySize() const noexcept
{
	return _pimpl->getParts().front().getCArraySize();
}

bool Type::match(Type const& other) const noexcept
{
	return	(*this == other) ||																	//Strictly the same type
			((isPointer() && other.getArchetype() == rfk::getArchetype<std::nullptr_t>()) ||	//Pointer - nullptr_t correspondance
			(getArchetype() == rfk::getArchetype<std::nullptr_t>() && other.isPointer()));
}

Archetype const* Type::getArchetype() const noexcept
{
	return _pimpl->getArchetype();
}

void Type::setArchetype(Archetype const* archetype) noexcept
{
	_pimpl->setArchetype(archetype);
}

bool Type::operator==(Type const& type) const noexcept
{
	return	(this == &type) ||
			(_pimpl->getArchetype() == type.getArchetype() &&
			_pimpl->getParts().size() == type._pimpl->getParts().size() &&
			std::memcmp(_pimpl->getParts().data(), type._pimpl->getParts().data(), _pimpl->getParts().size() * sizeof(TypePart)) == 0);
}

bool Type::operator!=(Type const& type) const noexcept
{
	return !(*this == type);
}