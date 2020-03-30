#pragma once

#include <memory>

#include "Config.h"
#include "TypeInfo/Entity.h"
#include "TypeInfo/EAccessSpecifier.h"
#include "TypeInfo/Methods/EMethodFlags.h"
#include "Utility/ICallable.h"

namespace rfk
{
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