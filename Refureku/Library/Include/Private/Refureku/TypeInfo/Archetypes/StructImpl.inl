/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline StructAPI::StructImpl::StructImpl(char const* name, std::size_t	id, std::size_t memorySize, bool isClass, EClassKind classKind) noexcept:
	ArchetypeImpl(name, id, isClass ? EEntityKind::Class : EEntityKind::Struct, memorySize, nullptr),
	_defaultInstantiator{nullptr},
	_classKind{classKind}
{
}

inline void StructAPI::StructImpl::addDirectParent(StructAPI const& archetype, EAccessSpecifier inheritanceAccess) noexcept
{
	_directParents.emplace_back(archetype, inheritanceAccess);

	//Inherit parent properties
	inheritProperties(*archetype.getPimpl());
}

inline void StructAPI::StructImpl::addSubclass(StructAPI const& subclass) noexcept
{
	_subclasses.insert(&subclass);
}

inline ArchetypeAPI* StructAPI::StructImpl::addNestedArchetype(ArchetypeAPI const* nestedArchetype,
															   EAccessSpecifier accessSpecifier, StructAPI const* outerEntity) noexcept
{
	//The hash is based on the archetype name which is immutable, so it's safe to const_cast to update other members.
	ArchetypeAPI* result = const_cast<ArchetypeAPI*>(*_nestedArchetypes.emplace(nestedArchetype).first);

	result->setAccessSpecifier(accessSpecifier);
	result->setOuterEntity(outerEntity);

	return result;
}

inline FieldAPI* StructAPI::StructImpl::addField(char const* name, std::size_t id, Type const& type, EFieldFlags flags, 
												 StructAPI const* owner, std::size_t memoryOffset, StructAPI const* outerEntity) noexcept
{
	assert((flags & EFieldFlags::Static) != EFieldFlags::Static);

	//The hash is based on the field name which is immutable, so it's safe to const_cast to update other members.
	return const_cast<FieldAPI*>(&*_fields.emplace(name, id, type, flags, owner, memoryOffset, outerEntity));
}

inline StaticFieldAPI* StructAPI::StructImpl::addStaticField(char const* name, std::size_t id, Type const& type, EFieldFlags flags, 
															 StructAPI const* owner, void* fieldPtr, StructAPI const* outerEntity) noexcept
{
	assert((flags & EFieldFlags::Static) == EFieldFlags::Static);

	//The hash is based on the static field name which is immutable, so it's safe to const_cast to update other members.
	return const_cast<StaticFieldAPI*>(&*_staticFields.emplace(name, id, type, flags, owner, fieldPtr, outerEntity));
}

inline StaticFieldAPI* StructAPI::StructImpl::addStaticField(char const* name, std::size_t id, Type const& type, EFieldFlags flags, 
															 StructAPI const* owner, void const* fieldPtr, StructAPI const* outerEntity) noexcept
{
	assert((flags & EFieldFlags::Static) == EFieldFlags::Static);

	//The hash is based on the static field name which is immutable, so it's safe to const_cast to update other members.
	return const_cast<StaticFieldAPI*>(&*_staticFields.emplace(name, id, type, flags, owner, fieldPtr, outerEntity));
}

inline MethodAPI* StructAPI::StructImpl::addMethod(char const* name, std::size_t id, Type const& returnType,
												   ICallable* internalMethod, EMethodFlags flags, StructAPI const*	outerEntity) noexcept
{
	assert((flags & EMethodFlags::Static) != EMethodFlags::Static);

	//The hash is based on the method name which is immutable, so it's safe to const_cast to update other members.
	return const_cast<MethodAPI*>(&*_methods.emplace(name, id, returnType, internalMethod, flags, outerEntity));
}

inline StaticMethodAPI* StructAPI::StructImpl::addStaticMethod(char const* name, std::size_t id, Type const& returnType,
															   ICallable* internalMethod, EMethodFlags flags, StructAPI const* outerEntity) noexcept
{
	assert((flags & EMethodFlags::Static) == EMethodFlags::Static);

	//The hash is based on the static method name which is immutable, so it's safe to const_cast to update other members.
	return const_cast<StaticMethodAPI*>(&*_staticMethods.emplace(name, id, returnType, internalMethod, flags, outerEntity));
}

inline void StructAPI::StructImpl::setDefaultInstantiator(void* (*defaultInstantiator)()) noexcept
{
	_defaultInstantiator = defaultInstantiator;
}

inline void StructAPI::StructImpl::addInstantiator(StaticMethodAPI const* instantiator) noexcept
{
	//Make sure the instantiator is valid
	assert(instantiator != nullptr);
	assert(instantiator->getReturnType().isPointer());

	//If it is a parameterless custom instantiator, replace the default instantiator
	if (instantiator->getParametersCount() == 0u)
	{
		setDefaultInstantiator(reinterpret_cast<rfk::NonMemberFunction<void* ()> const*>(instantiator->getInternalFunction())->getFunctionHandle());
	}
	else
	{
		_customInstantiators.push_back(instantiator);
	}
}

inline void StructAPI::StructImpl::setDirectParentsCapacity(std::size_t capacity) noexcept
{
	_directParents.reserve(capacity);
}

inline void StructAPI::StructImpl::setNestedArchetypesCapacity(std::size_t capacity) noexcept
{
	_nestedArchetypes.rehash(capacity);
}

inline void StructAPI::StructImpl::setFieldsCapacity(std::size_t capacity) noexcept
{
	_fields.reserve(capacity);
}

inline void StructAPI::StructImpl::setStaticFieldsCapacity(std::size_t capacity) noexcept
{
	_staticFields.reserve(capacity);
}

inline void StructAPI::StructImpl::setMethodsCapacity(std::size_t capacity) noexcept
{
	_methods.reserve(capacity);
}

inline void StructAPI::StructImpl::setStaticMethodsCapacity(std::size_t capacity) noexcept
{
	_staticMethods.reserve(capacity);
}

inline ArchetypeAPI const* StructAPI::StructImpl::getNestedArchetype(char const* name, EAccessSpecifier access) const noexcept
{
	return EntityUtility::getEntityByNameAndPredicate(_nestedArchetypes, name,
													  [access](ArchetypeAPI const& archetype)
													  {
														  return access == EAccessSpecifier::Undefined || access == archetype.getAccessSpecifier();
													  });
}

inline StructAPI::StructImpl::ParentStructs const& StructAPI::StructImpl::getDirectParents() const noexcept
{
	return _directParents;
}

inline StructAPI::StructImpl::Subclasses const& StructAPI::StructImpl::getSubclasses() const noexcept
{
	return _subclasses;
}

inline StructAPI::StructImpl::NestedArchetypes const& StructAPI::StructImpl::getNestedArchetypes() const noexcept
{
	return _nestedArchetypes;
}

inline StructAPI::StructImpl::Fields const& StructAPI::StructImpl::getFields() const noexcept
{
	return _fields;
}

inline StructAPI::StructImpl::StaticFields const& StructAPI::StructImpl::getStaticFields() const noexcept
{
	return _staticFields;
}

inline StructAPI::StructImpl::Methods const& StructAPI::StructImpl::getMethods() const noexcept
{
	return _methods;
}

inline StructAPI::StructImpl::StaticMethods const& StructAPI::StructImpl::getStaticMethods() const noexcept
{
	return _staticMethods;
}

inline StructAPI::StructImpl::CustomInstantiators const& StructAPI::StructImpl::getCustomInstantiators() const noexcept
{
	return _customInstantiators;
}

inline StructAPI::StructImpl::CustomInstantiator StructAPI::StructImpl::getDefaultInstantiator() const noexcept
{
	return _defaultInstantiator;
}

inline EClassKind StructAPI::StructImpl::getClassKind() const noexcept
{
	return _classKind;
}