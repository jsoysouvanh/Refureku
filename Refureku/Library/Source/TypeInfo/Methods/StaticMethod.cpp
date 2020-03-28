#include "TypeInfo/Methods/StaticMethod.h"

#include <utility>	//std::forward

using namespace refureku;

StaticMethod::StaticMethod(std::string&&				methodName,
						   uint64						methodId,
						   EAccessSpecifier				accessSpecifier,
						   std::shared_ptr<ICallable>&&	internalMethod,
						   bool							isInline)	noexcept:
	MethodBase(std::forward<std::string>(methodName),
			   methodId,
			   accessSpecifier,
			   std::forward<std::shared_ptr<ICallable>>(internalMethod),
			   isInline)
{
}