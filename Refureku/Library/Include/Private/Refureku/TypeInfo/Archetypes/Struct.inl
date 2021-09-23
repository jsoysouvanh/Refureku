/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename T>
void Struct::addParent(EAccessSpecifier inheritanceAccess) noexcept
{
	Archetype const* parentArchetype = getArchetype<T>();

	if (parentArchetype != nullptr)
	{
		assert(parentArchetype->getKind() == EEntityKind::Struct || parentArchetype->getKind() == EEntityKind::Class);

		addParent(reinterpret_cast<Struct const*>(parentArchetype), inheritanceAccess);
	}
}

template <typename Predicate, typename>
Archetype const* Struct::getNestedArchetype(Predicate predicate) const
{
	struct Data
	{
		Predicate			predicate;
		Archetype const*	result = nullptr;
	} data{predicate, nullptr};

	foreachNestedArchetype([](Archetype const& archetype, void* userData)
	{
		Data* data = reinterpret_cast<Data*>(userData);

		if (data->predicate(archetype))
		{
			data->result = &archetype;
			return false;
		}

		return true;
	}, &data);

	return data.result;
}

template <typename Predicate, typename>
Struct const* Struct::getNestedStruct(Predicate predicate) const
{
	struct Data
	{
		Predicate		predicate;
		Struct const*	result = nullptr;
	} data{predicate, nullptr};

	foreachNestedArchetype([](Archetype const& archetype, void* userData)
	{
		Data* data = reinterpret_cast<Data*>(userData);

		if (archetype.getKind() == EEntityKind::Struct && data->predicate(static_cast<Struct const&>(archetype)))
		{
			data->result = &static_cast<Struct const&>(archetype);
			return false;
		}

		return true;
	}, &data);

	return data.result;
}

template <typename Predicate, typename>
Class const* Struct::getNestedClass(Predicate predicate) const
{
	struct Data
	{
		Predicate		predicate;
		Class const*	result = nullptr;
	} data{predicate, nullptr};

	foreachNestedArchetype([](Archetype const& archetype, void* userData)
	{
		Data* data = reinterpret_cast<Data*>(userData);

		if (archetype.getKind() == EEntityKind::Class && data->predicate(static_cast<Class const&>(archetype)))
		{
			data->result = &static_cast<Class const&>(archetype);
			return false;
		}

		return true;
	}, &data);

	return data.result;
}

template <typename Predicate, typename>
Enum const* Struct::getNestedEnum(Predicate predicate) const
{
	struct Data
	{
		Predicate	predicate;
		Enum const*	result = nullptr;
	} data{predicate, nullptr};

	foreachNestedArchetype([](Archetype const& archetype, void* userData)
	{
		Data* data = reinterpret_cast<Data*>(userData);

		if (archetype.getKind() == EEntityKind::Enum && data->predicate(static_cast<Enum const&>(archetype)))
		{
			data->result = &static_cast<Enum const&>(archetype);
			return false;
		}

		return true;
	}, &data);

	return data.result;
}

template <typename Predicate, typename>
Field const* Struct::getField(Predicate predicate, bool shouldInspectInherited) const
{
	struct Data
	{
		Predicate		predicate;
		bool			shouldInspectInherited;
		Struct const*	thisStruct;
		Field const*	result = nullptr;
	} data{predicate, shouldInspectInherited, this, nullptr};

	foreachField([](Field const& field, void* userData)
	{
		Data* data = reinterpret_cast<Data*>(userData);
				 
		if ((data->shouldInspectInherited || field.getOuterEntity() == data->thisStruct) && data->predicate(field))
		{
			data->result = &field;
			return false;
		}
				 
		return true;
	}, &data);

	return data.result;
}

template <typename Predicate, typename>
std::vector<Field const*> Struct::getFields(Predicate predicate, bool shouldInspectInherited) const
{
	struct Data
	{
		Predicate					predicate;
		bool						shouldInspectInherited;
		Struct const*				thisStruct;
		std::vector<Field const*>	result;
	} data{predicate, shouldInspectInherited, this};

	foreachField([](Field const& field, void* userData)
	{
		Data* data = reinterpret_cast<Data*>(userData);

		if ((data->shouldInspectInherited || field.getOuterEntity() == data->thisStruct) && data->predicate(field))
		{
			data->result.push_back(&field);
		}

		return true;
	}, &data);

	return data.result; //Should we std::move?
}

template <typename Predicate, typename>
StaticField const* Struct::getStaticField(Predicate predicate, bool shouldInspectInherited) const
{
	struct Data
	{
		Predicate			predicate;
		bool				shouldInspectInherited;
		Struct const*		thisStruct;
		StaticField const*	result;
	} data{predicate, shouldInspectInherited, this, nullptr};

	foreachStaticField([](StaticField const& staticField, void* userData)
	{
		Data* data = reinterpret_cast<Data*>(userData);
					   
		/**
		*	_staticFields collection contains both this struct static fields and inherited static fields,
		*	make sure we check inherited fields only if requested
		*/
		if ((data->shouldInspectInherited || staticField.getOuterEntity() == data->thisStruct) && data->predicate(staticField))
		{
			data->result = &staticField;
			return false;
		}
					   
		return true;
	}, &data);

	return data.result;
}

template <typename Predicate, typename>
std::vector<StaticField const*> Struct::getStaticFields(Predicate predicate, bool shouldInspectInherited) const
{
	struct Data
	{
		Predicate						predicate;
		bool							shouldInspectInherited;
		Struct const*					thisStruct;
		std::vector<StaticField const*>	result;
	} data{predicate, shouldInspectInherited, this};

	foreachStaticField([](StaticField const& staticField, void* userData)
	{
		Data* data = reinterpret_cast<Data*>(userData);

		/**
		*	_staticFields collection contains both this struct static fields and inherited static fields,
		*	make sure we check inherited fields only if requested
		*/
		if ((data->shouldInspectInherited || staticField.getOuterEntity() == data->thisStruct) && data->predicate(staticField))
		{
			data->result.push_back(&staticField);
		}

		return true;
	}, &data);

	return data.result; //Should we std::move?
}

template <typename MethodSignature>
Method const* Struct::getMethod(std::string const& methodName, EMethodFlags minFlags, bool shouldInspectInherited) const noexcept
{
	static_assert(std::is_function_v<MethodSignature>, "Struct::getMethod<> must be called with a function signature as template argument.");

	//Use an Entity instead of a Method to avoid memory / allocation overhead
	auto range = _methods.equal_range(static_cast<Method&&>(Entity(std::string(methodName), 0u)));

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

		for (std::size_t i = 0u; i < getDirectParentsCount(); i++)
		{
			result = getDirectParentAt(i).getArchetype().getMethod(methodName, minFlags, true);

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
	struct Data
	{
		Predicate		predicate;
		Method const*	result;
	} data{predicate, nullptr};

	if (!foreachMethod([](Method const& method, void* userData)
		{
			Data* data = reinterpret_cast<Data*>(userData);

			if (data->predicate(method))
			{
				data->result = &method;
				return false;
			}

			return true;
		}, &data))
	{
		return data.result;
	}

	//Check in parent's methods
	if (shouldInspectInherited)
	{
		Method const* result = nullptr;

		for (std::size_t i = 0u; i < getDirectParentsCount(); i++)
		{
			result = getDirectParentAt(i).getArchetype().getMethod<Predicate>(predicate, true);

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
	struct Data
	{
		Predicate					predicate;
		std::vector<Method const*>	result;
	} data{predicate};

	//Retrieve methods declared in this struct first
	foreachMethod([](Method const& method, void* userData)
	{
		Data* data = reinterpret_cast<Data*>(userData);

		if (data->predicate(method))
		{
			data->result.push_back(&method);
		}

		return true;
	}, &data);

	//Add parent's method matching the predicate if queried
	if (shouldInspectInherited)
	{
		std::vector<Method const*> parentResult;

		for (std::size_t i = 0u; i < getDirectParentsCount(); i++)
		{
			parentResult = getDirectParentAt(i).getArchetype().getMethods(predicate, true);

			data.result.insert(data.result.end(), parentResult.begin(), parentResult.end());
		}
	}

	return data.result;	//Should we std::move?
}

template <typename MethodSignature>
StaticMethod const* Struct::getStaticMethod(std::string const& methodName, EMethodFlags minFlags, bool shouldInspectInherited) const noexcept
{
	static_assert(std::is_function_v<MethodSignature>, "Struct::getStaticMethod<> must be called with a function signature as template argument.");

	//Use an Entity instead of a StaticMethod to avoid memory / allocation overhead
	auto range = _staticMethods.equal_range(static_cast<StaticMethod&&>(Entity(std::string(methodName), 0u)));

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

		for (std::size_t i = 0u; i < getDirectParentsCount(); i++)
		{
			result = getDirectParentAt(i).getArchetype().getStaticMethod(methodName, minFlags, true);

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
	struct Data
	{
		Predicate			predicate;
		StaticMethod const*	result;
	} data{predicate, nullptr};

	//Iterate over this struct's static methods
	if (!foreachStaticMethod([](StaticMethod const& staticMethod, void* userData)
		{
			Data* data = reinterpret_cast<Data*>(userData);

			if (data->predicate(staticMethod))
			{
				data->result = &staticMethod;
				return false;
			}

			return true;
		}, &data))
	{
		return data.result;
	}

	//Check in parent's static methods
	if (shouldInspectInherited)
	{
		StaticMethod const* result = nullptr;

		for (std::size_t i = 0u; i < getDirectParentsCount(); i++)
		{
			result = getDirectParentAt(i).getArchetype().getStaticMethod(predicate, true);

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
	struct Data
	{
		Predicate							predicate;
		std::vector<StaticMethod const*>	result;
	} data{predicate};

	//Iterate over this struct's static methods
	foreachStaticMethod([](StaticMethod const& staticMethod, void* userData)
	{
		Data* data = reinterpret_cast<Data*>(userData);

		if (data->predicate(staticMethod))
		{
			data->result.push_back(&staticMethod);
		}

		return true;
	}, &data);

	//Check in parent's static methods
	if (shouldInspectInherited)
	{
		std::vector<StaticMethod const*> parentResult;

		for (std::size_t i = 0u; i < getDirectParentsCount(); i++)
		{
			parentResult = getDirectParentAt(0).getArchetype().getStaticMethods(predicate, true);

			data.result.insert(data.result.end(), parentResult.begin(), parentResult.end());
		}
	}

	return data.result;	//Should we std::move?
}

template <typename ReturnType, typename... ArgTypes>
ReturnType* Struct::makeInstanceFromCustomInstantiator(ArgTypes&&... args) const
{
	for (StaticMethod const* instantiator : _customInstantiators)
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
		_customInstantiators.push_back(instantiator);
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
	return _classKind == EClassKind::Template;
}

inline ClassTemplate const* Struct::asTemplate() const noexcept
{
	return isTemplate() ? reinterpret_cast<ClassTemplate const*>(this) : nullptr;
}

inline bool	Struct::isTemplateInstantiation() const noexcept
{
	return _classKind == EClassKind::TemplateInstantiation;
}

inline ClassTemplateInstantiation const* Struct::asTemplateInstantiation() const noexcept
{
	return isTemplateInstantiation() ? reinterpret_cast<ClassTemplateInstantiation const*>(this) : nullptr;
}