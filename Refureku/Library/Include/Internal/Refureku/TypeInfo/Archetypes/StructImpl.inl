/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline Struct::StructImpl::StructImpl(char const* name, std::size_t	id, std::size_t memorySize, bool isClass, EClassKind classKind) noexcept:
	ArchetypeImpl(name, id, isClass ? EEntityKind::Class : EEntityKind::Struct, memorySize, nullptr),
	_classKind{classKind}
{
}

inline void Struct::StructImpl::addDirectParent(Struct const& archetype, EAccessSpecifier inheritanceAccess) noexcept
{
	_directParents.emplace_back(archetype, inheritanceAccess);

	//Inherit parent properties
	inheritProperties(*archetype.getPimpl());
}

inline void Struct::StructImpl::removeDirectParentAt(std::size_t parentIndex) noexcept
{
	_directParents.erase(_directParents.begin() + parentIndex);
}

inline void Struct::StructImpl::addSubclass(Struct const& subclass, std::ptrdiff_t subclassPointerOffset) noexcept
{
	_subclasses.emplace(&subclass, subclassPointerOffset);
}

inline void Struct::StructImpl::removeSubclassRecursive(rfk::Struct const& subclass) noexcept
{
	for (ParentStruct const& parent : _directParents)
	{
		const_cast<rfk::Struct&>(parent.getArchetype()).getPimpl()->removeSubclassRecursive(subclass);
	}

	_subclasses.erase(&subclass);
}

inline void Struct::StructImpl::addNestedArchetype(Archetype const* nestedArchetype,
												   EAccessSpecifier accessSpecifier, Struct const* outerEntity) noexcept
{
	//The hash is based on the archetype name which is immutable, so it's safe to const_cast to update other members.
	Archetype* result = const_cast<Archetype*>(*_nestedArchetypes.emplace(nestedArchetype).first);

	result->setAccessSpecifier(accessSpecifier);
	result->setOuterEntity(outerEntity);
}

inline Field* Struct::StructImpl::addField(char const* name, std::size_t id, char const* canonicalTypeName, Type const& type, EFieldFlags flags, 
										   Struct const* owner, std::size_t memoryOffset, Struct const* outerEntity) noexcept
{
	assert(name != nullptr);
	assert((flags & EFieldFlags::Static) != EFieldFlags::Static);

	//The hash is based on the field name which is immutable, so it's safe to const_cast to update other members.
	return const_cast<Field*>(&*_fields.emplace(name, id, canonicalTypeName, type, flags, owner, memoryOffset, outerEntity));
}

inline StaticField* Struct::StructImpl::addStaticField(char const* name, std::size_t id, char const* canonicalTypeName, Type const& type, EFieldFlags flags, 
													   Struct const* owner, void* fieldPtr, Struct const* outerEntity) noexcept
{
	assert(name != nullptr);
	assert((flags & EFieldFlags::Static) == EFieldFlags::Static);

	//The hash is based on the static field name which is immutable, so it's safe to const_cast to update other members.
	return const_cast<StaticField*>(&*_staticFields.emplace(name, id, canonicalTypeName, type, flags, owner, fieldPtr, outerEntity));
}

inline StaticField* Struct::StructImpl::addStaticField(char const* name, std::size_t id, char const* canonicalTypeName, Type const& type, EFieldFlags flags, 
													   Struct const* owner, void const* fieldPtr, Struct const* outerEntity) noexcept
{
	assert(name != nullptr);
	assert((flags & EFieldFlags::Static) == EFieldFlags::Static);

	//The hash is based on the static field name which is immutable, so it's safe to const_cast to update other members.
	return const_cast<StaticField*>(&*_staticFields.emplace(name, id, canonicalTypeName, type, flags, owner, fieldPtr, outerEntity));
}

inline Method* Struct::StructImpl::addMethod(char const* name, std::size_t id, Type const& returnType,
											 ICallable* internalMethod, EMethodFlags flags, Struct const*	outerEntity) noexcept
{
	assert(name != nullptr);
	assert((flags & EMethodFlags::Static) != EMethodFlags::Static);

	//The hash is based on the method name which is immutable, so it's safe to const_cast to update other members.
	return const_cast<Method*>(&*_methods.emplace(name, id, returnType, internalMethod, flags, outerEntity));
}

inline StaticMethod* Struct::StructImpl::addStaticMethod(char const* name, std::size_t id, Type const& returnType,
														 ICallable* internalMethod, EMethodFlags flags, Struct const* outerEntity) noexcept
{
	assert(name != nullptr);
	assert((flags & EMethodFlags::Static) == EMethodFlags::Static);

	//The hash is based on the static method name which is immutable, so it's safe to const_cast to update other members.
	return const_cast<StaticMethod*>(&*_staticMethods.emplace(name, id, returnType, internalMethod, flags, outerEntity));
}

inline void Struct::StructImpl::addSharedInstantiator(StaticMethod const& instantiator) noexcept
{
	std::size_t parametersCount = instantiator.getParametersCount();

	//If it is a parameterless instantiator, use it as the (unique) default instantiator
	if (parametersCount == 0u)
	{
		if (!_sharedInstantiators.empty() && _sharedInstantiators[0]->getParametersCount() == 0u)
		{
			//There is already a default instantiator, so replace it
			_sharedInstantiators[0] = &instantiator;
		}
		else
		{
			//No default instantiator, add a new one
			_sharedInstantiators.insert(_sharedInstantiators.cbegin(), &instantiator);
		}
	}
	else
	{
		//Insert instantiators by ascendent parameters count
		for (auto it = _sharedInstantiators.cbegin(); it != _sharedInstantiators.cend(); it++)
		{
			if ((*it)->getParametersCount() >= parametersCount)
			{
				_sharedInstantiators.insert(it, &instantiator);
				return;
			}
		}

		//Couldn't insert the instantiator in-between elements, so add it at the end
		_sharedInstantiators.push_back(&instantiator);
	}
}

inline void Struct::StructImpl::addUniqueInstantiator(StaticMethod const& instantiator) noexcept
{
	std::size_t parametersCount = instantiator.getParametersCount();

	//If it is a parameterless instantiator, use it as the (unique) default instantiator
	if (parametersCount == 0u)
	{
		if (!_uniqueInstantiators.empty() && _uniqueInstantiators[0]->getParametersCount() == 0u)
		{
			//There is already a default instantiator, so replace it
			_uniqueInstantiators[0] = &instantiator;
		}
		else
		{
			//No default instantiator, add a new one
			_uniqueInstantiators.insert(_uniqueInstantiators.cbegin(), &instantiator);
		}
	}
	else
	{
		//Insert instantiators by ascendent parameters count
		for (auto it = _uniqueInstantiators.cbegin(); it != _uniqueInstantiators.cend(); it++)
		{
			if ((*it)->getParametersCount() >= parametersCount)
			{
				_uniqueInstantiators.insert(it, &instantiator);
				return;
			}
		}

		//Couldn't insert the instantiator in-between elements, so add it at the end
		_uniqueInstantiators.push_back(&instantiator);
	}
}

inline void Struct::StructImpl::setDirectParentsCapacity(std::size_t capacity) noexcept
{
	_directParents.reserve(capacity);
}

inline void Struct::StructImpl::setNestedArchetypesCapacity(std::size_t capacity) noexcept
{
	_nestedArchetypes.rehash(capacity);
}

inline void Struct::StructImpl::setFieldsCapacity(std::size_t capacity) noexcept
{
	_fields.reserve(capacity);
}

inline void Struct::StructImpl::setStaticFieldsCapacity(std::size_t capacity) noexcept
{
	_staticFields.reserve(capacity);
}

inline void Struct::StructImpl::setMethodsCapacity(std::size_t capacity) noexcept
{
	_methods.reserve(capacity);
}

inline void Struct::StructImpl::setStaticMethodsCapacity(std::size_t capacity) noexcept
{
	_staticMethods.reserve(capacity);
}

inline Archetype const* Struct::StructImpl::getNestedArchetype(char const* name, EAccessSpecifier access) const noexcept
{
	return Algorithm::getEntityByNameAndPredicate(_nestedArchetypes, name,
													  [access](Archetype const& archetype)
													  {
														  return access == EAccessSpecifier::Undefined || access == archetype.getAccessSpecifier();
													  });
}

inline bool Struct::StructImpl::getPointerOffset(Struct const& to, std::ptrdiff_t& out_pointerOffset) const noexcept
{
	auto it = _subclasses.find(&to);

	if (it != _subclasses.cend())
	{
		out_pointerOffset = it->second.pointerOffset;
		return true;
	}
	
	return false;
}

inline Struct::StructImpl::ParentStructs const& Struct::StructImpl::getDirectParents() const noexcept
{
	return _directParents;
}

inline Struct::StructImpl::Subclasses const& Struct::StructImpl::getSubclasses() const noexcept
{
	return _subclasses;
}

inline Struct::StructImpl::NestedArchetypes const& Struct::StructImpl::getNestedArchetypes() const noexcept
{
	return _nestedArchetypes;
}

inline Struct::StructImpl::Fields const& Struct::StructImpl::getFields() const noexcept
{
	return _fields;
}

inline Struct::StructImpl::StaticFields const& Struct::StructImpl::getStaticFields() const noexcept
{
	return _staticFields;
}

inline Struct::StructImpl::Methods const& Struct::StructImpl::getMethods() const noexcept
{
	return _methods;
}

inline Struct::StructImpl::StaticMethods const& Struct::StructImpl::getStaticMethods() const noexcept
{
	return _staticMethods;
}

inline Struct::StructImpl::Instantiators const& Struct::StructImpl::getSharedInstantiators() const noexcept
{
	return _sharedInstantiators;
}

inline Struct::StructImpl::Instantiators const& Struct::StructImpl::getUniqueInstantiators() const noexcept
{
	return _uniqueInstantiators;
}

inline EClassKind Struct::StructImpl::getClassKind() const noexcept
{
	return _classKind;
}