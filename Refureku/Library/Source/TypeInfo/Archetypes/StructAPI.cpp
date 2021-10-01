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

rfk::Vector<StructAPI const*> StructAPI::getDirectSubclasses() const noexcept
{
	rfk::Vector<StructAPI const*> result;

	for (StructAPI const* subclass : reinterpret_cast<StructImpl const*>(getPimpl())->getSubclasses())
	{
		//Search this struct in subclasses's parents
		for (ParentStruct const& subclassParent : reinterpret_cast<StructImpl const*>(subclass->getPimpl())->getDirectParents())
		{
			if (&subclassParent.getArchetype() == this)
			{
				result.emplace_back(subclass);
				break;
			}
		}
	}

	return result;
}

bool StructAPI::isSubclassOf(StructAPI const& archetype) const noexcept
{
	return &archetype != this && archetype.isBaseOf(*this);
}

bool StructAPI::isBaseOf(StructAPI const& archetype) const noexcept
{
	auto const& subclasses = reinterpret_cast<StructImpl const*>(getPimpl())->getSubclasses();

	return &archetype == this || subclasses.find(&archetype) != subclasses.cend();
}

EClassKind StructAPI::getClassKind() const noexcept
{
	return reinterpret_cast<StructImpl const*>(getPimpl())->getClassKind();
}

ParentStruct const& StructAPI::getDirectParentAt(std::size_t index) const noexcept
{
	return reinterpret_cast<StructImpl const*>(getPimpl())->getDirectParents()[index];
}

std::size_t StructAPI::getDirectParentsCount() const noexcept
{
	return reinterpret_cast<StructImpl const*>(getPimpl())->getDirectParents().size();
}

bool StructAPI::foreachNestedArchetype(bool (*visitor)(ArchetypeAPI const&, void*), void* userData) const noexcept
{
	if (visitor != nullptr)
	{
		for (ArchetypeAPI const* nestedArchetype : reinterpret_cast<StructImpl const*>(getPimpl())->getNestedArchetypes())
		{
			if (!visitor(*nestedArchetype, userData))
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

bool StructAPI::foreachField(bool (*visitor)(FieldAPI const&, void*), void* userData) const noexcept
{
	if (visitor != nullptr)
	{
		for (FieldAPI const& field : reinterpret_cast<StructImpl const*>(getPimpl())->getFields())
		{
			if (!visitor(field, userData))
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

bool StructAPI::foreachStaticField(bool (*visitor)(StaticFieldAPI const&, void*), void* userData) const noexcept
{
	if (visitor != nullptr)
	{
		for (StaticFieldAPI const& staticField : reinterpret_cast<StructImpl const*>(getPimpl())->getStaticFields())
		{
			if (!visitor(staticField, userData))
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

bool StructAPI::foreachMethod(bool (*visitor)(MethodAPI const&, void*), void* userData) const noexcept
{
	if (visitor != nullptr)
	{
		for (MethodAPI const& method : reinterpret_cast<StructImpl const*>(getPimpl())->getMethods())
		{
			if (!visitor(method, userData))
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

bool StructAPI::foreachStaticMethod(bool (*visitor)(StaticMethodAPI const&, void*), void* userData) const noexcept
{
	if (visitor != nullptr)
	{
		for (StaticMethodAPI const& staticMethod : reinterpret_cast<StructImpl const*>(getPimpl())->getStaticMethohds())
		{
			if (!visitor(staticMethod, userData))
			{
				return false;
			}
		}

		return true;
	}

	return false;
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

void StructAPI::addDirectParent(ArchetypeAPI const* archetype, EAccessSpecifier inheritanceAccess) noexcept
{
	if (archetype != nullptr)
	{
		assert(archetype->getKind() == EEntityKind::Struct || archetype->getKind() == EEntityKind::Class);

		reinterpret_cast<StructImpl*>(getPimpl())->addDirectParent(*reinterpret_cast<StructAPI const*>(archetype), inheritanceAccess);
	}
}

void StructAPI::setDirectParentsCapacity(std::size_t capacity) noexcept
{
	reinterpret_cast<StructImpl*>(getPimpl())->setDirectParentsCapacity(capacity);
}

void StructAPI::addSubclass(StructAPI const& subclass) noexcept
{
	reinterpret_cast<StructImpl*>(getPimpl())->addSubclass(subclass);
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

void StructAPI::setFieldsCapacity(std::size_t capacity) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->setFieldsCapacity(capacity);
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

void StructAPI::setStaticFieldsCapacity(std::size_t capacity) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->setStaticFieldsCapacity(capacity);
}

MethodAPI* StructAPI::addMethod(char const* name, std::size_t id,
								TypeAPI const& returnType, ICallable* internalMethod, EMethodFlags flags) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->addMethod(name, id, returnType, internalMethod, flags, this);
}

void StructAPI::setMethodsCapacity(std::size_t capacity) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->setMethodsCapacity(capacity);
}

StaticMethodAPI* StructAPI::addStaticMethod(char const* name, std::size_t id,
											TypeAPI const& returnType, ICallable* internalMethod, EMethodFlags flags) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->addStaticMethod(name, id, returnType, internalMethod, flags, this);
}

void StructAPI::setStaticMethodsCapacity(std::size_t capacity) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->setStaticMethodsCapacity(capacity);
}

void StructAPI::setDefaultInstantiator(void* (*instantiator)()) noexcept
{
	reinterpret_cast<StructImpl*>(getPimpl())->setDefaultInstantiator(instantiator);
}

void StructAPI::addInstantiator(StaticMethodAPI const* instantiator) noexcept
{
	reinterpret_cast<StructImpl*>(getPimpl())->addInstantiator(instantiator);
}