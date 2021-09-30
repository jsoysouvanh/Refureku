/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

StructAPI::StructImpl::StructImpl(char const* name, std::size_t	id, std::size_t memorySize, bool isClass, EClassKind classKind) noexcept:
	ArchetypeImpl(name, id, isClass ? EEntityKind::Class : EEntityKind::Struct, memorySize, nullptr),
	_defaultInstantiator{nullptr},
	_classKind{classKind}
{
}

ArchetypeAPI* StructAPI::StructImpl::addNestedArchetype(ArchetypeAPI const* nestedArchetype,
														EAccessSpecifier accessSpecifier, StructAPI const* outerEntity) noexcept
{
	//The hash is based on the archetype name which is immutable, so it's safe to const_cast to update other members.
	ArchetypeAPI* result = const_cast<ArchetypeAPI*>(*_nestedArchetypes.emplace(nestedArchetype).first);

	result->setAccessSpecifier(accessSpecifier);
	result->setOuterEntity(outerEntity);

	return result;
}

FieldAPI* StructAPI::StructImpl::addField(char const* name, std::size_t id, TypeAPI const& type, EFieldFlags flags, 
										  StructAPI const* owner, std::size_t memoryOffset, StructAPI const* outerEntity) noexcept
{
	assert((flags & EFieldFlags::Static) != EFieldFlags::Static);

	//The hash is based on the field name which is immutable, so it's safe to const_cast to update other members.
	return const_cast<FieldAPI*>(&*_fields.emplace(name, id, type, flags, owner, memoryOffset, outerEntity));
}

StaticFieldAPI* StructAPI::StructImpl::addStaticField(char const* name, std::size_t id, TypeAPI const& type, EFieldFlags flags, 
													  StructAPI const* owner, void* fieldPtr, StructAPI const* outerEntity) noexcept
{
	assert((flags & EFieldFlags::Static) == EFieldFlags::Static);

	//The hash is based on the static field name which is immutable, so it's safe to const_cast to update other members.
	return const_cast<StaticFieldAPI*>(&*_staticFields.emplace(name, id, type, flags, owner, fieldPtr, outerEntity));
}

StaticFieldAPI* StructAPI::StructImpl::addStaticField(char const* name, std::size_t id, TypeAPI const& type, EFieldFlags flags, 
													  StructAPI const* owner, void const* fieldPtr, StructAPI const* outerEntity) noexcept
{
	assert((flags & EFieldFlags::Static) == EFieldFlags::Static);

	//The hash is based on the static field name which is immutable, so it's safe to const_cast to update other members.
	return const_cast<StaticFieldAPI*>(&*_staticFields.emplace(name, id, type, flags, owner, fieldPtr, outerEntity));
}

MethodAPI* StructAPI::StructImpl::addMethod(char const* name, std::size_t id, TypeAPI const& returnType,
											ICallable* internalMethod, EMethodFlags flags, StructAPI const*	outerEntity) noexcept
{
	assert((flags & EMethodFlags::Static) != EMethodFlags::Static);

	//The hash is based on the method name which is immutable, so it's safe to const_cast to update other members.
	return const_cast<MethodAPI*>(&*_methods.emplace(name, id, returnType, internalMethod, flags, outerEntity));
}

StaticMethodAPI* StructAPI::StructImpl::addStaticMethod(char const* name, std::size_t id, TypeAPI const& returnType,
														ICallable* internalMethod, EMethodFlags flags, StructAPI const* outerEntity) noexcept
{
	assert((flags & EMethodFlags::Static) == EMethodFlags::Static);

	//The hash is based on the static method name which is immutable, so it's safe to const_cast to update other members.
	return const_cast<StaticMethodAPI*>(&*_staticMethods.emplace(name, id, returnType, internalMethod, flags, outerEntity));
}

void StructAPI::StructImpl::setDefaultInstantiator(void* (*defaultInstantiator)()) noexcept
{
	_defaultInstantiator = defaultInstantiator;
}

void StructAPI::StructImpl::addInstantiator(StaticMethodAPI const* instantiator) noexcept
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

StructAPI::StructImpl::NestedArchetypes const& StructAPI::StructImpl::getNestedArchetypes() const noexcept
{
	return _nestedArchetypes;
}

StructAPI::StructImpl::Fields const& StructAPI::StructImpl::getFields() const noexcept
{
	return _fields;
}

StructAPI::StructImpl::StaticFields const& StructAPI::StructImpl::getStaticFields() const noexcept
{
	return _staticFields;
}

StructAPI::StructImpl::Methods const& StructAPI::StructImpl::getMethods() const noexcept
{
	return _methods;
}

StructAPI::StructImpl::StaticMethods const& StructAPI::StructImpl::getStaticMethohds() const noexcept
{
	return _staticMethods;
}

StructAPI::StructImpl::CustomInstantiators const& StructAPI::StructImpl::getCustomInstantiators() const noexcept
{
	return _customInstantiators;
}

StructAPI::StructImpl::CustomInstantiator StructAPI::StructImpl::getDefaultInstantiator() const noexcept
{
	return _defaultInstantiator;
}

EClassKind StructAPI::StructImpl::getClassKind() const noexcept
{
	return _classKind;
}