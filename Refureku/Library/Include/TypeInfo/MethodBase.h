#pragma once

#include <string>
#include <memory>

#include "Config.h"

#include "Misc/FundamentalTypes.h"
#include "TypeInfo/EAccessSpecifier.h"
#include "Utility/ICallable.h"

namespace refureku
{
	class MethodBase
	{
		protected:
			/** Unique identifier for this method -> OwnerName+MethodName+Prototype */
			uint64						_id				= 0u;

			/** Handle pointing to the actual method */
			std::shared_ptr<ICallable>	_internalMethod;


			MethodBase()											= default;
			MethodBase(std::string&&				methodName, 
					   uint64						methodId,
					   EAccessSpecifier				accessSpecifier,
					   std::shared_ptr<ICallable>&&	internalMethod)	noexcept;
			//MethodBase(MethodBase&&)				noexcept;

		public:
			/** Name of this method */
			std::string			name;

			EAccessSpecifier	access = EAccessSpecifier::Undefined;

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