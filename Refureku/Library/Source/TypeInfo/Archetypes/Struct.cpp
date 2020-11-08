#include "Refureku/TypeInfo/Archetypes/Struct.h"

#include "Refureku/TypeInfo/Archetypes/Class.h"

using namespace rfk;

Struct::Struct(std::string&& name, uint64 id, EEntityKind kind, uint64 memorySize) noexcept:
	Archetype(std::forward<std::string>(name), id, kind, memorySize)
{
}

Struct::Struct(std::string&& newName, uint64 newId, uint64 newMemorySize) noexcept:
	Struct(std::forward<std::string>(newName), newId, EEntityKind::Struct, newMemorySize)
{
}

Struct const* Struct::getNestedStruct(std::string structName, EAccessSpecifier access) const noexcept
{
	//Use an Entity instead of a Struct to avoid containers initialization
	Entity searchingStruct(std::move(structName), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(nestedArchetypes)::const_iterator it = nestedArchetypes.find(reinterpret_cast<Archetype const*>(&searchingStruct));

	return (it != nestedArchetypes.cend() &&
			(*it)->kind == EEntityKind::Struct &&
			(access == EAccessSpecifier::Undefined || access == (*it)->accessSpecifier)) ?
				reinterpret_cast<Struct const*>(*it) : nullptr;
}

Class const* Struct::getNestedClass(std::string className, EAccessSpecifier access) const noexcept
{
	//Use an Entity instead of a Class to avoid containers initialization
	Entity searchingClass(std::move(className), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(nestedArchetypes)::const_iterator it = nestedArchetypes.find(reinterpret_cast<Archetype const*>(&searchingClass));

	return (it != nestedArchetypes.cend() &&
			(*it)->kind == EEntityKind::Class &&
			(access == EAccessSpecifier::Undefined || access == (*it)->accessSpecifier)) ?
				reinterpret_cast<Class const*>(*it) : nullptr;
}

Enum const* Struct::getNestedEnum(std::string enumName, EAccessSpecifier access) const noexcept
{
	//Use an Entity instead of a Class to avoid containers initialization
	Entity searchingEnum(std::move(enumName), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(nestedArchetypes)::const_iterator it = nestedArchetypes.find(reinterpret_cast<Archetype const*>(&searchingEnum));

	return (it != nestedArchetypes.cend() &&
			(*it)->kind == EEntityKind::Enum &&
			(access == EAccessSpecifier::Undefined || access == (*it)->accessSpecifier)) ?
				reinterpret_cast<Enum const*>(*it) : nullptr;
}

Field const* Struct::getField(std::string fieldName, EFieldFlags minFlags, bool shouldInspectInherited) const noexcept
{
	//Use an Entity instead of a Field to avoid memory / allocation overhead
	auto range = fields.equal_range(static_cast<Field&&>(Entity(std::move(fieldName), 0u)));

	for (auto it = range.first; it != range.second; it++)
	{
		/**
		*	fields variable contains both this struct fields and inherited fields,
		*	make sure we check inherited fields only if requested
		*/
		if (shouldInspectInherited || it->outerEntity == this)
		{
			//We found a field which has minFlags
			if ((it->flags & minFlags) == minFlags)
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
	auto range = fields.equal_range(static_cast<Field&&>(Entity(std::move(fieldName), 0u)));

	//In case of full match, avoid reallocation
	result.reserve(std::distance(range.first, range.second));

	for (auto it = range.first; it != range.second; it++)
	{
		/**
		*	fields variable contains both this struct fields and inherited fields,
		*	make sure we check inherited fields only if requested
		*/
		if (shouldInspectInherited || it->outerEntity == this)
		{
			//We found a field which has minFlags
			if ((it->flags & minFlags) == minFlags)
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
		if (shouldInspectInherited || it->outerEntity == this)
		{
			//We found a field which has minFlags
			if ((it->flags & minFlags) == minFlags)
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
		if (shouldInspectInherited || it->outerEntity == this)
		{
			//We found a field which has minFlags
			if ((it->flags & minFlags) == minFlags)
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
		if ((it->flags & minFlags) == minFlags)
		{
			return &*it;
		}
	}

	//If we reach this point, couldn't find a valid method
	if (shouldInspectParents)
	{
		Method const* result = nullptr;

		for (Struct::Parent const& parent : directParents)
		{
			result = parent.type->getMethod(methodName, minFlags, true);

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
		if ((it->flags & minFlags) == minFlags)
		{
			result.emplace_back(&*it);
		}
	}

	//Search in parent too if needed
	if (shouldInspectParents)
	{
		std::vector<Method const*> parentResult;
		
		for (Struct::Parent const& parent : directParents)
		{
			parentResult = parent.type->getMethods(methodName, minFlags, true);

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
		if ((it->flags & minFlags) == minFlags)
		{
			return &*it;
		}
	}

	//If we reach this point, couldn't find a valid method
	if (shouldInspectParents)
	{
		StaticMethod const* result = nullptr;

		for (Struct::Parent const& parent : directParents)
		{
			result = parent.type->getStaticMethod(methodName, minFlags, true);

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
		if ((it->flags & minFlags) == minFlags)
		{
			result.emplace_back(&*it);
		}
	}

	//Search in parent too if needed
	if (shouldInspectParents)
	{
		std::vector<StaticMethod const*> parentResult;

		for (Struct::Parent const& parent : directParents)
		{
			parentResult = parent.type->getStaticMethods(methodName, minFlags, true);

			if (!parentResult.empty())
			{
				result.insert(result.end(), parentResult.begin(), parentResult.end());
			}
		}
	}

	return result;
}

bool Struct::inheritsFrom(Struct const& otherType) const noexcept
{
	for (Parent const& parent : directParents)
	{
		if (parent.type == &otherType || parent.type->inheritsFrom(otherType))
		{
			return true;
		}
	}

	return false;
}

bool Struct::isBaseOf(Struct const& otherType) const noexcept
{
	return &otherType == this || children.find(&otherType) != children.cend();
}

void Struct::setDefaultInstantiationMethod(void* (*func)() noexcept) noexcept
{
	_defaultInstantiator = func;
}

Method* Struct::addMethod(std::string methodName, uint64 entityId, Type const& returnType, std::unique_ptr<ICallable> internalMethod, EMethodFlags flags) noexcept
{
	assert((flags & EMethodFlags::Static) != EMethodFlags::Static);

	//Add the method to the container
	Method* result = const_cast<Method*>(&*methods.emplace(std::move(methodName), entityId, returnType, std::move(internalMethod), flags));

	//Set outer entity
	result->outerEntity = this;

	return result;
}

StaticMethod* Struct::addStaticMethod(std::string methodName, uint64 entityId, Type const& returnType, std::unique_ptr<ICallable> internalMethod, EMethodFlags flags) noexcept
{
	assert((flags & EMethodFlags::Static) == EMethodFlags::Static);

	//Add the static method to the container
	StaticMethod* result = const_cast<StaticMethod*>(&*staticMethods.emplace(std::move(methodName), entityId, returnType, std::move(internalMethod), flags));

	//Set outer entity
	result->outerEntity = this;

	return result;
}

Field* Struct::addField(std::string	fieldName, uint64 entityId, Type const& type, EFieldFlags flags, Struct const* outerEntity_, uint64 memoryOffset) noexcept
{
	assert((flags & EFieldFlags::Static) != EFieldFlags::Static);

	//Add the field to the container
	Field* result = const_cast<Field*>(&*fields.emplace(std::move(fieldName), entityId, type, flags, this, memoryOffset));

	//Set outer entity
	result->outerEntity = outerEntity_;

	return result;
}

StaticField* Struct::addStaticField(std::string fieldName, uint64 entityId, Type const& type, EFieldFlags flags, Struct const* outerEntity_, void* fieldPtr) noexcept
{
	assert((flags & EFieldFlags::Static) == EFieldFlags::Static);

	//Add the static field to the container
	StaticField* result = const_cast<StaticField*>(&*staticFields.emplace(std::move(fieldName), entityId, type, flags, this, fieldPtr));

	//Set outer entity
	result->outerEntity = outerEntity_;

	return result;
}

Archetype* Struct::addNestedArchetype(Archetype const* nestedArchetype, EAccessSpecifier accessSpecifier_) noexcept
{
	//Add the archetype to the container
	Archetype* result = const_cast<Archetype*>(*nestedArchetypes.emplace(nestedArchetype).first);

	//Set the access specifier
	result->accessSpecifier = accessSpecifier_;

	//Set outer entity
	result->outerEntity = this;

	return result;
}