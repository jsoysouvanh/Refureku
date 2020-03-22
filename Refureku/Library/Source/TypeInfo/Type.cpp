#include "TypeInfo/Type.h"

using namespace refureku;

Method const* Type::getMethod(std::string methodName) const noexcept
{
	decltype(methodLookupTable)::const_iterator it = methodLookupTable.find(std::move(methodName));

	return (it != methodLookupTable.cend()) ? it->second : nullptr;
}

StaticMethod const* Type::getStaticMethod(std::string methodName) const noexcept
{
	decltype(staticMethodLookupTable)::const_iterator it = staticMethodLookupTable.find(std::move(methodName));

	return (it != staticMethodLookupTable.cend()) ? it->second : nullptr;
}