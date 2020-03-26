#include "TypeInfo/MethodBase.h"

using namespace refureku;

MethodBase::MethodBase(std::string&& methodName, uint64 methodId, EAccessSpecifier accessSpecifier, std::shared_ptr<ICallable>&& internalMethod) noexcept:
	_id{std::forward<uint64>(methodId)},
	_internalMethod{std::forward<std::shared_ptr<ICallable>>(internalMethod)},
	name{std::forward<std::string>(methodName)},
	access{std::forward<EAccessSpecifier>(accessSpecifier)}
{
}