#pragma once

#include <memory>

#include "Config.h"

#include "Misc/FundamentalTypes.h"
#include "TypeInfo/Entity.h"
#include "TypeInfo/EAccessSpecifier.h"
#include "Utility/ICallable.h"

namespace rfk
{
	enum EMethodFlags : uint16
	{
		/** No flag */
		Default			= 0,

		/** Access specifiers */
		Public			= 1 << 0,
		Protected		= 1 << 1,
		Private			= 1 << 2,

		/** Method qualifiers */
		Static			= 1 << 3,
		Inline			= 1 << 4,
		Virtual			= 1 << 5,
		PureVirtual		= 1 << 6,
		Override		= 1 << 7,
		Final			= 1 << 8,
		Const			= 1 << 9
	};

	class MethodBase : public Entity
	{
		protected:
			/** Handle pointing to the actual method in memory */
			std::shared_ptr<ICallable>	_internalMethod;

			MethodBase()											= default;
			MethodBase(std::string&&				name, 
					   uint64						id,
					   EMethodFlags					flags,
					   std::shared_ptr<ICallable>&&	internalMethod)	noexcept;
			MethodBase(MethodBase const&)							= default;
			MethodBase(MethodBase&&)								= default;

			MethodBase& operator=(MethodBase const&)				= default;
			MethodBase& operator=(MethodBase&&)						= default;

		public:
			/** Flags describing this method */
			EMethodFlags	flags	= EMethodFlags::Default;

			~MethodBase() = default;

			/** Get access of this method */
			EAccessSpecifier	getAccess()		const	noexcept;

			/** Getter for this methods qualifiers */
			bool				isStatic()		const	noexcept;
			bool				isInline()		const	noexcept;
			bool				isVirtual()		const	noexcept;
			bool				isPureVirtual()	const	noexcept;
			bool				isOverride()	const	noexcept;
			bool				isFinal()		const	noexcept;
			bool				isConst()		const	noexcept;
	};
}