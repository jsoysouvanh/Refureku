#include "TypeInfo/Struct.h"

using namespace refureku;

Struct::Struct(std::string&& newName, uint64 newId, ECategory newCategory) noexcept:
	Archetype(std::forward<std::string>(newName), std::forward<uint64>(newId), std::forward<ECategory>(newCategory))
{
}

Method const* Struct::getMethod(std::string const& methodName) const noexcept
{
	//Look between [start, end]
	auto first = std::lower_bound(methods.cbegin(), methods.cend(), Method(std::string(methodName)),
								  [](Method const& m1, Method const& m2){ return m1.name < m2.name; });

	return (first != methods.cend() && first->name == methodName) ? &*first : nullptr;
}

std::vector<Method const*> Struct::getMethods(std::string const& methodName) const noexcept
{
	auto range = std::equal_range(methods.cbegin(), methods.cend(), Method(std::string(methodName)),
								  [](Method const& m1, Method const& m2){ return m1.name < m2.name; });

	//Translate Method const& into Method const* to avoid copies
	std::vector<Method const*> result(std::distance(range.first, range.second));
	std::transform(range.first, range.second, result.begin(), [](Method const& method) -> Method const* { return &method; });

	return result;
}

StaticMethod const* Struct::getStaticMethod(std::string const& methodName) const noexcept
{
	//Look between [start, end]
	auto first = std::lower_bound(staticMethods.cbegin(), staticMethods.cend(), StaticMethod(std::string(methodName)),
								  [](StaticMethod const& m1, StaticMethod const& m2){ return m1.name < m2.name; });

	return (first != staticMethods.cend() && first->name == methodName) ? &*first : nullptr;
}

std::vector<StaticMethod const*> Struct::getStaticMethods(std::string const& methodName) const noexcept
{
	auto range = std::equal_range(staticMethods.cbegin(), staticMethods.cend(), StaticMethod(std::string(methodName)),
								  [](StaticMethod const& m1, StaticMethod const& m2){ return m1.name < m2.name; });

	//Translate Method const& into Method const* to avoid copies
	std::vector<StaticMethod const*> result(std::distance(range.first, range.second));
	std::transform(range.first, range.second, result.begin(), [](StaticMethod const& method) -> StaticMethod const* { return &method; });

	return result;
}

bool Struct::inheritsFrom(Archetype const& otherType) const noexcept
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