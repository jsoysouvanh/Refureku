#pragma once

#include <type_traits>

/**
*	This macro generates a traits which allows to know at compile-time if a class owns a callable method called MethodName
*/
#define GENERATE_IMPLEMENTS_PUBLIC_METHOD_TRAITS(MethodName)																					\
template<typename Class, typename T>	struct implements_##MethodName {};																		\
template <typename Class, typename Ret, typename... Args>																						\
struct implements_##MethodName<Class, Ret(Args...)>																								\
{																																				\
	private:																																	\
		template<typename T>																													\
		static constexpr auto check(T*) -> typename std::is_same<decltype(std::declval<T>().MethodName(std::declval<Args>()...)), Ret>::value;	\
																																				\
		template<typename>																														\
		static constexpr std::false_type check(...);																							\
																																				\
	public:																																		\
		static constexpr bool value = decltype(check<Class>(nullptr))::value;																	\
};																																				\
																																				\
template <typename Class, typename Ret, typename... Args>																						\
inline constexpr bool implements_##MethodName##_v = implements_##MethodName<Class, Ret(Args...)>::value;

/**
*	This macro generates a traits which allows to know at compile-time if a class has a public field named fieldName
*/
#define GENERATE_HAS_PUBLIC_FIELD_TRAITS(fieldName)																			\
template <typename Class, typename FieldType>																				\
struct hasField_##fieldName																									\
{																															\
	private:																												\
		template <typename T>																								\
		static constexpr auto check(T*) -> typename std::is_same<decltype(std::declval<T>().fieldName), FieldType>::value;	\
																															\
		template <typename>																									\
		static constexpr std::false_type check(...);																		\
																															\
	public:																													\
		static constexpr bool value = decltype(check<Class>(nullptr))::value;												\
};																															\
																															\
template <typename Class, typename FieldType>																				\
inline constexpr bool hasField_##fieldName##_v = hasField_##fieldName_v<Class, FieldType>::value;