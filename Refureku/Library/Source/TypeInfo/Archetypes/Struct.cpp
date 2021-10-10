#include "Refureku/TypeInfo/Archetypes/Struct.h"

#include "Refureku/TypeInfo/Archetypes/StructImpl.h"
#include "Refureku/TypeInfo/Archetypes/Enum.h"
#include "Refureku/TypeInfo/Entity/EntityUtility.h"

using namespace rfk;

template class REFUREKU_TEMPLATE_API_DEF rfk::Allocator<Struct const*>;
template class REFUREKU_TEMPLATE_API_DEF rfk::Vector<Struct const*, rfk::Allocator<Struct const*>>;

Struct::Struct(char const* name, std::size_t id, std::size_t memorySize, bool isClass, EClassKind classKind) noexcept:
	Archetype(new StructImpl(name, id, memorySize, isClass, classKind))
{
}

Struct::Struct(char const* name, std::size_t id, std::size_t memorySize, bool isClass) noexcept:
	Struct(name, id, memorySize, isClass, EClassKind::Standard)
{
}

Struct::Struct(StructImpl* implementation) noexcept:
	Archetype(implementation)
{
}

Struct::~Struct() noexcept = default;

rfk::Vector<Struct const*> Struct::getDirectSubclasses() const noexcept
{
	rfk::Vector<Struct const*> result;

	for (Struct const* subclass : reinterpret_cast<StructImpl const*>(getPimpl())->getSubclasses())
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

bool Struct::isSubclassOf(Struct const& archetype) const noexcept
{
	return &archetype != this && archetype.isBaseOf(*this);
}

bool Struct::isBaseOf(Struct const& archetype) const noexcept
{
	auto const& subclasses = reinterpret_cast<StructImpl const*>(getPimpl())->getSubclasses();

	return &archetype == this || subclasses.find(&archetype) != subclasses.cend();
}

EClassKind Struct::getClassKind() const noexcept
{
	return reinterpret_cast<StructImpl const*>(getPimpl())->getClassKind();
}

ParentStruct const& Struct::getDirectParentAt(std::size_t index) const noexcept
{
	return reinterpret_cast<StructImpl const*>(getPimpl())->getDirectParents()[index];
}

std::size_t Struct::getDirectParentsCount() const noexcept
{
	return reinterpret_cast<StructImpl const*>(getPimpl())->getDirectParents().size();
}

bool Struct::foreachDirectParent(Visitor<ParentStruct> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(reinterpret_cast<StructImpl const*>(getPimpl())->getDirectParents(), visitor, userData);
}

Struct const* Struct::getNestedStructByName(char const* name, EAccessSpecifier access) const noexcept
{
	Archetype const* foundArchetype = reinterpret_cast<StructImpl const*>(getPimpl())->getNestedArchetype(name, access);

	return (foundArchetype != nullptr && foundArchetype->getKind() == EEntityKind::Struct) ?
				reinterpret_cast<Struct const*>(foundArchetype) :
				nullptr;
}

Struct const* Struct::getNestedStructByPredicate(Predicate<Struct> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		reinterpret_cast<Struct const*>(
			EntityUtility::getEntityByPredicate(reinterpret_cast<StructImpl const*>(getPimpl())->getNestedArchetypes(),
												   [predicate, userData](Archetype const& archetype)
												   {
													   return archetype.getKind() == EEntityKind::Struct && predicate(static_cast<Struct const&>(archetype), userData);
												   })) : nullptr;
}

Vector<Struct const*> Struct::getNestedStructsByPredicate(Predicate<Struct> predicate, void* userData) const
{
	if (predicate != nullptr)
	{
		return EntityUtility::getEntitiesByPredicate(reinterpret_cast<StructImpl const*>(getPimpl())->getNestedArchetypes(),
													 [predicate, userData](Archetype const& archetype)
													 {
														 return archetype.getKind() == EEntityKind::Struct && predicate(static_cast<Struct const&>(archetype), userData);
													 });
	}
	else
	{
		return Vector<Struct const*>(0);
	}
}

Class const* Struct::getNestedClassByName(char const* name, EAccessSpecifier access) const noexcept
{
	Archetype const* foundArchetype = reinterpret_cast<StructImpl const*>(getPimpl())->getNestedArchetype(name, access);

	return (foundArchetype != nullptr && foundArchetype->getKind() == EEntityKind::Class) ?
				reinterpret_cast<Class const*>(foundArchetype) :
				nullptr;
}

Class const* Struct::getNestedClassByPredicate(Predicate<Class> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		reinterpret_cast<Class const*>(
			EntityUtility::getEntityByPredicate(reinterpret_cast<StructImpl const*>(getPimpl())->getNestedArchetypes(),
			[predicate, userData](Archetype const& archetype)
			{
				return archetype.getKind() == EEntityKind::Class && predicate(static_cast<Class const&>(archetype), userData);
			})) : nullptr;
}

Vector<Class const*> Struct::getNestedClassesByPredicate(Predicate<Class> predicate, void* userData) const
{
	if (predicate != nullptr)
	{
		return EntityUtility::getEntitiesByPredicate(reinterpret_cast<StructImpl const*>(getPimpl())->getNestedArchetypes(),
													 [predicate, userData](Archetype const& archetype)
													 {
														 return archetype.getKind() == EEntityKind::Class && predicate(static_cast<Class const&>(archetype), userData);
													 });
	}
	else
	{
		return Vector<Class const*>(0);
	}
}

Enum const* Struct::getNestedEnumByName(char const* name, EAccessSpecifier access) const noexcept
{
	Archetype const* foundArchetype = reinterpret_cast<StructImpl const*>(getPimpl())->getNestedArchetype(name, access);

	return (foundArchetype != nullptr && foundArchetype->getKind() == EEntityKind::Enum) ?
				reinterpret_cast<Enum const*>(foundArchetype) :
				nullptr;
}

Enum const* Struct::getNestedEnumByPredicate(Predicate<Enum> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		reinterpret_cast<Enum const*>(
			EntityUtility::getEntityByPredicate(reinterpret_cast<StructImpl const*>(getPimpl())->getNestedArchetypes(),
			[predicate, userData](Archetype const& archetype)
			{
				return archetype.getKind() == EEntityKind::Enum && predicate(static_cast<Enum const&>(archetype), userData);
			})) : nullptr;
}

Vector<Enum const*> Struct::getNestedEnumsByPredicate(Predicate<Enum> predicate, void* userData) const
{
	if (predicate != nullptr)
	{
		return EntityUtility::getEntitiesByPredicate(reinterpret_cast<StructImpl const*>(getPimpl())->getNestedArchetypes(),
													 [predicate, userData](Archetype const& archetype)
													 {
														 return archetype.getKind() == EEntityKind::Enum && predicate(static_cast<Enum const&>(archetype), userData);
													 });
	}
	else
	{
		return Vector<Enum const*>(0);
	}
}

bool Struct::foreachNestedArchetype(Visitor<Archetype> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(reinterpret_cast<StructImpl const*>(getPimpl())->getNestedArchetypes(), visitor, userData);
}

Field const* Struct::getFieldByName(char const* name, EFieldFlags minFlags, bool shouldInspectInherited) const noexcept
{
	Field const* result = nullptr;

	EntityUtility::foreachEntityNamed(reinterpret_cast<StructImpl const*>(getPimpl())->getFields(),
									  name,
									  [this, &result, minFlags, shouldInspectInherited](Field const& field)
									  {
										  /**
										  *	fields variable contains both this struct fields and inherited fields,
										  *	make sure we check inherited fields only if requested
										  */
										  if (shouldInspectInherited || field.getOuterEntity() == this)
										  {
											  if ((field.getFlags() & minFlags) == minFlags)
											  {
												  //We found a field that satisfies minFlags
												  result = &field;
												  return false;
											  }
										  }

										  return true;
									  });

	return result;
}

Field const* Struct::getFieldByPredicate(Predicate<Field> predicate, void* userData, bool shouldInspectInherited) const
{
	return (predicate != nullptr) ?
		EntityUtility::getEntityByPredicate(reinterpret_cast<StructImpl const*>(getPimpl())->getFields(),
		[this, predicate, userData, shouldInspectInherited](Field const& field)
		{
			return	field.getKind() == EEntityKind::Field &&
					(shouldInspectInherited || field.getOuterEntity() == this) &&
					predicate(static_cast<Field const&>(field), userData);
		}) : nullptr;
}

Vector<Field const*> Struct::getFieldsByPredicate(Predicate<Field> predicate, void* userData, bool shouldInspectInherited) const
{
	if (predicate != nullptr)
	{
		return EntityUtility::getEntitiesByPredicate(reinterpret_cast<StructImpl const*>(getPimpl())->getFields(),
													 [this, predicate, userData, shouldInspectInherited](Field const& field)
													 {
														 return	field.getKind() == EEntityKind::Field &&
																(shouldInspectInherited || field.getOuterEntity() == this) &&
																predicate(static_cast<Field const&>(field), userData);
													 });
	}
	else
	{
		return Vector<Field const*>(0);
	}
}

bool Struct::foreachField(Visitor<Field> visitor, void* userData, bool shouldInspectInherited) const
{
	return EntityUtility::foreachEntity(reinterpret_cast<StructImpl const*>(getPimpl())->getFields(),
										[this, visitor, userData, shouldInspectInherited](Field const& field)
										{
											return (shouldInspectInherited || field.getOuterEntity() == this) ? visitor(field, userData) : true;
										});
}

StaticField const* Struct::getStaticFieldByName(char const* name, EFieldFlags minFlags, bool shouldInspectInherited) const noexcept
{
	StaticField const* result = nullptr;

	EntityUtility::foreachEntityNamed(reinterpret_cast<StructImpl const*>(getPimpl())->getStaticFields(),
									  name,
									  [this, &result, minFlags, shouldInspectInherited](StaticField const& staticField)
									  {
										  /**
										  *	static fields container contains both this struct static fields and inherited static fields,
										  *	make sure we check inherited fields only if requested
										  */
										  if (shouldInspectInherited || staticField.getOuterEntity() == this)
										  {
											  if ((staticField.getFlags() & minFlags) == minFlags)
											  {
												  //We found a static field that satisfies minFlags
												  result = &staticField;
												  return false;
											  }
										  }
										  
										  return true;
									  });

	return result;
}

StaticField const* Struct::getStaticFieldByPredicate(Predicate<StaticField> predicate, void* userData, bool shouldInspectInherited) const
{
	return (predicate != nullptr) ?
		EntityUtility::getEntityByPredicate(reinterpret_cast<StructImpl const*>(getPimpl())->getStaticFields(),
											[this, predicate, userData, shouldInspectInherited](StaticField const& staticField)
											{
												return (shouldInspectInherited || staticField.getOuterEntity() == this) && predicate(staticField, userData);
											}) : nullptr;
}

Vector<StaticField const*> Struct::getStaticFieldsByPredicate(Predicate<StaticField> predicate, void* userData, bool shouldInspectInherited) const
{
	if (predicate != nullptr)
	{
		return EntityUtility::getEntitiesByPredicate(reinterpret_cast<StructImpl const*>(getPimpl())->getStaticFields(),
													 [this, predicate, userData, shouldInspectInherited](StaticField const& staticField)
													 {
														 return (shouldInspectInherited || staticField.getOuterEntity() == this) && predicate(staticField, userData);
													 });
	}
	else
	{
		return Vector<StaticField const*>(0);
	}
}

bool Struct::foreachStaticField(Visitor<StaticField> visitor, void* userData, bool shouldInspectInherited) const
{
	return EntityUtility::foreachEntity(reinterpret_cast<StructImpl const*>(getPimpl())->getStaticFields(),
										[this, visitor, userData, shouldInspectInherited](StaticField const& staticField)
										{
											return (shouldInspectInherited || staticField.getOuterEntity() == this) ? visitor(staticField, userData) : true;
										});
}

Method const* Struct::getMethodByName(char const* name, EMethodFlags minFlags, bool shouldInspectInherited) const noexcept
{
	StructImpl const*	structImpl	= reinterpret_cast<StructImpl const*>(getPimpl());
	Method const*		result		= nullptr;

	bool foundMethod = !EntityUtility::foreachEntityNamed(structImpl->getMethods(),
									  name,
									  [&result, minFlags](Method const& method)
									  {
										  if ((method.getFlags() & minFlags) == minFlags)
										  {
											  //We found a method that satisfies minFlags
											  result = &method;
											  return false;
										  }

										  return true;
									  });

	if (foundMethod)
	{
		return result;
	}
	else
	{
		//If we reach this point, couldn't find a valid method
		if (shouldInspectInherited)
		{
			for (ParentStruct const& parent : structImpl->getDirectParents())
			{
				result = parent.getArchetype().getMethodByName(name, minFlags, true);

				if (result != nullptr)
				{
					return result;
				}
			}
		}

		return nullptr;
	}
}

Vector<Method const*> Struct::getMethodsByName(char const* name, EMethodFlags minFlags, bool shouldInspectInherited) const noexcept
{
	//Users using this method likely are waiting for at least 2 results, so default capacity to 2.
	Vector<Method const*>	result(2);
	StructImpl const*		structImpl = reinterpret_cast<StructImpl const*>(getPimpl());

	EntityUtility::foreachEntityNamed(structImpl->getMethods(),
									 name,
									 [&result, minFlags](Method const& method)
									 {
										 if ((method.getFlags() & minFlags) == minFlags)
										 {
											 //We found a method that satisfies minFlags
											 result.push_back(&method);
										 }

										 return true;
									 });

	if (shouldInspectInherited)
	{
		for (ParentStruct const& parent : structImpl->getDirectParents())
		{
			result.push_back(parent.getArchetype().getMethodsByName(name, minFlags, true));
		}
	}

	return result;
}

Method const* Struct::getMethodByPredicate(Predicate<Method> predicate, void* userData, bool shouldInspectInherited) const
{
	if (predicate != nullptr)
	{
		StructImpl const*	structImpl	= reinterpret_cast<StructImpl const*>(getPimpl());
		Method const*		result		= EntityUtility::getEntityByPredicate(structImpl->getMethods(), predicate, userData);

		if (result != nullptr)
		{
			return result;
		}
		else if (shouldInspectInherited)
		{
			for (ParentStruct const& parent : structImpl->getDirectParents())
			{
				result = parent.getArchetype().getMethodByPredicate(predicate, userData, true);

				if (result != nullptr)
				{
					return result;
				}
			}
		}
	}

	return nullptr;
}

Vector<Method const*> Struct::getMethodsByPredicate(Predicate<Method> predicate, void* userData, bool shouldInspectInherited) const
{
	if (predicate != nullptr)
	{
		StructImpl const*		structImpl = reinterpret_cast<StructImpl const*>(getPimpl());
		Vector<Method const*>	result(2);

		result.push_back(EntityUtility::getEntitiesByPredicate(structImpl->getMethods(), predicate, userData));

		if (shouldInspectInherited)
		{
			for (ParentStruct const& parent : structImpl->getDirectParents())
			{
				result.push_back(parent.getArchetype().getMethodsByPredicate(predicate, userData, true));
			}
		}

		return result;
	}
	else
	{
		return Vector<Method const*>(0);
	}
}

bool Struct::foreachMethod(Visitor<Method> visitor, void* userData, bool shouldInspectInherited) const
{
	StructImpl const*	structImpl	= reinterpret_cast<StructImpl const*>(getPimpl());
	bool				result		= EntityUtility::foreachEntity(structImpl->getMethods(), visitor, userData);

	//Iterate on parent methods if necessary
	if (shouldInspectInherited)
	{
		std::size_t i = 0u;
		auto const&	directParents = structImpl->getDirectParents();

		while (result && i < directParents.size())
		{
			result &= directParents[i].getArchetype().foreachMethod(visitor, userData, true);
			i++;
		}
	}

	return result;
}

StaticMethod const* Struct::getStaticMethodByName(char const* name, EMethodFlags minFlags, bool shouldInspectInherited) const noexcept
{
	StructImpl const*	structImpl	= reinterpret_cast<StructImpl const*>(getPimpl());
	StaticMethod const*	result		= nullptr;

	bool foundMethod = !EntityUtility::foreachEntityNamed(structImpl->getStaticMethods(),
														 name,
														 [&result, minFlags](StaticMethod const& staticMethod)
														 {
															 if ((staticMethod.getFlags() & minFlags) == minFlags)
															 {
																 //We found a static method that satisfies minFlags
																 result = &staticMethod;
																 return false;
															 }

															 return true;
														 });

	if (foundMethod)
	{
		return result;
	}
	else
	{
		//If we reach this point, couldn't find a valid static method
		if (shouldInspectInherited)
		{
			for (ParentStruct const& parent : structImpl->getDirectParents())
			{
				result = parent.getArchetype().getStaticMethodByName(name, minFlags, true);

				if (result != nullptr)
				{
					return result;
				}
			}
		}

		return nullptr;
	}
}

Vector<StaticMethod const*> Struct::getStaticMethodsByName(char const* name, EMethodFlags minFlags, bool shouldInspectInherited) const noexcept
{
	//Users using this method likely are waiting for at least 2 results, so default capacity to 2.
	Vector<StaticMethod const*>	result(2);
	StructImpl const*				structImpl = reinterpret_cast<StructImpl const*>(getPimpl());

	EntityUtility::foreachEntityNamed(structImpl->getStaticMethods(),
								   	 name,
								   	 [&result, minFlags](StaticMethod const& staticMethod)
								   	 {
								   		 if ((staticMethod.getFlags() & minFlags) == minFlags)
								   		 {
								   			 //We found a static method that satisfies minFlags
								   			 result.push_back(&staticMethod);
								   		 }
								   
								   		 return true;
								   	 });

	//If we reach this point, couldn't find a valid method
	if (shouldInspectInherited)
	{
		for (ParentStruct const& parent : structImpl->getDirectParents())
		{
			result.push_back(parent.getArchetype().getStaticMethodsByName(name, minFlags, true));
		}
	}

	return result;
}

StaticMethod const* Struct::getStaticMethodByPredicate(Predicate<StaticMethod> predicate, void* userData, bool shouldInspectInherited) const
{
	if (predicate != nullptr)
	{
		StructImpl const*	structImpl	= reinterpret_cast<StructImpl const*>(getPimpl());
		StaticMethod const*	result		= EntityUtility::getEntityByPredicate(structImpl->getStaticMethods(), predicate, userData);

		if (result != nullptr)
		{
			return result;
		}
		else if (shouldInspectInherited)
		{
			for (ParentStruct const& parent : structImpl->getDirectParents())
			{
				result = parent.getArchetype().getStaticMethodByPredicate(predicate, userData, true);

				if (result != nullptr)
				{
					return result;
				}
			}
		}
	}

	return nullptr;
}

Vector<StaticMethod const*> Struct::getStaticMethodsByPredicate(Predicate<StaticMethod> predicate, void* userData, bool shouldInspectInherited) const
{
	if (predicate != nullptr)
	{
		StructImpl const*			structImpl = reinterpret_cast<StructImpl const*>(getPimpl());
		Vector<StaticMethod const*>	result(2);

		result.push_back(EntityUtility::getEntitiesByPredicate(structImpl->getStaticMethods(), predicate, userData));

		if (shouldInspectInherited)
		{
			for (ParentStruct const& parent : structImpl->getDirectParents())
			{
				result.push_back(parent.getArchetype().getStaticMethodsByPredicate(predicate, userData, true));
			}
		}

		return result;
	}
	else
	{
		return Vector<StaticMethod const*>(0);
	}
}

bool Struct::foreachStaticMethod(Visitor<StaticMethod> visitor, void* userData, bool shouldInspectInherited) const
{
	StructImpl const*	structImpl	= reinterpret_cast<StructImpl const*>(getPimpl());
	bool				result		= EntityUtility::foreachEntity(structImpl->getStaticMethods(), visitor, userData);

	//Iterate on parent static methods if necessary
	if (shouldInspectInherited)
	{
		std::size_t i = 0u;
		auto const&	directParents = structImpl->getDirectParents();

		while (result && i < directParents.size())
		{
			result &= directParents[i].getArchetype().foreachStaticMethod(visitor, userData, true);
			i++;
		}
	}

	return result;
}

ClassTemplate const* Struct::asTemplate() const noexcept
{
	return (getClassKind() == EClassKind::Template) ?
		reinterpret_cast<ClassTemplate const*>(this) : nullptr;
}

ClassTemplateInstantiation const* Struct::asTemplateInstantiation() const noexcept
{
	return (getClassKind() == EClassKind::TemplateInstantiation) ?
		reinterpret_cast<ClassTemplateInstantiation const*>(this) : nullptr;
}

void Struct::addDirectParent(Archetype const* archetype, EAccessSpecifier inheritanceAccess) noexcept
{
	if (archetype != nullptr)
	{
		assert(archetype->getKind() == EEntityKind::Struct || archetype->getKind() == EEntityKind::Class);

		reinterpret_cast<StructImpl*>(getPimpl())->addDirectParent(*reinterpret_cast<Struct const*>(archetype), inheritanceAccess);
	}
}

void Struct::setDirectParentsCapacity(std::size_t capacity) noexcept
{
	reinterpret_cast<StructImpl*>(getPimpl())->setDirectParentsCapacity(capacity);
}

void Struct::addSubclass(Struct const& subclass) noexcept
{
	reinterpret_cast<StructImpl*>(getPimpl())->addSubclass(subclass);
}

Archetype* Struct::addNestedArchetype(Archetype const* nestedArchetype, EAccessSpecifier accessSpecifier) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->addNestedArchetype(nestedArchetype, accessSpecifier, this);
}

void Struct::setNestedArchetypesCapacity(std::size_t capacity) noexcept
{
	reinterpret_cast<StructImpl*>(getPimpl())->setNestedArchetypesCapacity(capacity);
}

Field* Struct::addField(char const* name, std::size_t id, Type const& type,
							  EFieldFlags flags, std::size_t memoryOffset, Struct const* outerEntity) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->addField(name, id, type, flags, this, memoryOffset, outerEntity);
}

void Struct::setFieldsCapacity(std::size_t capacity) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->setFieldsCapacity(capacity);
}

StaticField* Struct::addStaticField(char const* name, std::size_t id, Type const& type,
										  EFieldFlags flags, void* fieldPtr, Struct const* outerEntity) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->addStaticField(name, id, type, flags, this, fieldPtr, outerEntity);
}

StaticField* Struct::addStaticField(char const* name, std::size_t id, Type const& type,
										  EFieldFlags flags, void const* fieldPtr, Struct const* outerEntity) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->addStaticField(name, id, type, flags, this, fieldPtr, outerEntity);
}

void Struct::setStaticFieldsCapacity(std::size_t capacity) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->setStaticFieldsCapacity(capacity);
}

Method* Struct::addMethod(char const* name, std::size_t id,
								Type const& returnType, ICallable* internalMethod, EMethodFlags flags) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->addMethod(name, id, returnType, internalMethod, flags, this);
}

void Struct::setMethodsCapacity(std::size_t capacity) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->setMethodsCapacity(capacity);
}

StaticMethod* Struct::addStaticMethod(char const* name, std::size_t id,
											Type const& returnType, ICallable* internalMethod, EMethodFlags flags) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->addStaticMethod(name, id, returnType, internalMethod, flags, this);
}

void Struct::setStaticMethodsCapacity(std::size_t capacity) noexcept
{
	return reinterpret_cast<StructImpl*>(getPimpl())->setStaticMethodsCapacity(capacity);
}

void Struct::setDefaultInstantiator(void* (*instantiator)()) noexcept
{
	reinterpret_cast<StructImpl*>(getPimpl())->setDefaultInstantiator(instantiator);
}

void Struct::addInstantiator(StaticMethod const* instantiator) noexcept
{
	reinterpret_cast<StructImpl*>(getPimpl())->addInstantiator(instantiator);
}

void* Struct::makeInstanceFromDefaultInstantiator() const
{
	void* (*defaultInstantiator)() = reinterpret_cast<StructImpl const*>(getPimpl())->getDefaultInstantiator();

	assert(defaultInstantiator != nullptr);

	return (*defaultInstantiator)();
}

std::size_t Struct::getInstantiatorsCount() const noexcept
{
	return reinterpret_cast<StructImpl const*>(getPimpl())->getCustomInstantiators().size();
}

StaticMethod const* Struct::getInstantiatorAt(std::size_t index) const noexcept
{
	return reinterpret_cast<StructImpl const*>(getPimpl())->getCustomInstantiators()[index];
}