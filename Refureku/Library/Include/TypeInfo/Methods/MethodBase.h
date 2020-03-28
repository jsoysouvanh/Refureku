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
					   std::shared_ptr<ICallable>&&	internalMethod,
					   bool							isInline)		noexcept;
			MethodBase(MethodBase const&)							= default;
			MethodBase(MethodBase&&)								= default;

			MethodBase& operator=(MethodBase const&)	= default;
			MethodBase& operator=(MethodBase&&)			= default;

		public:
			/** Accessibility of this method in its owner struct */
			EAccessSpecifier	access		= EAccessSpecifier::Undefined;
			
			/** Is this method inline */
			bool				isInline	= false;

			~MethodBase() = default;
	};
}