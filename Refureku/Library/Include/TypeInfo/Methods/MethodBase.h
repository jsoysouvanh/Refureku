#pragma once

#include <memory>

#include "Config.h"

#include "Misc/FundamentalTypes.h"
#include "TypeInfo/Entity.h"
#include "TypeInfo/EAccessSpecifier.h"
#include "Utility/ICallable.h"

namespace refureku
{
	class MethodBase : public Entity
	{
		protected:
			/** Handle pointing to the actual method in memory */
			std::shared_ptr<ICallable>	_internalMethod;

			MethodBase()											= default;
			MethodBase(std::string&&				methodName, 
					   uint64						methodId,
					   EAccessSpecifier				accessSpecifier,
					   std::shared_ptr<ICallable>&&	internalMethod)	noexcept;
			MethodBase(MethodBase const&)							= default;
			MethodBase(MethodBase&&)								= default;

			MethodBase& operator=(MethodBase const&)	= default;
			MethodBase& operator=(MethodBase&&)			= default;

		public:
			/** Accessibility of this method in its owner struct */
			EAccessSpecifier	access = EAccessSpecifier::Undefined;

			//TODO Dispatch these in Method & StaticMethod
			bool	isDefault		: 1;
			bool	isStatic		: 1;
			bool	isVirtual		: 1;
			bool	isPureVirtual	: 1;
			bool	isInline		: 1;
			bool	isOverride		: 1;
			bool	isFinal			: 1;
			bool	isConst			: 1;

			~MethodBase() = default;
	};
}