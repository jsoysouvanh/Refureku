#include "TypeInfo/Type.h"

#include <algorithm>

using namespace refureku;

Type::Type(std::string&& newName, uint64 newId, ECategory newCategory) noexcept:
	name{std::forward<std::string>(newName)},
	id{newId},
	category{newCategory}
{
}

Method const* Type::getMethod(std::string const& methodName) const noexcept
{
	//Look between [start, end]
	auto first = std::lower_bound(methods.cbegin(), methods.cend(), Method(std::string(methodName)),
						 [](Method const& m1, Method const& m2){ return m1.name < m2.name; });
	
	return (first != methods.cend()) ? &*first : nullptr;
}

StaticMethod const* Type::getStaticMethod(std::string const& methodName) const noexcept
{
	//Look between [start, end]
	auto first = std::lower_bound(staticMethods.cbegin(), staticMethods.cend(), StaticMethod(std::string(methodName)),
								  [](StaticMethod const& m1, StaticMethod const& m2){ return m1.name < m2.name; });
	
	return (first != staticMethods.cend()) ? &*first : nullptr;
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