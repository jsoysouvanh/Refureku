#include "TypeInfo/Methods/StaticMethod.h"

#include <utility>	//std::forward

using namespace refureku;

StaticMethod::StaticMethod(std::string&& methodName, uint64 methodId, EAccessSpecifier accessSpecifier, std::shared_ptr<ICallable>&& internalMethod) noexcept:
	MethodBase(std::forward<std::string>(methodName),
			   std::forward<uint64>(methodId),
			   std::forward<EAccessSpecifier>(accessSpecifier),
			   std::forward<std::shared_ptr<ICallable>>(internalMethod))
{}

//StaticMethod::StaticMethod(StaticMethod&& other) noexcept:
//	MethodBase(std::forward<StaticMethod>(other))
//{}