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
#include "TypeInfo/Methods/Exceptions/ArgCountMismatchException.h"
#include "TypeInfo/Methods/Exceptions/ReturnTypeMismatchException.h"
#include "TypeInfo/Methods/Exceptions/ArgTypeMismatchException.h"

namespace rfk
{
	class MethodBase : public Entity
	{
		private:
			template <size_t Rank, typename FirstArgType, typename SecondArgType, typename... OtherArgTypes>
			void	checkArguments()		const;

			template <size_t Rank, typename LastArgType>
			void	checkArguments()		const;

			template <typename... ArgTypes>
			bool	hasSameArgumentsCount()	const	noexcept;

			template <typename ReturnType>
			bool	hasSameReturnType()		const	noexcept;

			template <size_t Rank, typename FirstArgType, typename SecondArgType, typename... OtherArgTypes>
			bool	hasSameArgumentTypes()	const	noexcept;

			template <size_t Rank, typename LastArgType>
			bool	hasSameArgumentTypes()	const	noexcept;

			template <typename... ArgTypes>
			bool	hasSameArgumentTypes()	const	noexcept;

		protected:
			/** Handle pointing to the actual method in memory */
			std::shared_ptr<ICallable>	_internalMethod;

			MethodBase()											= delete;
			MethodBase(std::string&&				name, 
					   uint64						id,
					   EMethodFlags					flags,
					   std::shared_ptr<ICallable>&&	internalMethod)	noexcept;
			MethodBase(MethodBase const&)							= default;
			MethodBase(MethodBase&&)								= default;

			template <typename... ArgTypes>
			void checkArgumentsCount()	const;

			template <typename... ArgTypes>
			void checkArguments()		const;

			template <typename ReturnType>
			void checkReturnType()		const;

			MethodBase& operator=(MethodBase const&)	= default;
			MethodBase& operator=(MethodBase&&)			= default;

		public:
			/** Flags describing this method */
			EMethodFlags					flags	= EMethodFlags::Default;

			/** Type returned by this method */
			Type							returnType;

			/** Parameters of this method */
			std::vector<MethodParameter>	parameters;

			~MethodBase() = default;

			/**
			*	\tparam ReturnType Return type to compare with
			*	\tparam... ArgTypes Argument types to compare with
			*
			*	\return true if this method has the same return type as ReturnType and the same
						parameter types as ArgTypes, else false
			*/
			template <typename ReturnType, typename... ArgTypes>
			bool				hasSamePrototype()	const	noexcept;

			/**
			*	\tparam... ArgTypes Argument types to compare with
			*
			*	\return true if this method has the same parameter types as ArgTypes, else false
			*/
			template <typename... ArgTypes>
			bool				hasSameArguments()	const	noexcept;

			/**
			*	\return Access specifier of this method in its owner struct/class.
			*/
			EAccessSpecifier	getAccess()			const	noexcept;

			/**
			*	\return true if this method is static, else false.
			*/
			bool				isStatic()			const	noexcept;

			/**
			*	\return true if this method is declared as inline, else false.
			*/
			bool				isInline()			const	noexcept;

			/**
			*	\return true if this method is virtual, else false.
			*/
			bool				isVirtual()			const	noexcept;

			/**
			*	\return true if this method is virtual pure, else false.
			*/
			bool				isPureVirtual()		const	noexcept;

			/**
			*	\return true if this method overrides a previous definition, else false.
			*/
			bool				isOverride()		const	noexcept;

			/**
			*	\return true if this method is marked as final, else false.
			*/
			bool				isFinal()			const	noexcept;

			/**
			*	\return true if this method is marked as const, else false.
			*/
			bool				isConst()			const	noexcept;
	};

	#include "TypeInfo/Methods/MethodBase.inl"
}