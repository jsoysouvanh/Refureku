/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline Database const& getDatabase() noexcept
{
	return Database::getInternal();
}

inline Database& Database::getInternal() noexcept
{
	static Database database;
	return database;
}

template <typename Predicate, typename>
Entity const* Database::getEntity(Predicate predicate) const
{
	for (Entity const* entity : _entitiesById)
	{
		if (predicate(entity))
		{
			return entity;
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
Namespace const* Database::getNamespace(Predicate predicate) const
{
	for (Namespace const* n : _fileLevelNamespacesByName)
	{
		if (predicate(n))
		{
			return n;
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
Archetype const* Database::getArchetype(Predicate predicate) const
{
	Archetype const* result = nullptr;

	if ((result = getStruct(predicate)) == nullptr)
	{
		if ((result = getClass(predicate)) == nullptr)
		{
			if ((result = getEnum(predicate)) == nullptr)
			{
				result = getFundamentalArchetype(predicate);
			}
		}
	}

	return result;
}

template <typename Predicate, typename>
Struct const* Database::getStruct(Predicate predicate) const
{
	for (Struct const* s : _fileLevelStructsByName)
	{
		if (predicate(s))
		{
			return s;
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
Class const* Database::getClass(Predicate predicate) const
{
	for (Class const* c : _fileLevelClassesByName)
	{
		if (predicate(c))
		{
			return c;
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
Enum const* Database::getEnum(Predicate predicate) const
{
	for (Enum const* e : _fileLevelEnumsByName)
	{
		if (predicate(e))
		{
			return e;
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
FundamentalArchetype const* Database::getFundamentalArchetype(Predicate predicate) const
{
	for (FundamentalArchetype const* fundamentalArchetype : _fundamentalArchetypes)
	{
		if (predicate(fundamentalArchetype))
		{
			return fundamentalArchetype;
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
Variable const* Database::getVariable(Predicate predicate) const
{
	for (Variable const* variable : _fileLevelVariablesByName)
	{
		if (predicate(variable))
		{
			return variable;
		}
	}

	return nullptr;
}

template <typename Predicate, typename>
Function const* Database::getFunction(Predicate predicate) const
{
	for (Function const* function : _fileLevelFunctionsByName)
	{
		if (predicate(function))
		{
			return function;
		}
	}

	return nullptr;
}

template <typename FunctionSignature>
Function const* Database::getFunction(std::string functionName, EFunctionFlags flags) const noexcept
{
	static_assert(std::is_function_v<FunctionSignature>, "Database::getFunction<> must be called with a function signature as template argument.");

	Entity searchedFunction(std::move(functionName), 0u);

	//Use an Entity instead of a Function to avoid memory / allocation overhead
	auto range = _fileLevelFunctionsByName.equal_range(static_cast<Function const*>(&searchedFunction));

	for (auto it = range.first; it != range.second; it++)
	{
		if (((*it)->flags & flags) == flags && internal::FunctionHelper<FunctionSignature>::hasSamePrototype(**it))
		{
			//We found a method which has minFlags and matches the signature
			return *it;
		}
	}

	return nullptr;
}