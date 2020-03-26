#include "TypeInfo/Type.h"

#include <algorithm>

using namespace refureku;

Type::Type(std::string&& newName, uint64 newId, ECategory newCategory) noexcept:
	name{std::forward<std::string>(newName)},
	id{newId},
	category{newCategory}
{
}

Method const* Type::getMethod(std::string const& methodName, std::string const& prototype) const noexcept
{
	return nullptr;

	////Look between [start, end]
	//auto first = std::lower_bound(methods.cbegin(), methods.cend(), Method(std::string(methodName)),
	//					 [methodName](Method const& m1, Method const& m2){ return m1.name < m2.name; });
	//
	//if (prototype.empty())
	//{
	//	return (first != methods.cend()) ? &*first : nullptr;
	//}
	//else
	//{
	//	//Look between [first method called methodName, end]
	//	//std::vector<Method>::const_iterator last = std::lower_bound(first, methods.cend(), [](std::string const& m1, std::string const& m2){ return true; });
	//
	//	//TODO
	//	return nullptr;
	//}
}

StaticMethod const* Type::getStaticMethod(std::string const& methodName, std::string const& prototype) const noexcept
{
	return nullptr;

	//decltype(staticMethodsLookupTable)::const_iterator it = staticMethodsLookupTable.find(std::move(methodName));
	//
	//return (it != staticMethodsLookupTable.cend()) ? &it->second.front() : nullptr;
}

bool Type::inheritsFrom(Type const& otherType) const noexcept
{
	for (Parent const& parent : directParents)
	{
		if (&parent.type == &otherType || parent.type.inheritsFrom(otherType))
		{
			return true;
		}
	}

	return false;
}