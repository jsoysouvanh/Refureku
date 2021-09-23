#include "Refureku/TypeInfo/Archetypes/Struct.h"

#include "Refureku/TypeInfo/Archetypes/Class.h"

using namespace rfk;

//////////////////////
//	Struct::Parent
//////////////////////
Struct::Parent::Parent(EAccessSpecifier	_inheritanceAccessSpecifier, Struct const& archetype) noexcept:
	_archetype{archetype},
	_inheritanceAccessSpecifier{_inheritanceAccessSpecifier}
{
}

Struct const& Struct::Parent::getArchetype() const noexcept
{
	return _archetype;
}

EAccessSpecifier Struct::Parent::getInheritanceAccessSpecifier() const noexcept
{
	return _inheritanceAccessSpecifier;
}


//////////////////////
//	Struct
//////////////////////
Struct::Struct(std::string&& name, std::size_t id, std::size_t memorySize, bool isClass, EClassKind classKind) noexcept:
	Archetype(std::forward<std::string>(name), id, isClass ? EEntityKind::Class : EEntityKind::Struct, memorySize),
	_classKind{classKind}
{
}

Struct::Struct(std::string&& name, std::size_t id, std::size_t memorySize, bool isClass) noexcept:
	Struct(std::forward<std::string>(name), id, memorySize, isClass, rfk::EClassKind::Standard)
{
}

Struct const* Struct::getNestedStruct(std::string structName, EAccessSpecifier access) const noexcept
{
	//Use an Entity instead of a Struct to avoid containers initialization
	Entity searchingStruct(std::move(structName), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	NestedArchetypes::const_iterator it = _nestedArchetypes.find(reinterpret_cast<Archetype const*>(&searchingStruct));

	return (it != _nestedArchetypes.cend() &&
			(*it)->getKind() == EEntityKind::Struct &&
			(access == EAccessSpecifier::Undefined || access == (*it)->getAccessSpecifier())) ?
				reinterpret_cast<Struct const*>(*it) : nullptr;
}

Class const* Struct::getNestedClass(std::string className, EAccessSpecifier access) const noexcept
{
	//Use an Entity instead of a Class to avoid containers initialization
	Entity searchingClass(std::move(className), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	NestedArchetypes::const_iterator it = _nestedArchetypes.find(reinterpret_cast<Archetype const*>(&searchingClass));

	return (it != _nestedArchetypes.cend() &&
			(*it)->getKind() == EEntityKind::Class &&
			(access == EAccessSpecifier::Undefined || access == (*it)->getAccessSpecifier())) ?
				reinterpret_cast<Class const*>(*it) : nullptr;
}

Enum const* Struct::getNestedEnum(std::string enumName, EAccessSpecifier access) const noexcept
{
	//Use an Entity instead of a Class to avoid containers initialization
	Entity searchingEnum(std::move(enumName), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	NestedArchetypes::const_iterator it = _nestedArchetypes.find(reinterpret_cast<Archetype const*>(&searchingEnum));

	return (it != _nestedArchetypes.cend() &&
			(*it)->getKind() == EEntityKind::Enum &&
			(access == EAccessSpecifier::Undefined || access == (*it)->getAccessSpecifier())) ?
				reinterpret_cast<Enum const*>(*it) : nullptr;
}

Field const* Struct::getField(std::string fieldName, EFieldFlags minFlags, bool shouldInspectInherited) const noexcept
{
	//Use an Entity instead of a Field to avoid memory / allocation overhead
	auto range = _fields.equal_range(static_cast<Field&&>(Entity(std::move(fieldName), 0u)));

	for (auto it = range.first; it != range.second; it++)
	{
		/**
		*	fields variable contains both this struct fields and inherited fields,
		*	make sure we check inherited fields only if requested
		*/
		if (shouldInspectInherited || it->getOuterEntity() == this)
		{
			//We found a field which has minFlags
			if ((it->getFlags() & minFlags) == minFlags)
			{
				return &*it;
			}
		}
	}

	return nullptr;
}

std::vector<Field const*> Struct::getFields(std::string fieldName, EFieldFlags minFlags, bool shouldInspectInherited) const noexcept
{
	std::vector<Field const*> result;

	//Use an Entity instead of a Field to avoid memory / allocation overhead
	auto range = _fields.equal_range(static_cast<Field&&>(Entity(std::move(fieldName), 0u)));

	//In case of full match, avoid reallocation
	result.reserve(std::distance(range.first, range.second));

	for (auto it = range.first; it != range.second; it++)
	{
		/**
		*	fields variable contains both this struct fields and inherited fields,
		*	make sure we check inherited fields only if requested
		*/
		if (shouldInspectInherited || it->getOuterEntity() == this)
		{
			//We found a field which has minFlags
			if ((it->getFlags() & minFlags) == minFlags)
			{
				result.emplace_back(&*it);
			}
		}
	}

	return result;
}

StaticField const* Struct::getStaticField(std::string fieldName, EFieldFlags minFlags, bool shouldInspectInherited) const noexcept
{
	//Use an Entity instead of a StaticField to avoid memory / allocation overhead
	auto range = staticFields.equal_range(static_cast<StaticField&&>(Entity(std::move(fieldName), 0u)));

	for (auto it = range.first; it != range.second; it++)
	{
		/**
		*	staticFields variable contains both this struct static fields and inherited static fields,
		*	make sure we check inherited fields only if requested
		*/
		if (shouldInspectInherited || it->getOuterEntity() == this)
		{
			//We found a field which has minFlags
			if ((it->getFlags() & minFlags) == minFlags)
			{
				return &*it;
			}
		}
	}

	return nullptr;
}

std::vector<StaticField const*> Struct::getStaticFields(std::string fieldName, EFieldFlags minFlags, bool shouldInspectInherited) const noexcept
{
	std::vector<StaticField const*> result;

	//Use an Entity instead of a StaticField to avoid memory / allocation overhead
	auto range = staticFields.equal_range(static_cast<StaticField&&>(Entity(std::move(fieldName), 0u)));

	//In case of full match, avoid reallocation
	result.reserve(std::distance(range.first, range.second));

	for (auto it = range.first; it != range.second; it++)
	{
		/**
		*	staticFields variable contains both this struct static fields and inherited static fields,
		*	make sure we check inherited fields only if requested
		*/
		if (shouldInspectInherited || it->getOuterEntity() == this)
		{
			//We found a field which has minFlags
			if ((it->getFlags() & minFlags) == minFlags)
			{
				result.emplace_back(&*it);
			}
		}
	}

	return result;
}

Method const* Struct::getMethod(std::string const& methodName, EMethodFlags minFlags, bool shouldInspectParents) const noexcept
{
	//Use an Entity instead of a Method to avoid memory / allocation overhead
	auto range = methods.equal_range(static_cast<Method&&>(Entity(std::string(methodName), 0u)));

	for (auto it = range.first; it != range.second; it++)
	{
		//We found a method which has minFlags
		if ((it->getFlags() & minFlags) == minFlags)
		{
			return &*it;
		}
	}

	//If we reach this point, couldn't find a valid method
	if (shouldInspectParents)
	{
		Method const* result = nullptr;

		for (Struct::Parent const& parent : _directParents)
		{
			result = parent.getArchetype().getMethod(methodName, minFlags, true);

			if (result != nullptr)
			{
				return result;
			}
		}
	}

	return nullptr;
}

std::vector<Method const*> Struct::getMethods(std::string const& methodName, EMethodFlags minFlags, bool shouldInspectParents) const noexcept
{
	std::vector<Method const*> result;

	//Use an Entity instead of a Method to avoid memory / allocation overhead
	auto range = methods.equal_range(static_cast<Method&&>(Entity(std::string(methodName), 0u)));

	for (auto it = range.first; it != range.second; it++)
	{
		//We found a method which has minFlags
		if ((it->getFlags() & minFlags) == minFlags)
		{
			result.emplace_back(&*it);
		}
	}

	//Search in parent too if needed
	if (shouldInspectParents)
	{
		std::vector<Method const*> parentResult;
		
		for (Struct::Parent const& parent : _directParents)
		{
			parentResult = parent.getArchetype().getMethods(methodName, minFlags, true);

			if (!parentResult.empty())
			{
				result.insert(result.end(), parentResult.begin(), parentResult.end());
			}
		}
	}

	return result;
}

StaticMethod const* Struct::getStaticMethod(std::string const& methodName, EMethodFlags minFlags, bool shouldInspectParents) const noexcept
{
	//Use an Entity instead of a StaticMethod to avoid memory / allocation overhead
	auto range = staticMethods.equal_range(static_cast<StaticMethod&&>(Entity(std::string(methodName), 0u)));

	for (auto it = range.first; it != range.second; it++)
	{
		//We found a method which has minFlags
		if ((it->getFlags() & minFlags) == minFlags)
		{
			return &*it;
		}
	}

	//If we reach this point, couldn't find a valid method
	if (shouldInspectParents)
	{
		StaticMethod const* result = nullptr;

		for (Struct::Parent const& parent : _directParents)
		{
			result = parent.getArchetype().getStaticMethod(methodName, minFlags, true);

			if (result != nullptr)
			{
				return result;
			}
		}
	}

	return nullptr;
}

std::vector<StaticMethod const*> Struct::getStaticMethods(std::string const& methodName, EMethodFlags minFlags, bool shouldInspectParents) const noexcept
{
	std::vector<StaticMethod const*> result;

	//Use an Entity instead of a StaticMethod to avoid memory / allocation overhead
	auto range = staticMethods.equal_range(static_cast<StaticMethod&&>(Entity(std::string(methodName), 0u)));

	for (auto it = range.first; it != range.second; it++)
	{
		//We found a method which has minFlags
		if ((it->getFlags() & minFlags) == minFlags)
		{
			result.emplace_back(&*it);
		}
	}

	//Search in parent too if needed
	if (shouldInspectParents)
	{
		std::vector<StaticMethod const*> parentResult;

		for (Struct::Parent const& parent : _directParents)
		{
			parentResult = parent.getArchetype().getStaticMethods(methodName, minFlags, true);

			if (!parentResult.empty())
			{
				result.insert(result.end(), parentResult.begin(), parentResult.end());
			}
		}
	}

	return result;
}

std::vector<Struct const*> Struct::getDirectSubclasses() const noexcept
{
	std::vector<Struct const*> result;

	for (Struct const* child : _subclasses)
	{
		//Search this struct in subclasses's parents
		for (Parent const& childParent : child->_directParents)
		{
			if (&childParent.getArchetype() == this)
			{
				result.emplace_back(child);
				break;
			}
		}
	}

	return result;
}

bool Struct::isSubclassOf(Struct const& otherType) const noexcept
{
	return &otherType != this && otherType.isBaseOf(*this);
}

bool Struct::isBaseOf(Struct const& otherType) const noexcept
{
	return &otherType == this || _subclasses.find(&otherType) != _subclasses.cend();
}

void Struct::setDefaultInstantiator(void* (*defaultInstantiator)()) noexcept
{
	_defaultInstantiator = defaultInstantiator;
}

void Struct::addParent(Struct const* parent, EAccessSpecifier inheritanceAccess) noexcept
{
	if (parent != nullptr)
	{
		_directParents.emplace_back(inheritanceAccess, *parent);

		//Inherit parent properties
		inheritProperties(*parent);
	}
}

Method* Struct::addMethod(std::string methodName, std::size_t entityId, Type const& returnType, std::unique_ptr<ICallable> internalMethod, EMethodFlags flags) noexcept
{
	assert((flags & EMethodFlags::Static) != EMethodFlags::Static);

	//Add the method to the container
	return const_cast<Method*>(&*methods.emplace(std::move(methodName), entityId, returnType, std::move(internalMethod), flags, this));
}

StaticMethod* Struct::addStaticMethod(std::string methodName, std::size_t entityId, Type const& returnType, std::unique_ptr<ICallable> internalMethod, EMethodFlags flags) noexcept
{
	assert((flags & EMethodFlags::Static) == EMethodFlags::Static);

	//Add the static method to the container
	return const_cast<StaticMethod*>(&*staticMethods.emplace(std::move(methodName), entityId, returnType, std::move(internalMethod), flags, this));
}

Field* Struct::addField(std::string	fieldName, std::size_t entityId, Type const& type, EFieldFlags flags, Struct const* outerEntity, std::size_t memoryOffset) noexcept
{
	assert((flags & EFieldFlags::Static) != EFieldFlags::Static);

	//Add the field to the container
	return const_cast<Field*>(&*_fields.emplace(std::move(fieldName), entityId, type, flags, this, memoryOffset, outerEntity));
}

StaticField* Struct::addStaticField(std::string fieldName, std::size_t entityId, Type const& type, EFieldFlags flags, Struct const* outerEntity, void* fieldPtr) noexcept
{
	assert((flags & EFieldFlags::Static) == EFieldFlags::Static);

	//Add the static field to the container
	//The first const_cast is here so that we can set the outerEntity field. It doesn't change the hash value so it won't break the unordered_multiset.
	return const_cast<StaticField*>(&*staticFields.emplace(std::move(fieldName), entityId, type, flags, this, fieldPtr, outerEntity));
}

StaticField* Struct::addStaticField(std::string fieldName, std::size_t entityId, Type const& type, EFieldFlags flags, Struct const* outerEntity, void const* fieldPtr) noexcept
{
	assert((flags & EFieldFlags::Static) == EFieldFlags::Static);

	//Add the static field to the container
	//The first const_cast is here so that we can set the outerEntity field. It doesn't change the hash value so it won't break the unordered_multiset.
	return const_cast<StaticField*>(&*staticFields.emplace(std::move(fieldName), entityId, type, flags, this, fieldPtr, outerEntity));
}

Archetype* Struct::addNestedArchetype(Archetype const* nestedArchetype, EAccessSpecifier accessSpecifier) noexcept
{
	//Add the archetype to the container
	Archetype* result = const_cast<Archetype*>(*_nestedArchetypes.emplace(nestedArchetype).first);

	result->setAccessSpecifier(accessSpecifier);
	result->setOuterEntity(this);

	return result;
}

EClassKind Struct::getClassKind() const noexcept
{
	return _classKind;
}

Struct::Parent const& Struct::getDirectParentAt(std::size_t index) const
{
	return _directParents.at(index);
}

std::size_t Struct::getDirectParentsCount() const noexcept
{
	return _directParents.size();
}

void Struct::setDirectParentsCapacity(std::size_t capacity) noexcept
{
	_directParents.reserve(capacity);
}

void Struct::addSubclass(Struct const& subclass) noexcept
{
	_subclasses.insert(&subclass);
}

void Struct::foreachNestedArchetype(bool (*visitor)(Archetype const&, void*), void* userData) const noexcept
{
	if (visitor != nullptr)
	{
		for (Archetype const* nestedArchetype : _nestedArchetypes)
		{
			if (!visitor(*nestedArchetype, userData))
			{
				return;
			}
		}
	}
}

void Struct::setNestedArchetypesCapacity(std::size_t capacity) noexcept
{
	_nestedArchetypes.reserve(capacity);
}

void Struct::foreachField(bool (*visitor)(Field const&, void*), void* userData) const noexcept
{
	if (visitor != nullptr)
	{
		for (Field const& field : _fields)
		{
			if (!visitor(field, userData))
			{
				return;
			}
		}
	}
}

void Struct::setFieldsCapacity(std::size_t capacity) noexcept
{
	_fields.reserve(capacity);
}

//TODO: TEST
//template <typename Predicate, typename>
//Archetype const* Struct::getNestedArchetype(Predicate predicate) const
//{
//	struct Data
//	{
//		Predicate			predicate;
//		Archetype const*	result = nullptr;
//	} data;
//
//	foreachNestedArchetype([](Archetype const& archetype, void* userData)
//						   {
//							   Data* data = reinterpret_cast<Data*>(userData);
//
//							   if (data.predicate(archetype))
//							   {
//								   data->result = &archetype;
//								   return false;
//							   }
//
//							   return true;
//						   }, &data);
//
//	return data.result;
//
//	/*for (Archetype const* archetype : nestedArchetypes)
//	{
//		if (predicate(archetype))
//		{
//			return archetype;
//		}
//	}
//
//	return nullptr;*/
//}
//END TODO: TEST