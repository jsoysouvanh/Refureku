#include "Refureku/TypeInfo/Archetypes/StructAPI.h"

#include "Refureku/TypeInfo/Archetypes/StructImpl.h"
#include "Refureku/TypeInfo/Archetypes/ClassTemplate.h"
#include "Refureku/TypeInfo/Archetypes/ClassTemplateInstantiation.h"

using namespace rfk;

StructAPI::StructAPI(char const* name, std::size_t id, std::size_t memorySize, bool isClass, EClassKind classKind) noexcept:
	ArchetypeAPI(new StructImpl(name, id, memorySize, isClass, classKind))
{
}

StructAPI::StructAPI(char const* name, std::size_t id, std::size_t memorySize, bool isClass) noexcept:
	StructAPI(name, id, memorySize, isClass, EClassKind::Standard)
{
}

StructAPI::StructAPI(StructImpl* implementation) noexcept:
	ArchetypeAPI(implementation)
{
}

StructAPI::~StructAPI() noexcept = default;

EClassKind StructAPI::getClassKind() const noexcept
{
	return reinterpret_cast<StructImpl const*>(getPimpl())->getClassKind();
}

ArchetypeAPI* StructAPI::addNestedArchetype(ArchetypeAPI const* nestedArchetype, EAccessSpecifier accessSpecifier) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->addNestedArchetype(nestedArchetype, accessSpecifier, this);
}

FieldAPI* StructAPI::addField(char const* name, std::size_t id, TypeAPI const& type,
							  EFieldFlags flags, std::size_t memoryOffset, StructAPI const* outerEntity) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->addField(name, id, type, flags, this, memoryOffset, outerEntity);
}

StaticFieldAPI* StructAPI::addStaticField(char const* name, std::size_t id, TypeAPI const& type,
										  EFieldFlags flags, void* fieldPtr, StructAPI const* outerEntity) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->addStaticField(name, id, type, flags, this, fieldPtr, outerEntity);
}

StaticFieldAPI* StructAPI::addStaticField(char const* name, std::size_t id, TypeAPI const& type,
										  EFieldFlags flags, void const* fieldPtr, StructAPI const* outerEntity) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->addStaticField(name, id, type, flags, this, fieldPtr, outerEntity);
}

MethodAPI* StructAPI::addMethod(char const* name, std::size_t id,
								TypeAPI const& returnType, ICallable* internalMethod, EMethodFlags flags) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->addMethod(name, id, returnType, internalMethod, flags, this);
}

StaticMethodAPI* StructAPI::addStaticMethod(char const* name, std::size_t id,
											TypeAPI const& returnType, ICallable* internalMethod, EMethodFlags flags) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->addStaticMethod(name, id, returnType, internalMethod, flags, this);
}

void StructAPI::setDefaultInstantiator(void* (*instantiator)()) noexcept
{
	reinterpret_cast<StructImpl*>(getPimpl())->setDefaultInstantiator(instantiator);
}

void StructAPI::addInstantiator(StaticMethodAPI const* instantiator) noexcept
{
	reinterpret_cast<StructImpl*>(getPimpl())->addInstantiator(instantiator);
}

ClassTemplate const* StructAPI::asTemplate() const noexcept
{
	return (getClassKind() == EClassKind::Template) ?
		reinterpret_cast<ClassTemplate const*>(this) : nullptr;
}

ClassTemplateInstantiation const* StructAPI::asTemplateInstantiation() const noexcept
{
	return (getClassKind() == EClassKind::TemplateInstantiation) ?
		reinterpret_cast<ClassTemplateInstantiation const*>(this) : nullptr;
}