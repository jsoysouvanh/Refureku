#pragma once

#include <memory>
#include <vector>

#include "Config.h"
#include "Utility/ICallable.h"
#include "TypeInfo/Type.h"
#include "TypeInfo/Entity.h"
#include "TypeInfo/EAccessSpecifier.h"
#include "TypeInfo/Methods/EMethodFlags.h"
#include "TypeInfo/Methods/MethodParameter.h"
#include "TypeInfo/Methods/MethodError.h"

namespace rfk
{
	class MethodBase : public Entity
	{
		private:
			template <size_t Rank, typename FirstArgType, typename... OtherArgTypes>
			void	checkArgumentsStrict(FirstArgType&& a, OtherArgTypes&&... args)	const;

			template <size_t Rank, typename LastArgType>
			void	checkArgumentsStrict(LastArgType&& a)	const;

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

			template <typename... ArgTypes>
			void checkArgumentsStrict(ArgTypes&&... args)	const;

			template <typename... ArgTypes>
			void checkArgumentsLax(ArgTypes&&... args)		const;

			template <typename ReturnType>
			void checkReturnTypeStrict()	const;

			template <typename ReturnType>
			void checkReturnTypeLax()		const;

			MethodBase& operator=(MethodBase const&)				= default;
			MethodBase& operator=(MethodBase&&)						= default;

		public:
			/** Flags describing this method */
			EMethodFlags					flags	= EMethodFlags::Default;

			/** Type returned by this method */
			Type							returnType;

			/** Parameters of this method */
			std::vector<MethodParameter>	parameters;

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

	#include "TypeInfo/Methods/MethodBase.inl"
}