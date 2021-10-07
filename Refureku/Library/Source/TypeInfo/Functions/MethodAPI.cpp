#include "Refureku/TypeInfo/Functions/MethodAPI.h"

#include <cassert>

#include "Refureku/TypeInfo/Functions/MethodImpl.h"
#include "Refureku/Exceptions/ConstViolation.h"

using namespace rfk;

MethodAPI::MethodAPI(char const* name, std::size_t id, Type const& returnType,
					 ICallable* internalMethod, EMethodFlags flags, Entity const* outerEntity) noexcept:
	MethodBaseAPI(new MethodImpl(name, id, returnType, internalMethod, flags, outerEntity))
{
}

MethodAPI::MethodAPI(MethodAPI&&) noexcept = default;

MethodAPI::~MethodAPI() noexcept = default;

void MethodAPI::inheritBaseMethodProperties() noexcept
{
	//TODOOOOOOO

	//Make sure outerEntity is set and is a class or a struct
	assert(getOuterEntity() != nullptr && (getOuterEntity()->getKind() == EEntityKind::Struct || getOuterEntity()->getKind() == EEntityKind::Class));

	//StructAPI const* ownerStruct = reinterpret_cast<Struct const*>(getOuterEntity());

	////Check inherited properties if this method is an override
	//std::size_t directParentsCount = ownerStruct->getDirectParentsCount();
	//if ((getFlags() & EMethodFlags::Override) == EMethodFlags::Override && directParentsCount != 0u)
	//{
	//	Method const* parentMethod = nullptr;

	//	for (std::size_t i = 0; i < directParentsCount; i++)
	//	{
	//		parentMethod = ownerStruct->getDirectParentAt(i).getArchetype().getMethod([this](Method const& other){ return getName() == other.getName() && hasSamePrototype(other) && isConst() == other.isConst(); }, true);

	//		if (parentMethod != nullptr)
	//		{
	//			//Found the parent method
	//			inheritProperties(*parentMethod);

	//			break;
	//		}
	//	}
	//}
}

void MethodAPI::throwConstViolationException(char const* message) const
{
	throw ConstViolation(message);
}