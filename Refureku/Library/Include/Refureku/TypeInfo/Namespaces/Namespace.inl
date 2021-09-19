/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename Predicate, typename>
Namespace const* Namespace::getNamespace(Predicate predicate) const
{
	for (Namespace const* n : namespaces)
	{
		if (predicate(n))
		{
			return n;
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
Archetype const* Namespace::getArchetype(Predicate predicate) const
{
	for (Archetype const* archetype : archetypes)
	{
		if (predicate(archetype))
		{
			return archetype;
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
Struct const* Namespace::getStruct(Predicate predicate) const
{
	for (Archetype const* archetype : archetypes)
	{
		if (archetype->getKind() == EEntityKind::Struct && predicate(reinterpret_cast<Struct const*>(archetype)))
		{
			return reinterpret_cast<Struct const*>(archetype);
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
Class const* Namespace::getClass(Predicate predicate) const
{
	for (Archetype const* archetype : archetypes)
	{
		if (archetype->getKind() == EEntityKind::Class && predicate(reinterpret_cast<Class const*>(archetype)))
		{
			return reinterpret_cast<Class const*>(archetype);
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
Enum const* Namespace::getEnum(Predicate predicate) const
{
	for (Archetype const* archetype : archetypes)
	{
		if (archetype->getKind() == EEntityKind::Enum && predicate(reinterpret_cast<Enum const*>(archetype)))
		{
			return reinterpret_cast<Enum const*>(archetype);
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
Variable const* Namespace::getVariable(Predicate predicate) const
{
	for (Variable const* v : variables)
	{
		if (predicate(v))
		{
			return v;
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
Function const* Namespace::getFunction(Predicate predicate) const
{
	for (Function const* function : functions)
	{
		if (predicate(function))
		{
			return function;
		}
	}

	return nullptr;
}

template <typename FunctionSignature>
Function const* Namespace::getFunction(std::string functionName, EFunctionFlags flags) const noexcept
{
	Entity searchedFunction(std::move(functionName), 0u);

	//Use an Entity instead of a Function to avoid memory / allocation overhead
	auto range = functions.equal_range(static_cast<Function const*>(&searchedFunction));

	for (auto it = range.first; it != range.second; it++)
	{
		//We found a method which has minFlags
		if (((*it)->flags & flags) == flags && internal::FunctionHelper<FunctionSignature>::hasSamePrototype(**it))
		{
			return *it;
		}
	}

	return nullptr;
}