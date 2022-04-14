#include "Refureku/TypeInfo/Archetypes/Struct.h"

#include "Refureku/TypeInfo/Archetypes/StructImpl.h"
#include "Refureku/TypeInfo/Archetypes/Enum.h"
#include "Refureku/Misc/Algorithm.h"

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

Struct::~Struct() noexcept
{
	//Unregister this class from subclasses direct parents
	std::size_t i = 0u;
	for (auto [subclass, subclassData] : getPimpl()->getSubclasses())
	{
		//Search this struct in subclasses's parents
		i = 0u;
		for (ParentStruct const& subclassParent : subclass->getPimpl()->getDirectParents())
		{
			if (&subclassParent.getArchetype() == this)
			{
				//Found a subclass that has this Struct as a direct parent
				const_cast<Struct*>(subclass)->getPimpl()->removeDirectParentAt(i);
				break;
			}

			i++;
		}

		//Unregister this struct subclasses from upper class hierarchy
		Struct const* subclassLValue = subclass;
		Algorithm::foreach(getPimpl()->getDirectParents(), [subclassLValue](ParentStruct const& parent)
						   {
							   const_cast<Struct&>(parent.getArchetype()).getPimpl()->removeSubclassRecursive(*subclassLValue);

							   return true;
						   });
	}

	//Unregister this class from upper class hierarchy subclasses
	Algorithm::foreach(getPimpl()->getDirectParents(), [this](ParentStruct const& parent)
					   {
						   const_cast<Struct&>(parent.getArchetype()).getPimpl()->removeSubclassRecursive(*this);

						   return true;
					   });
}

rfk::Vector<Struct const*> Struct::getDirectSubclasses() const noexcept
{
	rfk::Vector<Struct const*> result;

	for (auto [subclass, subclassData] : getPimpl()->getSubclasses())
	{
		//Search this struct in subclasses's parents
		for (ParentStruct const& subclassParent : subclass->getPimpl()->getDirectParents())
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
	auto const& subclasses = getPimpl()->getSubclasses();

	return &archetype == this || subclasses.find(&archetype) != subclasses.cend();
}

EClassKind Struct::getClassKind() const noexcept
{
	return getPimpl()->getClassKind();
}

bool Struct::getPointerOffset(Struct const& to, std::ptrdiff_t& out_pointerOffset) const noexcept
{
	//This method is used for downcast in most cases, so search in the parent first.
	//In the case of a downcast, this is likely the parent struct and to the child one
	if (getPimpl()->getPointerOffset(to, out_pointerOffset))
	{
		return true;
	}
	//Try the other way around
	else if (to.getPimpl()->getPointerOffset(*this, out_pointerOffset))
	{
		//Invert the offset to switch from
		//to -> this offset
		//to
		//this -> to offset
		out_pointerOffset = -out_pointerOffset;

		return true;
	}
	
	//this Struct and to Struct do not belong to the same inheritance tree
	return false;
}

bool Struct::getSubclassPointerOffset(Struct const& to, std::ptrdiff_t& out_pointerOffset) const noexcept
{
	return getPimpl()->getPointerOffset(to, out_pointerOffset);
}

ParentStruct const& Struct::getDirectParentAt(std::size_t index) const noexcept
{
	return getPimpl()->getDirectParents()[index];
}

std::size_t Struct::getDirectParentsCount() const noexcept
{
	return getPimpl()->getDirectParents().size();
}

bool Struct::foreachDirectParent(Visitor<ParentStruct> visitor, void* userData) const
{
	return Algorithm::foreach(getPimpl()->getDirectParents(), visitor, userData);
}

Struct const* Struct::getNestedStructByName(char const* name, EAccessSpecifier access) const noexcept
{
	Archetype const* foundArchetype = getPimpl()->getNestedArchetype(name, access);

	return (foundArchetype != nullptr && foundArchetype->getKind() == EEntityKind::Struct) ?
				reinterpret_cast<Struct const*>(foundArchetype) :
				nullptr;
}

Struct const* Struct::getNestedStructByPredicate(Predicate<Struct> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		reinterpret_cast<Struct const*>(
			Algorithm::getItemByPredicate(getPimpl()->getNestedArchetypes(),
												   [predicate, userData](Archetype const& archetype)
												   {
													   return archetype.getKind() == EEntityKind::Struct && predicate(static_cast<Struct const&>(archetype), userData);
												   })) : nullptr;
}

Vector<Struct const*> Struct::getNestedStructsByPredicate(Predicate<Struct> predicate, void* userData) const
{
	if (predicate != nullptr)
	{
		return Algorithm::getItemsByPredicate(getPimpl()->getNestedArchetypes(),
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
	Archetype const* foundArchetype = getPimpl()->getNestedArchetype(name, access);

	return (foundArchetype != nullptr && foundArchetype->getKind() == EEntityKind::Class) ?
				reinterpret_cast<Class const*>(foundArchetype) :
				nullptr;
}

Class const* Struct::getNestedClassByPredicate(Predicate<Class> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		reinterpret_cast<Class const*>(
			Algorithm::getItemByPredicate(getPimpl()->getNestedArchetypes(),
			[predicate, userData](Archetype const& archetype)
			{
				return archetype.getKind() == EEntityKind::Class && predicate(static_cast<Class const&>(archetype), userData);
			})) : nullptr;
}

Vector<Class const*> Struct::getNestedClassesByPredicate(Predicate<Class> predicate, void* userData) const
{
	if (predicate != nullptr)
	{
		return Algorithm::getItemsByPredicate(getPimpl()->getNestedArchetypes(),
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
	Archetype const* foundArchetype = getPimpl()->getNestedArchetype(name, access);

	return (foundArchetype != nullptr && foundArchetype->getKind() == EEntityKind::Enum) ?
				reinterpret_cast<Enum const*>(foundArchetype) :
				nullptr;
}

Enum const* Struct::getNestedEnumByPredicate(Predicate<Enum> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		reinterpret_cast<Enum const*>(
			Algorithm::getItemByPredicate(getPimpl()->getNestedArchetypes(),
			[predicate, userData](Archetype const& archetype)
			{
				return archetype.getKind() == EEntityKind::Enum && predicate(static_cast<Enum const&>(archetype), userData);
			})) : nullptr;
}

Vector<Enum const*> Struct::getNestedEnumsByPredicate(Predicate<Enum> predicate, void* userData) const
{
	if (predicate != nullptr)
	{
		return Algorithm::getItemsByPredicate(getPimpl()->getNestedArchetypes(),
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
	return Algorithm::foreach(getPimpl()->getNestedArchetypes(), visitor, userData);
}

std::size_t Struct::getNestedArchetypesCount() const noexcept
{
	return getPimpl()->getNestedArchetypes().size();
}

Field const* Struct::getFieldByName(char const* name, EFieldFlags minFlags, bool shouldInspectInherited) const noexcept
{
	Field const* result = nullptr;

	Algorithm::foreachEntityNamed(getPimpl()->getFields(),
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
		Algorithm::getItemByPredicate(getPimpl()->getFields(),
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
		return Algorithm::getItemsByPredicate(getPimpl()->getFields(),
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
	return (visitor != nullptr) ? Algorithm::foreach(getPimpl()->getFields(),
										[this, visitor, userData, shouldInspectInherited](Field const& field)
										{
											return (shouldInspectInherited || field.getOuterEntity() == this) ? visitor(field, userData) : true;
										}) : false;
}

std::size_t Struct::getFieldsCount() const noexcept
{
	return getPimpl()->getFields().size();
}

StaticField const* Struct::getStaticFieldByName(char const* name, EFieldFlags minFlags, bool shouldInspectInherited) const noexcept
{
	StaticField const* result = nullptr;

	Algorithm::foreachEntityNamed(getPimpl()->getStaticFields(),
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
		Algorithm::getItemByPredicate(getPimpl()->getStaticFields(),
											[this, predicate, userData, shouldInspectInherited](StaticField const& staticField)
											{
												return (shouldInspectInherited || staticField.getOuterEntity() == this) && predicate(staticField, userData);
											}) : nullptr;
}

Vector<StaticField const*> Struct::getStaticFieldsByPredicate(Predicate<StaticField> predicate, void* userData, bool shouldInspectInherited) const
{
	if (predicate != nullptr)
	{
		return Algorithm::getItemsByPredicate(getPimpl()->getStaticFields(),
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
	return (visitor != nullptr) ? Algorithm::foreach(getPimpl()->getStaticFields(),
										[this, visitor, userData, shouldInspectInherited](StaticField const& staticField)
										{
											return (shouldInspectInherited || staticField.getOuterEntity() == this) ? visitor(staticField, userData) : true;
										}) : false;
}

std::size_t Struct::getStaticFieldsCount() const noexcept
{
	return getPimpl()->getStaticFields().size();
}

Method const* Struct::getMethodByName(char const* name, EMethodFlags minFlags, bool shouldInspectInherited) const noexcept
{
	Method const* result = nullptr;

	bool foundMethod = !Algorithm::foreachEntityNamed(getPimpl()->getMethods(),
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
			for (ParentStruct const& parent : getPimpl()->getDirectParents())
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
	Vector<Method const*> result(2);

	Algorithm::foreachEntityNamed(getPimpl()->getMethods(),
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
		for (ParentStruct const& parent : getPimpl()->getDirectParents())
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
		Method const* result = Algorithm::getItemByPredicate(getPimpl()->getMethods(), predicate, userData);

		if (result != nullptr)
		{
			return result;
		}
		else if (shouldInspectInherited)
		{
			for (ParentStruct const& parent : getPimpl()->getDirectParents())
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
		Vector<Method const*> result(2);

		result.push_back(Algorithm::getItemsByPredicate(getPimpl()->getMethods(), predicate, userData));

		if (shouldInspectInherited)
		{
			for (ParentStruct const& parent : getPimpl()->getDirectParents())
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
	bool result = Algorithm::foreach(getPimpl()->getMethods(), visitor, userData);

	//Iterate on parent methods if necessary
	if (result && shouldInspectInherited)
	{
		std::size_t i = 0u;
		auto const&	directParents = getPimpl()->getDirectParents();

		while (result && i < directParents.size())
		{
			result &= directParents[i].getArchetype().foreachMethod(visitor, userData, true);
			i++;
		}
	}

	return result;
}

std::size_t Struct::getMethodsCount() const noexcept
{
	return getPimpl()->getMethods().size();
}

StaticMethod const* Struct::getStaticMethodByName(char const* name, EMethodFlags minFlags, bool shouldInspectInherited) const noexcept
{
	StaticMethod const*	result = nullptr;

	bool foundMethod = !Algorithm::foreachEntityNamed(getPimpl()->getStaticMethods(),
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
			for (ParentStruct const& parent : getPimpl()->getDirectParents())
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

	Algorithm::foreachEntityNamed(getPimpl()->getStaticMethods(),
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
		for (ParentStruct const& parent : getPimpl()->getDirectParents())
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
		StaticMethod const*	result = Algorithm::getItemByPredicate(getPimpl()->getStaticMethods(), predicate, userData);

		if (result != nullptr)
		{
			return result;
		}
		else if (shouldInspectInherited)
		{
			for (ParentStruct const& parent : getPimpl()->getDirectParents())
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
		Vector<StaticMethod const*> result(2);

		result.push_back(Algorithm::getItemsByPredicate(getPimpl()->getStaticMethods(), predicate, userData));

		if (shouldInspectInherited)
		{
			for (ParentStruct const& parent : getPimpl()->getDirectParents())
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
	bool result = Algorithm::foreach(getPimpl()->getStaticMethods(), visitor, userData);

	//Iterate on parent static methods if necessary
	if (result && shouldInspectInherited)
	{
		std::size_t i = 0u;
		auto const&	directParents = getPimpl()->getDirectParents();

		while (result && i < directParents.size())
		{
			result &= directParents[i].getArchetype().foreachStaticMethod(visitor, userData, true);
			i++;
		}
	}

	return result;
}

std::size_t Struct::getStaticMethodsCount() const noexcept
{
	return getPimpl()->getStaticMethods().size();
}

void Struct::addDirectParent(Archetype const* archetype, EAccessSpecifier inheritanceAccess) noexcept
{
	if (archetype != nullptr)
	{
		assert(archetype->getKind() == EEntityKind::Struct || archetype->getKind() == EEntityKind::Class);

		getPimpl()->addDirectParent(*reinterpret_cast<Struct const*>(archetype), inheritanceAccess);
	}
}

void Struct::setDirectParentsCapacity(std::size_t capacity) noexcept
{
	getPimpl()->setDirectParentsCapacity(capacity);
}

void Struct::addSubclass(Struct const& subclass, std::ptrdiff_t subclassPointerOffset) noexcept
{
	getPimpl()->addSubclass(subclass, subclassPointerOffset);
}

void Struct::addNestedArchetype(Archetype const* nestedArchetype, EAccessSpecifier accessSpecifier) noexcept
{
	if (nestedArchetype != nullptr)
	{
		getPimpl()->addNestedArchetype(nestedArchetype, accessSpecifier, this);
	}
}

void Struct::setNestedArchetypesCapacity(std::size_t capacity) noexcept
{
	getPimpl()->setNestedArchetypesCapacity(capacity);
}

Field* Struct::addField(char const* name, std::size_t id, Type const& type,
							  EFieldFlags flags, std::size_t memoryOffset, Struct const* outerEntity) noexcept
{
	return (name != nullptr) ? getPimpl()->addField(name, id, type, flags, this, memoryOffset, outerEntity) : nullptr;
}

void Struct::setFieldsCapacity(std::size_t capacity) noexcept
{
	return getPimpl()->setFieldsCapacity(capacity);
}

StaticField* Struct::addStaticField(char const* name, std::size_t id, Type const& type,
									EFieldFlags flags, void* fieldPtr, Struct const* outerEntity) noexcept
{
	return (name != nullptr) ? getPimpl()->addStaticField(name, id, type, flags, this, fieldPtr, outerEntity) : nullptr;
}

StaticField* Struct::addStaticField(char const* name, std::size_t id, Type const& type,
									EFieldFlags flags, void const* fieldPtr, Struct const* outerEntity) noexcept
{
	return (name != nullptr) ? getPimpl()->addStaticField(name, id, type, flags, this, fieldPtr, outerEntity) : nullptr;
}

void Struct::setStaticFieldsCapacity(std::size_t capacity) noexcept
{
	return getPimpl()->setStaticFieldsCapacity(capacity);
}

Method* Struct::addMethod(char const* name, std::size_t id, Type const& returnType,
						  ICallable* internalMethod, EMethodFlags flags) noexcept
{
	return (name != nullptr) ? getPimpl()->addMethod(name, id, returnType, internalMethod, flags, this) : nullptr;
}

void Struct::setMethodsCapacity(std::size_t capacity) noexcept
{
	return getPimpl()->setMethodsCapacity(capacity);
}

StaticMethod* Struct::addStaticMethod(char const* name, std::size_t id, Type const& returnType,
									  ICallable* internalMethod, EMethodFlags flags) noexcept
{
	return (name != nullptr) ? getPimpl()->addStaticMethod(name, id, returnType, internalMethod, flags, this) : nullptr;
}

void Struct::setStaticMethodsCapacity(std::size_t capacity) noexcept
{
	return getPimpl()->setStaticMethodsCapacity(capacity);
}


bool Struct::foreachSharedInstantiator(std::size_t argCount, Visitor<StaticMethod> visitor, void* userData) const
{
	bool result = true;

	Algorithm::foreach(getPimpl()->getSharedInstantiators(), [&result, argCount, visitor, userData](StaticMethod const& instantiator)
					   {
							std::size_t instantiatorParamCounts = instantiator.getParametersCount();

							//Instantiators are ordered by ascending param counts, so skip all
							//instantiators having less than the required arg count
							if (instantiatorParamCounts < argCount)
							{
								return true;
							}
							else if (instantiatorParamCounts == argCount)
							{
								//Run the visitor on each instantiator having the same arg count
								result = visitor(instantiator, userData);
								return result;
							}
							else //instantiatorParamCounts > argCount
							{
								//Abort the foreach loop once we reach elements that have a greater
								//arg count
								return false;
							}
					   });

	return result;
}

bool Struct::foreachUniqueInstantiator(std::size_t argCount, Visitor<StaticMethod> visitor, void* userData) const
{
	bool result = true;

	Algorithm::foreach(getPimpl()->getUniqueInstantiators(), [&result, argCount, visitor, userData](StaticMethod const& instantiator)
					   {
						   std::size_t instantiatorParamCounts = instantiator.getParametersCount();

						   //Instantiators are ordered by ascending param counts, so skip all
						   //instantiators having less than the required arg count
						   if (instantiatorParamCounts < argCount)
						   {
							   return true;
						   }
						   else if (instantiatorParamCounts == argCount)
						   {
							   //Run the visitor on each instantiator having the same arg count
							   result = visitor(instantiator, userData);
							   return result;
						   }
						   else //instantiatorParamCounts > argCount
						   {
							   //Abort the foreach loop once we reach elements that have a greater
							   //arg count
							   return false;
						   }
					   });

	return result;
}

void Struct::addSharedInstantiator(StaticMethod const& instantiator) noexcept
{
	getPimpl()->addSharedInstantiator(instantiator);
}

void Struct::addUniqueInstantiator(StaticMethod const& instantiator) noexcept
{
	getPimpl()->addUniqueInstantiator(instantiator);
}