#include "Refureku/TypeInfo/Functions/Method.h"

#include <cassert>

#include "Refureku/TypeInfo/Functions/MethodImpl.h"
#include "Refureku/TypeInfo/Archetypes/Struct.h"
#include "Refureku/TypeInfo/Archetypes/ParentStruct.h"
#include "Refureku/Exceptions/ConstViolation.h"

using namespace rfk;

template class REFUREKU_TEMPLATE_API_DEF rfk::Allocator<Method const*>;
template class REFUREKU_TEMPLATE_API_DEF rfk::Vector<Method const*, rfk::Allocator<Method const*>>;

Method::Method(char const* name, std::size_t id, Type const& returnType,
					 ICallable* internalMethod, EMethodFlags flags, Entity const* outerEntity) noexcept:
	MethodBase(new MethodImpl(name, id, returnType, internalMethod, flags, outerEntity))
{
}

Method::Method(Method&&) noexcept = default;

Method::~Method() noexcept = default;

void Method::inheritBaseMethodProperties() noexcept
{
	//Make sure outerEntity is set and is a class or a struct
	assert(getOuterEntity() != nullptr && (getOuterEntity()->getKind() == EEntityKind::Struct || getOuterEntity()->getKind() == EEntityKind::Class));

	Struct const* ownerStruct = reinterpret_cast<Struct const*>(getOuterEntity());

	//Check inherited properties if this method is an override
	std::size_t directParentsCount = ownerStruct->getDirectParentsCount();
	if ((getFlags() & EMethodFlags::Override) == EMethodFlags::Override && directParentsCount != 0u)
	{
		struct Data
		{
			Method const& self;
			Method const* parentMethod;
		} data{ *this, nullptr };

		if (!ownerStruct->foreachDirectParent([](rfk::ParentStruct const& parent, void* userData)
			{
				Data& data = *reinterpret_cast<Data*>(userData);

				data.parentMethod = parent.getArchetype().getMethodByPredicate([](Method const& method, void* userData)
																			   {
																				   Method const& method2 = reinterpret_cast<Data*>(userData)->self;

																				   return	method.hasSameName(method2.getName()) &&
																							method.hasSameSignature(method2);
																			   }, userData, true);

				//Continue until we find a parent method
				return data.parentMethod == nullptr;
			}, &data))
		{
			//Found the parent method
			getPimpl()->inheritProperties(*data.parentMethod->getPimpl());
		}
	}
}

void Method::throwConstViolationException() const
{
	throw ConstViolation("Can't call a non-const member function on a const caller instance.");
}

void Method::throwInvalidCallerException() const
{
	throw InvalidCaller("The caller instance has no relationship with this method hence it can't be called.");
}