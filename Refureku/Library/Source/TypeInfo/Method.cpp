#include "TypeInfo/Method.h"

using namespace refureku;

Method::Method(std::string&& methodName, uint64 methodId, EAccessSpecifier accessSpecifier, Type const* methodOwnerType, ICallable* internalMethod) noexcept:
	MethodBase(std::forward<std::string>(methodName), std::forward<uint64>(methodId), std::forward<EAccessSpecifier>(accessSpecifier), internalMethod),
	ownerType{methodOwnerType}
{}

//Method::Method(Method&& other) noexcept:
//	MethodBase(std::forward<Method>(other)),
//	ownerType{other.ownerType}
//{}