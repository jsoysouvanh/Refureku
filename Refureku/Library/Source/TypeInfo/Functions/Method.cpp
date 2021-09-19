#include "Refureku/TypeInfo/Functions/Method.h"

#include <cassert>

#include "Refureku/TypeInfo/Archetypes/Struct.h"

using namespace rfk;

Method::Method(std::string&& methodName, uint64 methodId, Type const& returnType, std::unique_ptr<ICallable>&& internalMethod, EMethodFlags flags, Entity const* outerEntity) noexcept:
	MethodBase(std::forward<std::string>(methodName), methodId, returnType, std::forward<std::unique_ptr<ICallable>>(internalMethod), flags, outerEntity)
{
	assert(!static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::Static));
}

void Method::inheritBaseMethodProperties() noexcept
{
	//Make sure outerEntity is set and is a class or a struct
	assert(getOuterEntity() != nullptr && (getOuterEntity()->getKind() == EEntityKind::Struct || getOuterEntity()->getKind() == EEntityKind::Class));

	Struct const* ownerStruct = reinterpret_cast<Struct const*>(getOuterEntity());

	//Check inherited properties if this method is an override
	if ((flags & EMethodFlags::Override) == EMethodFlags::Override && !ownerStruct->directParents.empty())
	{
		Method const* parentMethod = nullptr;

		for (Struct::Parent const& parent : ownerStruct->directParents)
		{
			parentMethod = parent.type->getMethod([this](Method const* other){ return getName() == other->getName() && hasSamePrototype(other) && isConst() == other->isConst(); }, true);

			if (parentMethod != nullptr)
			{
				//Found the parent method
				inheritProperties(*parentMethod);

				break;
			}
		}
	}
}