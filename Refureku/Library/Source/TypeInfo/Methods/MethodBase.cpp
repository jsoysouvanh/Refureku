#include "TypeInfo/Methods/MethodBase.h"

using namespace refureku;

MethodBase::MethodBase(std::string&& methodName, uint64 methodId, EAccessSpecifier accessSpecifier, std::shared_ptr<ICallable>&& internalMethod) noexcept:
	Entity(std::forward<std::string>(methodName), methodId),
	_internalMethod{std::forward<std::shared_ptr<ICallable>>(internalMethod)},
	access{std::forward<EAccessSpecifier>(accessSpecifier)}
{
}