#pragma once

#include <iostream>

namespace refureku
{
	template <typename T>
	class Function;

	template <typename Return_Type, typename... Arg_Types>
	class Function<Return_Type(Arg_Types...)>
	{
		typedef	void (*copyCallableFunction)(char**, char*);

		private:
			#pragma region Classes

			// this class is used to fake use parameters and avoid compilation warnings
			struct sink
			{
				template<typename... Args>
				sink(Args const&...) {}
			};

			template <typename Functor, typename Caller>
			class MemberFunction final : public NonMemberFunction<Functor>
			{
				private:
					#pragma region Variables

					Caller*		m_caller;

					#pragma endregion

				public:
					#pragma region Constructors

					inline MemberFunction() noexcept :
						NonMemberFunction<Functor>(),
						m_caller{ nullptr }
					{}

					inline MemberFunction(Functor const& in_functor, Caller* in_caller)	noexcept :
						NonMemberFunction<Functor>(in_functor),
						m_caller{ in_caller }
					{}

					inline MemberFunction(Functor&& in_functor, Caller* in_caller) noexcept :
						NonMemberFunction<Functor>(std::forward<Functor>(in_functor)),
						m_caller{ in_caller }
					{}

					MemberFunction(MemberFunction<Functor, Caller> const& in_other)	= default;
					MemberFunction(MemberFunction<Functor, Caller>&& in_other)		= default;

					#pragma endregion

					#pragma region Destructor

					~MemberFunction() = default;

					#pragma endregion

					#pragma region Methods

					static void copy(ICallable** in_dest, MemberFunction* in_src) noexcept
					{
						if (in_dest != nullptr && in_src != nullptr)
							*in_dest = new MemberFunction<Functor, Caller>(in_src->m_functor, in_src->m_caller);
						else
							std::cout << "[Error] MemberFunction::copy null pointer" << std::endl;	//SWITCH TO LOG
					}

					#pragma endregion

					#pragma region Operators
					
					MemberFunction& operator=(MemberFunction<Functor, Caller> const& in_other)	= default;
					MemberFunction& operator=(MemberFunction<Functor, Caller>&& in_other)		= default;

					inline bool operator==(ICallable const& in_callable) const noexcept override
					{
						try
						{
							MemberFunction const& mf = dynamic_cast<MemberFunction const&>(in_callable);

							return m_caller == mf.m_caller && m_functor == mf.m_functor;
						}
						catch (std::bad_cast const&)
						{
							//tried to compare member and non-member
							return false;
						}
					}
					
					inline Return_Type operator()(Arg_Types... in_args) noexcept override
					{
						return (m_caller->*m_functor)(std::forward<Arg_Types>(in_args)...);
					}

					#pragma endregion
			};

			#pragma endregion

			#pragma region Variables

			ICallable*				m_function;
			copyCallableFunction	m_copyCallableFunc;

			#pragma endregion

		public:
			#pragma region Constructors

			inline	Function()							noexcept;
			
			template <typename Functor>
			inline	Function(Functor in_functor)		noexcept;
			
			template <typename Caller>
			inline	Function(Return_Type (Caller::*in_ptrToMember)(Arg_Types...), Caller& in_caller) noexcept;

			template <typename Caller>
			inline	Function(Return_Type(Caller::*in_ptrToMember)(Arg_Types...) const, Caller& in_caller) noexcept;

			inline	Function(Function const& in_other)	noexcept;
			inline	Function(Function&& in_other)		noexcept;

			#pragma endregion

			#pragma region Destructor

			~Function()	noexcept;

			#pragma endregion

			#pragma region Methods

			inline bool	isValid() const noexcept;

			#pragma endregion

			#pragma region Operators

			inline Function&	operator=(Function const& in_other)														noexcept;
			inline Function&	operator=(Function&& in_other)															noexcept;

			template <typename Other_Return_Type, typename... Other_Arg_Types>
			inline bool			operator==(Function<Other_Return_Type(Other_Arg_Types...)> const& in_other)		const	noexcept;

			inline Return_Type	operator()(Arg_Types... in_args)														noexcept;

			#pragma endregion
	};

	/*!
	 * The clean implementation is written in below 3 headers, but the compilator is angry about it...
	 */
	//#include "Utility/ICallable.hpp"
	//#include "Utility/NonMemberFunction.hpp"
	//#include "Utility/MemberFunction.hpp"

	#include "Utility/Function.inl"
}