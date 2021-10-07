#include "Refureku/TypeInfo/Functions/Method.h"

#include <cassert>

#include "Refureku/TypeInfo/Functions/MethodImpl.h"
#include "Refureku/Exceptions/ConstViolation.h"

using namespace rfk;

Method::Method(char const* name, std::size_t id, Type const& returnType,
					 ICallable* internalMethod, EMethodFlags flags, Entity const* outerEntity) noexcept:
	MethodBase(new MethodImpl(name, id, returnType, internalMethod, flags, outerEntity))
{
}

Method::Method(Method&&) noexcept = default;

Method::~Method() noexcept = default;

void Method::inheritBaseMethodProperties() noexcept
{
	//TODOOOOOOO

	//Make sure outerEntity is set and is a class or a struct
	assert(getOuterEntity() != nullptr && (getOuterEntity()->getKind() == EEntityKind::Struct || getOuterEntity()->getKind() == EEntityKind::Class));

	//Struct const* ownerStruct = reinterpret_cast<Struct const*>(getOuterEntity());

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

void Method::throwConstViolationException(char const* message) const
{
	throw ConstViolation(message);
}