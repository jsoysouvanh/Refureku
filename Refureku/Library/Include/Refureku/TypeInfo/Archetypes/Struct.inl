/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename T>
void Struct::addToParents(EAccessSpecifier inheritanceAccess) noexcept
{
	Archetype const* parentArchetype = getArchetype<T>();

	if (parentArchetype != nullptr)
	{
		assert(parentArchetype->getKind() == EEntityKind::Struct || parentArchetype->getKind() == EEntityKind::Class);

		addToParents(reinterpret_cast<Struct const*>(parentArchetype), inheritanceAccess);
	}
}

template <typename Predicate, typename>
Archetype const* Struct::getNestedArchetype(Predicate predicate) const
{
	for (Archetype const* archetype : nestedArchetypes)
	{
		if (predicate(archetype))
		{
			return archetype;
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
Struct const* Struct::getNestedStruct(Predicate predicate) const
{
	for (Archetype const* archetype : nestedArchetypes)
	{
		if (archetype->getKind() == EEntityKind::Struct && predicate(reinterpret_cast<Struct const*>(archetype)))
		{
			return reinterpret_cast<Struct const*>(archetype);
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
Class const* Struct::getNestedClass(Predicate predicate) const
{
	for (Archetype const* archetype : nestedArchetypes)
	{
		if (archetype->getKind() == EEntityKind::Class && predicate(reinterpret_cast<Class const*>(archetype)))
		{
			return reinterpret_cast<Class const*>(archetype);
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
Enum const* Struct::getNestedEnum(Predicate predicate) const
{
	for (Archetype const* archetype : nestedArchetypes)
	{
		if (archetype->getKind() == EEntityKind::Enum && predicate(reinterpret_cast<Enum const*>(archetype)))
		{
			return reinterpret_cast<Enum const*>(archetype);
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
Field const* Struct::getField(Predicate predicate, bool shouldInspectInherited) const
{
	for (Field const& field : fields)
	{
		/**
		*	fields collection contains both this struct fields and inherited fields,
		*	make sure we check inherited fields only if requested
		*/
		if ((shouldInspectInherited || field.getOuterEntity() == this) && predicate(&field))
		{
			return &field;
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
std::vector<Field const*> Struct::getFields(Predicate predicate, bool shouldInspectInherited) const
{
	std::vector<Field const*> result;

	for (Field const& field : fields)
	{
		/**
		*	fields collection contains both this struct fields and inherited fields,
		*	make sure we check inherited fields only if requested
		*/
		if ((shouldInspectInherited || field.getOuterEntity() == this) && predicate(&field))
		{
			result.emplace_back(&field);
		}
	}

	return result;
}

template <typename Predicate, typename>
StaticField const* Struct::getStaticField(Predicate predicate, bool shouldInspectInherited) const
{
	for (StaticField const& staticField : staticFields)
	{
		/**
		*	staticFields collection contains both this struct static fields and inherited static fields,
		*	make sure we check inherited fields only if requested
		*/
		if ((shouldInspectInherited || staticField.getOuterEntity() == this) && predicate(&staticField))
		{
			return &staticField;
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
std::vector<StaticField const*> Struct::getStaticFields(Predicate predicate, bool shouldInspectInherited) const
{
	std::vector<StaticField const*> result;

	for (StaticField const& staticField : staticFields)
	{
		/**
		*	staticFields collection contains both this struct static fields and inherited static fields,
		*	make sure we check inherited fields only if requested
		*/
		if ((shouldInspectInherited || staticField.getOuterEntity() == this) && predicate(&staticField))
		{
			result.emplace_back(&staticField);
		}
	}

	return result;
}

template <typename MethodSignature>
Method const* Struct::getMethod(std::string const& methodName, EMethodFlags minFlags, bool shouldInspectInherited) const noexcept
{
	static_assert(std::is_function_v<MethodSignature>, "Struct::getMethod<> must be called with a function signature as template argument.");

	//Use an Entity instead of a Method to avoid memory / allocation overhead
	auto range = methods.equal_range(static_cast<Method&&>(Entity(std::string(methodName), 0u)));

	for (auto it = range.first; it != range.second; it++)
	{
		//We found a method which has minFlags
		if ((it->getFlags() & minFlags) == minFlags && internal::MethodHelper<MethodSignature>::hasSamePrototype(*it))
		{
			return &*it;
		}
	}

	//If we reach this point, couldn't find a valid method
	if (shouldInspectInherited)
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

template <typename Predicate, typename>
Method const* Struct::getMethod(Predicate predicate, bool shouldInspectInherited) const
{
	//Iterate over this struct's methods
	for (Method const& method : methods)
	{
		if (predicate(&method))
		{
			return &method;
		}
	}

	//Check in parent's methods
	if (shouldInspectInherited)
	{
		Method const* result = nullptr;

		for (Struct::Parent const& parent : directParents)
		{
			result = parent.type->getMethod<Predicate>(predicate, true);

			if (result != nullptr)
			{
				return result;
			}
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
std::vector<Method const*> Struct::getMethods(Predicate	predicate, bool shouldInspectInherited) const
{
	std::vector<Method const*> result;

	//Retrieve methods declared in this struct first
	for (Method const& method : methods)
	{
		if (predicate(&method))
		{
			result.emplace_back(&method);
		}
	}

	//Add parent's method matching the predicate if queried
	if (shouldInspectInherited)
	{
		std::vector<Method const*> parentResult;

		for (Struct::Parent const& parent : directParents)
		{
			parentResult = parent.type->getMethods(predicate, true);

			result.insert(result.end(), parentResult.begin(), parentResult.end());
		}
	}

	return result;
}

template <typename MethodSignature>
StaticMethod const* Struct::getStaticMethod(std::string const& methodName, EMethodFlags minFlags, bool shouldInspectInherited) const noexcept
{
	static_assert(std::is_function_v<MethodSignature>, "Struct::getStaticMethod<> must be called with a function signature as template argument.");

	//Use an Entity instead of a StaticMethod to avoid memory / allocation overhead
	auto range = staticMethods.equal_range(static_cast<StaticMethod&&>(Entity(std::string(methodName), 0u)));

	for (auto it = range.first; it != range.second; it++)
	{
		//We found a method which has minFlags
		if ((it->getFlags() & minFlags) == minFlags && internal::MethodHelper<MethodSignature>::hasSamePrototype(*it))
		{
			return &*it;
		}
	}

	//If we reach this point, couldn't find a valid method
	if (shouldInspectInherited)
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

template <typename Predicate, typename>
StaticMethod const* Struct::getStaticMethod(Predicate predicate, bool shouldInspectInherited) const
{
	//Iterate over this struct's static methods
	for (StaticMethod const& staticMethod : staticMethods)
	{
		if (predicate(&staticMethod))
		{
			return &staticMethod;
		}
	}

	//Check in parent's static methods
	if (shouldInspectInherited)
	{
		StaticMethod const* result = nullptr;

		for (Struct::Parent const& parent : directParents)
		{
			result = parent.type->getStaticMethod(predicate, true);

			if (result != nullptr)
			{
				return result;
			}
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
std::vector<StaticMethod const*> Struct::getStaticMethods(Predicate predicate, bool shouldInspectInherited) const
{
	std::vector<StaticMethod const*> result;

	//Iterate over this struct's static methods
	for (StaticMethod const& staticMethod : staticMethods)
	{
		if (predicate(&staticMethod))
		{
			result.emplace_back(&staticMethod);
		}
	}

	//Check in parent's static methods
	if (shouldInspectInherited)
	{
		std::vector<StaticMethod const*> parentResult;

		for (Struct::Parent const& parent : directParents)
		{
			parentResult = parent.type->getStaticMethods(predicate, true);

			result.insert(result.end(), parentResult.begin(), parentResult.end());
		}
	}

	return result;
}

template <typename ReturnType, typename... ArgTypes>
ReturnType* Struct::makeInstanceFromCustomInstantiator(ArgTypes&&... args) const
{
	for (StaticMethod const* instantiator : customInstantiators)
	{
		if (instantiator->hasSameArguments<ArgTypes...>())
		{
			return static_cast<ReturnType*>(instantiator->rInvoke<void*>(std::forward<ArgTypes>(args)...));
		}
	}

	return nullptr;
}

template <typename ReturnType, typename... ArgTypes>
ReturnType* Struct::makeInstance(ArgTypes&&... args) const
{
	static_assert(!std::is_pointer_v<ReturnType> && !std::is_reference_v<ReturnType>);

	if constexpr (sizeof...(args) == 0)
	{
		//No arguments, use default instantiator
		return (_defaultInstantiator != nullptr) ? static_cast<ReturnType*>((*_defaultInstantiator)()) : makeInstanceFromCustomInstantiator<ReturnType, ArgTypes...>(std::forward<ArgTypes>(args)...);
	}
	else
	{
		return makeInstanceFromCustomInstantiator<ReturnType, ArgTypes...>(std::forward<ArgTypes>(args)...);
	}
}

template <typename ReturnType>
void Struct::addCustomInstantiator(StaticMethod const* instantiator) noexcept
{
	//Make sure the instantiator is valid
	assert(instantiator != nullptr);
	assert(instantiator->getReturnType().isPointer());

	//If it is a parameterless custom instantiator, replace the default instantiator
	if (instantiator->getParameterCount() == 0u)
	{
		setDefaultInstantiator(reinterpret_cast<rfk::NonMemberFunction<void* ()> const*>(instantiator->getInternalFunction())->getFunctionHandle());
	}
	else
	{
		customInstantiators.emplace_back(instantiator);
	}
}

template <typename T>
void* defaultInstantiator()
{
	if constexpr (std::is_default_constructible_v<T>)
	{
		return new T();
	}
	else
	{
		return nullptr;
	}
}

inline bool Struct::isTemplate() const noexcept
{
	return classKind == EClassKind::Template;
}

inline ClassTemplate const* Struct::asTemplate() const noexcept
{
	return isTemplate() ? reinterpret_cast<ClassTemplate const*>(this) : nullptr;
}

inline bool	Struct::isTemplateInstantiation() const noexcept
{
	return classKind == EClassKind::TemplateInstantiation;
}

inline ClassTemplateInstantiation const* Struct::asTemplateInstantiation() const noexcept
{
	return isTemplateInstantiation() ? reinterpret_cast<ClassTemplateInstantiation const*>(this) : nullptr;
}