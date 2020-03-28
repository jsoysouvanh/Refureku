#include "TypeInfo/Methods/Method.h"

#include "TypeInfo/Struct.h"

using namespace refureku;

Method::Method(std::string&&				methodName,
			   uint64						methodId,
			   EAccessSpecifier				accessSpecifier,
			   std::shared_ptr<ICallable>&& internalMethod,
			   bool							isInline,
			   Struct const*				methodOwnerType,
			   bool							isVirtual,
			   bool							isPureVirtual,
			   bool							isOverride,
			   bool							isFinal,
			   bool							isConst) noexcept:
	MethodBase(std::forward<std::string>(methodName), methodId, accessSpecifier, std::forward<std::shared_ptr<ICallable>>(internalMethod), isInline),
	ownerType{methodOwnerType},
	isVirtual{isVirtual},
	isPureVirtual{isPureVirtual},
	isOverride{isOverride},
	isFinal{isFinal},
	isConst{isConst}
{
}