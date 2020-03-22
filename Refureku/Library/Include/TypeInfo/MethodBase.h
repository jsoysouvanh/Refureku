#pragma once

#include "Config.h"

#include "Utility/ICallable.h"

namespace refureku
{
	class MethodBase
	{
		protected:
			ICallable*	_internalMethod	= nullptr;

			MethodBase()							= delete;
			MethodBase(ICallable* internalMethod)	noexcept;
			MethodBase(MethodBase&&)				noexcept;

		public:
			bool	isDefault		: 1;
			bool	isStatic		: 1;
			bool	isVirtual		: 1;
			bool	isPureVirtual	: 1;
			bool	isInline		: 1;
			bool	isOverride		: 1;
			bool	isFinal			: 1;
			bool	isConst			: 1;

			//TODO accessSpecifier

			~MethodBase() noexcept;
	};
}