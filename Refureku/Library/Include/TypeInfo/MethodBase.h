#pragma once

namespace refureku
{
	class MethodBase
	{
		public:
			bool	isDefault		: 1;
			bool	isStatic		: 1;
			bool	isVirtual		: 1;
			bool	isPureVirtual	: 1;
			bool	isInline		: 1;
			bool	isOverride		: 1;
			bool	isFinal			: 1;
			bool	isConst			: 1;
	};
}