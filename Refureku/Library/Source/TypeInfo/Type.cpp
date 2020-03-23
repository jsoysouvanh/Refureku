#include "TypeInfo/Type.h"

using namespace refureku;

Method const* Type::getMethod(std::string methodName) const noexcept
{
	decltype(methodsLookupTable)::const_iterator it = methodsLookupTable.find(std::move(methodName));

	return (it != methodsLookupTable.cend()) ? &it->second.front() : nullptr;
}

StaticMethod const* Type::getStaticMethod(std::string methodName) const noexcept
{
	decltype(staticMethodsLookupTable)::const_iterator it = staticMethodsLookupTable.find(std::move(methodName));

	return (it != staticMethodsLookupTable.cend()) ? &it->second.front() : nullptr;
}