#include "TypeInfo/Struct.h"

using namespace rfk;

Struct::Struct(std::string&& newName, uint64 newId, ECategory newCategory, uint64 newMemorySize) noexcept:
	Archetype(std::forward<std::string>(newName), newId, newCategory, newMemorySize)
{
}

Field const* Struct::getField(std::string const& fieldName) const noexcept
{
	//Look between [start, end]
	auto first = std::lower_bound(fields.cbegin(), fields.cend(), Field(std::string(fieldName)),
								  [](Field const& f1, Field const& f2){ return f1.name < f2.name; });

	return (first != fields.cend() && first->name == fieldName) ? &*first : nullptr;
}

StaticField const* Struct::getStaticField(std::string const& fieldName) const noexcept
{
	//Look between [start, end]
	auto first = std::lower_bound(staticFields.cbegin(), staticFields.cend(), StaticField(std::string(fieldName)),
								  [](StaticField const& f1, StaticField const& f2){ return f1.name < f2.name; });

	return (first != staticFields.cend() && first->name == fieldName) ? &*first : nullptr;
}

Method const* Struct::getMethod(std::string const& methodName, uint16 minFlags, bool shouldInspectParents) const noexcept
{
	//Look between [begin, end]
	auto it = std::lower_bound(methods.cbegin(), methods.cend(), Method(std::string(methodName)),
								  [](Method const& m1, Method const& m2){ return m1.name < m2.name; });

	while (it != methods.cend() && it->name == methodName)
	{
		//We found a method which has minFlags
		if ((it->flags & minFlags) == minFlags)
		{
			return &*it;
		}

		++it;
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

std::vector<Method const*> Struct::getMethods(std::string const& methodName, uint16 minFlags, bool shouldInspectParents) const noexcept
{
	std::vector<Method const*> result;

	//Look between [begin, end]
	auto it = std::lower_bound(methods.cbegin(), methods.cend(), Method(std::string(methodName)),
							   [](Method const& m1, Method const& m2){ return m1.name < m2.name; });

	//Search until we reach the end or method name is no longer the one we are looking for
	while (it != methods.cend() && it->name == methodName)
	{
		//We found a method which has minFlags
		if ((it->flags & minFlags) == minFlags)
		{
			result.emplace_back(&*it);
		}

		++it;
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

StaticMethod const* Struct::getStaticMethod(std::string const& methodName, uint16 minFlags, bool shouldInspectParents) const noexcept
{
	//Look between [begin, end]
	auto it = std::lower_bound(staticMethods.cbegin(), staticMethods.cend(), StaticMethod(std::string(methodName)),
							   [](StaticMethod const& m1, StaticMethod const& m2){ return m1.name < m2.name; });

	while (it != staticMethods.cend() && it->name == methodName)
	{
		//We found a static method which has minFlags
		if ((it->flags & minFlags) == minFlags)
		{
			return &*it;
		}

		++it;
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

std::vector<StaticMethod const*> Struct::getStaticMethods(std::string const& methodName, uint16 minFlags, bool shouldInspectParents) const noexcept
{
	std::vector<StaticMethod const*> result;

	//Look between [begin, end]
	auto it = std::lower_bound(staticMethods.cbegin(), staticMethods.cend(), StaticMethod(std::string(methodName)),
							   [](StaticMethod const& m1, StaticMethod const& m2){ return m1.name < m2.name; });

	//Search until we reach the end or method name is no longer the one we are looking for
	while (it != staticMethods.cend() && it->name == methodName)
	{
		//We found a static method which has minFlags
		if ((it->flags & minFlags) == minFlags)
		{
			result.emplace_back(&*it);
		}

		++it;
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