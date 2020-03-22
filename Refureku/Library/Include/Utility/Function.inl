
#pragma region Constructors

template <typename Return_Type, typename... Arg_Types>
inline Function<Return_Type(Arg_Types...)>::Function() noexcept:
	m_function{nullptr},
	m_copyCallableFunc{nullptr}
{}

template <typename Return_Type, typename... Arg_Types>
template <typename Functor>
inline Function<Return_Type(Arg_Types...)>::Function(Functor in_functor) noexcept:
	m_function{ new NonMemberFunction<std::decay<Functor>::type>(std::move(in_functor)) },
	m_copyCallableFunc{ reinterpret_cast<copyCallableFunction>(&NonMemberFunction<std::decay<Functor>::type>::copy) }
{}

template <typename Return_Type, typename... Arg_Types>
template <typename Caller>
inline Function<Return_Type(Arg_Types...)>::Function(Return_Type (Caller::*in_ptrToMember)(Arg_Types...), Caller& in_caller) noexcept:
	m_function{ new MemberFunction<decltype(in_ptrToMember), Caller>(in_ptrToMember, &in_caller) },
	m_copyCallableFunc{ reinterpret_cast<copyCallableFunction>(&MemberFunction<decltype(in_ptrToMember), Caller>::copy) }
{}

template <typename Return_Type, typename... Arg_Types>
template <typename Caller>
inline Function<Return_Type(Arg_Types...)>::Function(Return_Type(Caller::*in_ptrToMember)(Arg_Types...) const, Caller& in_caller) noexcept:
	m_function{ new MemberFunction<decltype(in_ptrToMember), Caller>(in_ptrToMember, &in_caller) },
	m_copyCallableFunc{ reinterpret_cast<copyCallableFunction>(&MemberFunction<decltype(in_ptrToMember), Caller>::copy) }
{}

template <typename Return_Type, typename... Arg_Types>
inline Function<Return_Type(Arg_Types...)>::Function(Function const& in_other) noexcept:
	m_function{ nullptr },
	m_copyCallableFunc{ in_other.m_copyCallableFunc }
{
	if (in_other.m_function != nullptr)
	{
		//Copy function
		in_other.m_copyCallableFunc(reinterpret_cast<TEchar**>(&m_function), reinterpret_cast<TEchar*>(in_other.m_function));
	}
	else
	{
		m_function = nullptr;
	}
}

template <typename Return_Type, typename... Arg_Types>
inline Function<Return_Type(Arg_Types...)>::Function(Function&& in_other) noexcept:
	m_function{std::move(in_other.m_function)},
	m_copyCallableFunc{in_other.m_copyCallableFunc}
{
	in_other.m_function			= nullptr;
	in_other.m_copyCallableFunc	= nullptr;
}

#pragma endregion

#pragma region Destructor

template <typename Return_Type, typename... Arg_Types>
Function<Return_Type(Arg_Types...)>::~Function() noexcept
{
	if (m_function != nullptr)
		delete m_function;
}

#pragma endregion

#pragma region Methods

template <typename Return_Type, typename... Arg_Types>
inline TEbool Function<Return_Type(Arg_Types...)>::isValid() const noexcept
{
	return m_function != nullptr;
}

#pragma endregion

#pragma region Operators

template <typename Return_Type, typename... Arg_Types>
inline Function<Return_Type(Arg_Types...)>& Function<Return_Type(Arg_Types...)>::operator=(Function const& in_other) noexcept
{
	if (in_other.m_function != nullptr)
	{
		//Copy function
		in_other.m_copyCallableFunc(reinterpret_cast<TEchar**>(&m_function), reinterpret_cast<TEchar*>(in_other.m_function));
	}
	else
	{
		m_function = nullptr;
	}

	m_copyCallableFunc = in_other.m_copyCallableFunc;

	return *this;
}

template <typename Return_Type, typename... Arg_Types>
inline Function<Return_Type(Arg_Types...)>& Function<Return_Type(Arg_Types...)>::operator=(Function&& in_other) noexcept
{
	m_function			= std::move(in_other.m_function);
	m_copyCallableFunc	= in_other.m_copyCallableFunc;
		
	in_other.m_function			= nullptr;
	in_other.m_copyCallableFunc = nullptr;

	return *this;
}

template <typename Return_Type, typename... Arg_Types>
template <typename Other_Return_Type, typename... Other_Arg_Types>
inline TEbool Function<Return_Type(Arg_Types...)>::operator==(Function<Other_Return_Type(Other_Arg_Types...)> const& in_other) const noexcept
{
	//Check there is same number of arguments in both functions
	if constexpr (sizeof...(Arg_Types) == sizeof...(Other_Arg_Types))
	{
		//Check each argument of both fold expressions have the same type
		if constexpr (((std::is_same<Arg_Types, Other_Arg_Types>::value) && ...))
		{
			return	m_function != nullptr &&
				in_other.m_function != nullptr &&
				*m_function == *in_other.m_function;
		}
	}
}

template <typename Return_Type, typename... Arg_Types>
inline Return_Type Function<Return_Type(Arg_Types...)>::operator()(Arg_Types... in_args) noexcept
{
	#ifdef TE_DEBUG
	if (m_function == nullptr)
	{
		//used cout here because logger using function causes include loops
		std::cout << "[Crash] Tried to invoke empty function" << std::endl;
	}
	#endif

	return (*m_function)(std::forward<Arg_Types>(in_args)...);
}

#pragma endregion