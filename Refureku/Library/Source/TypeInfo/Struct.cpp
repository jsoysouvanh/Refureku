#include "TypeInfo/Struct.h"

using namespace rfk;

Struct::Struct(std::string&& newName, uint64 newId, ECategory newCategory, uint64 newMemorySize) noexcept:
	Archetype(std::forward<std::string>(newName), newId, newCategory, newMemorySize)
{
}

Field const* Struct::getField(std::string const& fieldName) const noexcept
{
	decltype(fields)::const_iterator first = fields.find(Field(std::string(fieldName)));

	return (first != fields.cend()) ? &*first : nullptr;
}

StaticField const* Struct::getStaticField(std::string const& fieldName) const noexcept
{
	decltype(staticFields)::const_iterator first = staticFields.find(StaticField(std::string(fieldName)));

	return (first != staticFields.cend()) ? &*first : nullptr;
}

Method const* Struct::getMethod(std::string const& methodName, uint16 minFlags, bool shouldInspectParents) const noexcept
{
	auto range = methods.equal_range(Method(std::string(methodName)));

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

std::vector<Method const*> Struct::getMethods(std::string const& methodName, uint16 minFlags, bool shouldInspectParents) const noexcept
{
	std::vector<Method const*> result;

	auto range = methods.equal_range(Method(std::string(methodName)));

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

StaticMethod const* Struct::getStaticMethod(std::string const& methodName, uint16 minFlags, bool shouldInspectParents) const noexcept
{
	auto range = staticMethods.equal_range(StaticMethod(std::string(methodName)));

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

std::vector<StaticMethod const*> Struct::getStaticMethods(std::string const& methodName, uint16 minFlags, bool shouldInspectParents) const noexcept
{
	std::vector<StaticMethod const*> result;

	auto range = staticMethods.equal_range(StaticMethod(std::string(methodName)));

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